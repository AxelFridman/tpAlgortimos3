#include <set>
#include <vector>
#include <list>
#include "red.h"
#include <iostream>
#include "tp1.h"

//Siguiente linea solo para Windows
#include <ctime>

using namespace std;

// Ambos necesarios que sean de un scope global
int infl_max;  // Se define la variable del grupo con mayor influencia
set<int> Q_max;

// Global auxiliar necesaria para usar en la funcion de comparacion al ordenar K
Red red_global("dummy");

// _________________________________________________________________________________________________________________________________________

// COMIENZO FUNCIONES AUXILIARES:
void visualizarVector(const list<int> v, Red r) {
    for (int v_i: v) {
        cout << " Es el nodo " << v_i << " y su influencia es " << r.p(v_i);
        cout << " " << endl;
    }
    cout << " " << endl;
}

// Funcion auxiliar para debuguear el codigo. Muestra el contenido de K en consola.
void mostrarK(list<int> &Kx, string indice) {
    cout << endl;
    cout << "K" << indice << ": ";
    for (int k_i: Kx) {
        cout << k_i << " ";
    }
    cout << endl << endl;
}

// Comparacion para ordenar
bool compare_actors_importances(const int &first, const int &second) {
    return (red_global.p(first) < red_global.p(second));
}


// FIN FUNCIONES AUXILIARES AJENAS AL TP.
// _________________________________________________________________________________________________________________________________________
// _________________________________________________________________________________________________________________________________________

void ejercicio1(Red &red) {
    // Esta funcion recibe el tipo red y devuelve la maxima clique y cual es su influencia total.
    unsigned t0, t1;

    t0 = clock();

    set<int> Q; // Seteo a Q como el conjunto vacio pues son los participes de la clique actual.
    list<int> K = {};

    for (int i: red.usuarios()) {
        // Mientras que K comienzan siendo todos los usuarios de la red.
        K.push_back(i);
    }

    // Ordenamiento de K
    red_global = red;
    K.sort(compare_actors_importances);
    K.reverse();

    //visualizarVector(K, red);

    // Seteo la influencia de la clique actual como 0
    int infl = 0;

    // Inicializo Q_max
    Q_max.clear();

    // Me aseguro que K comience cumpliendo sus invariantes.
    // Q comienza conteniendo a todos los amigos de todos.
    agregarCadaAmigoDeTodosLosDemasEnK(Q, K, infl, red);
    infl_max = infl;

    // Llamada a función recursiva
    // Esta funcion automaticamente actualizara Q_max e infl_max
    buscarMaxInfl(Q, K, infl, red);


    // Muestro resultados en consola
    cout << "Influencia máxima es: " << infl_max << endl;
    cout << "La clique más influyente: ";
    for (int i: Q_max) // Imprime todos los participantes de la clique mas influyente.
        cout << i << " ";
    cout << endl;

    t1 = clock();
    cout << "Tiempo: " << double(t1 - t0) / CLOCKS_PER_SEC << endl;
}

int sumarInfluenciasDe(list<int> &K, Red &red) {
    int res = 0;
    for (int v: K) {
        res += red.p(v);
    }
    return res;
}

list<int> amigosDexEnY(int v, list<int> &K,
                       Red &red) { // Funcion que devuelve todos amigos de una persona entre un vector de personas.
    list<int> res = {}; // originalmente nadie
    for (int k_i: K) { // y por cada persona del grupo le pregunto si es amigo de v
        if (red.sonAmigos(v, k_i))
            res.push_back(k_i); // si es amigo de el lo agrego a la respuesta.
    }
    return res;
}

bool sonTodosAmigosDeIter(list<int>::iterator it, list<int> &Ki, Red &red) {
    // Devuelve true si todos los elementos de un vector de actores son amigos
    // del actor en la posicion i, ignorando todos los indices en usados
    list<int>::iterator it2 = Ki.begin();
    bool res = true;
    // TODO: Completar una vez revisada la parte del codigo que usa esta funcion
    while (it2 != Ki.end() && res) {
        // Solo veo los elementos k_j de K que no hayan sido pasados a Q
        if (it != it2) {
            res = res && red.sonAmigos(*it, *it2);
        }
        it2 = next(it2, 1);
    }
    return res;
}


