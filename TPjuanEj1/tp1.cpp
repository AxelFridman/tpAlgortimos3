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
    // Ordeno de forma ASCENDENTE wrt importancia
    K.sort(compare_actors_importances);
    // Doy vuelta el orden (queda DESCENDENTE).
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


void ejercicio2(Red &red) {
    // Esta funcion recibe el tipo red y devuelve la maxima clique y cual es su influencia total.
    unsigned t0, t1;

    t0 = clock();

    set<int> Q; // Seteo a Q como el conjunto vacio pues son los participes de la clique actual.
    list<list<int>> K = {};
    list<int> actores = {};

    for (int a_i: red.usuarios()) {
        actores.push_back(a_i);
    }

    // Quiero separar a los actores en conjuntos I_i independientes
    // Ordenamiento de actores
    red_global = red;
    // Ordeno de forma ASCENDENTE wrt importancia
    actores.sort(compare_actors_importances);
    // Doy vuelta el orden (queda DESCENDENTE)
    actores.reverse();

    list<int>::iterator it = actores.begin();
    list<int>::iterator it2;
    while (it != actores.end()){
        list<int> I_i = {};
        I_i.push_back(*it);

        // Agrego a I_i todos los no amigos de *it
        it2 = next(it, 1);

        while (it2 != actores.end()){
            if (!red.sonAmigos(*it, *it2)){
                I_i.push_back(*it2);
                // Lo borro y avanzo al siguiente
                it2 = actores.erase(it2);
            }
            else{
                it2 = next(it2, 1);
            }

        }
        // Lo borro y avanzo al siguiente
        it = actores.erase(it);

        K.push_back(I_i);
    }

    // TODO Revisar que cuando meto los I_i en K, efectivamernte los esté copiando y no pisando la referencia una y otra vez

    // Seteo la influencia de la clique actual como 0
    int infl = 0;

    // Inicializo Q_max
    Q_max.clear();

    // Me aseguro que K comience cumpliendo sus invariantes.
    // Q comienza conteniendo a todos los amigos de todos.
    // O sea que todos los I_i que contengan un único elemento, deben ser pasados a Q (pues son amigos de todos).
    list<list<int>>::iterator itK = K.begin();
    list<int> I_i = {};
    while(itK != K.end()){
        I_i = *itK;
        if(I_i.size() == 1){
            // Lo meto en Q, y borro ese I_i
            Q.insert(I_i.front());
            itK = K.erase(itK);
        }
        else{
            itK = next(itK, 1);
        }
    }

    // Todos los I_i en K tienen ahora al menos 2 elementos
    infl_max = infl;

    // Llamada a función recursiva
    // Esta funcion automaticamente actualizara Q_max e infl_max
    buscarMaxInflEnIndependientes(Q, K, infl, red);

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
int sumarInfluenciasDeIndependientes(list<list<int>> &K, Red &red) {
    int res = 0;
    int v;
    // Sumo las influencias del primer elemento de cada I_i en K
    for (list<int> I_i: K) {
        // El primer elemento es siempre el mayor
        v = I_i.front();
        res += red.p(v);
    }
    return res;
}

list<int> amigosDexEnY(int v, list<int> &K, Red &red) { // Funcion que devuelve todos amigos de una persona entre un vector de personas.
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

void buscarMaxInfl(set<int> &Q, list<int> &K, int infl, Red &red) {
    // Funcion que busca maximique clique a tarves de ir partiendo todos los pendientes en si
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

        // Me copio el set de la clique hasta el momento
        set<int> Qi = Q;
        // Solo que a esta le agrego ADEMAS  v, el mayor influyente disponible de los usuarios en este momento.
        Qi.insert(v);

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

void buscarMaxInflEnIndependientes(set<int> &Q, list<list<int>> &K, int infl, Red &red) {
    // Funcion que busca maximique clique a tarves de ir partiendo todos los pendientes en si
    // los puedo agregar a mi clique o no e iterando.

    // Caso base, si ya no me queda nadie mas posible para agregar
    if (K.size() == 0) {
        // Entonces me pregunto si la influencia de este grupo es mas que la maxima
        if (infl > infl_max) {
            // Si lo es, actualizo ambas variables globales.
            infl_max = infl;
            Q_max = Q;
        }
    } else {
        // Todavia tengo elementos por agregar
        if (infl + sumarInfluenciasDeIndependientes(K, red) < infl_max) {
            // Poda pedida en el tp para reducir espacio de busqueda
            return;
        }

        // Iterador al primer I_i
        list<list<int>>::iterator itK = K.begin();
        // Agarro el primer elemento del primer I_i
        list<int>::iterator it = itK->begin();

        //int v = K.front().front();
        int v = *it;
        // Borro este elemento del I_i
        bool I_i_resulta_vacio = (itK->size() == 1);
        it = itK->erase(it);
        // Si al borrar v de I_i, I_i queda vacio, debo debo borrarlo

        if(I_i_resulta_vacio){
            // I_i es vacio. Debo borrarlo
            K.erase(itK);
        }

        // Me copio el set de la clique hasta el momento
        set<int> Qi = Q;
        // En la rama derecha SOLO borro v de I_i
        // En la rama izquierda agrego v y borro tod o I_i
        Qi.insert(v);

        list<list<int>> Ki = K;

        if(!I_i_resulta_vacio){
            // Iterador al primer I_i que quiero borrar
            list<list<int>>::iterator itKi = Ki.begin();
            // Borro el I_i pues ya puse en Q uno de sus elementos, y el resto son no amigos (ie: los descarto)
            Ki.erase(itKi);
        }

        // Agrego a la influencia actual la influencia de v
        int infli = infl + red.p(v);

        // TODO: Si al K que le borré SOLO el elemento v, le queda un unico elemento, tengo que hacer algo más?

        // Finalmente llamo al lado en donde agrego a v y considero el resto de posibilidades.
        buscarMaxInflEnIndependientes(Qi, Ki, infli, red);
        // idem con el lado que no agrego a v.
        buscarMaxInflEnIndependientes(Q, K, infl, red);
    }
}