list<int>::iterator pasarIterDeKaQ(list<int>::iterator it, set<int> &Qx, list<int> &Kx, int &inflx, Red &red) {
    Qx.insert(*it);
    //Ki = amigosDexEnY(*it, Ki, red);
    inflx += red.p(*it);
    // Borra y mueve el puntero
    //cout << "Son todos amigos de it!" << endl;
    //cout << "antes de borrar: " << *it << endl;
    it = Kx.erase(it);

    return it;
}

void agregarCadaAmigoDeTodosLosDemasEnK(set<int> &Qx, list<int> &Kx, int &inflx, Red &red) {
    // Caso Kx vacio
    if (Kx.begin() == Kx.end()) {
        // Lista vacia, no hago nada
        return;
    }

    // Caso Kx con unico elemento
    list<int>::iterator it = Kx.begin();
    if (Kx.size() == 1) {
        // Lo agrego a Qx y sumo su influencia
        it = pasarIterDeKaQ(it, Qx, Kx, inflx, red);
        return;
    }

    // Casi Kx con 2 o más elementos
    while (it != Kx.end()) {
        if (sonTodosAmigosDeIter(it, Kx, red)) {
            // Paso elemento a Q y devuelve iterador a siguiente elemento
            it = pasarIterDeKaQ(it, Qx, Kx, inflx, red);
        } else {
            it = next(it, 1);
        }
    }

}

void buscarMaxInfl(set<int> &Q, list<int> &K, int infl,
                   Red &red) { // Funcion que busca maximique clique a tarves de ir partiendo todos los pendientes en si
    // los puedo agregar a mi clique o no e iterando.
    if (K.size() == 0) { // Caso base, si ya no me queda nadie mas posible para agregar
        if (infl > infl_max) { // Entonces me pregunto si la influencia de este grupo es mas que la maxima
            infl_max = infl; // Si lo es, actualizo ambas variables globales.
            Q_max = Q;
        }
    } else { // Caso contrario en el que SI tengo a alguien que seria potencial para agregar a mi clique.
        if (infl + sumarInfluenciasDe(K, red) < infl_max) {
            // Poda pedida en el tp para reducir espacio de busqueda
            return;
        }

        int v = K.front(); // Lo tomo a ese alguien como el mas influyente que tengo disponible.
        K.pop_front(); // Y lo saco de los restantes

        set<int> Qi = Q; // Me copio el set de la clique hasta el momento
        Qi.insert(
                v); // Solo que a esta le agrego ADEMAS  v, el mayor influyente disponible de los usuarios en este momento.
        list<int> Ki = amigosDexEnY(v, K, red); // tomo todos los amigos de la persona v en K, y me los guardo en Ki.
        // Como esta es la rama en donde asumo que V es parte de la clique,
        // le agrego a la influencia actual la influencia de v
        int infli = infl + red.p(v);


        // Esta verificacion vuelve lento al algoritmo. Desactivarla lo acelera y sigue devolviendo el valor correcto,
        // pero no se cumple el invariante de K en cada nodo: Podrian existir actores en K que no tengan no-amigos.
        bool activar_chequeo_amigo_de_todos = true;
        if (activar_chequeo_amigo_de_todos) {
            agregarCadaAmigoDeTodosLosDemasEnK(Qi, Ki, infli, red);
            agregarCadaAmigoDeTodosLosDemasEnK(Q, K, infl, red);
        }

        buscarMaxInfl(Qi, Ki, infli,
                      red); // Finalmente llamo al lado en donde agrego a v y considero el resto de posibilidades.
        buscarMaxInfl(Q, K, infl, red); // idem con el lado que no agrego a v.
    }
}