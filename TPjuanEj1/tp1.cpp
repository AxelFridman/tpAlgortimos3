#include <set>
#include <vector>
#include <list>
#include "red.h"
#include <iostream>
#include "tp1.h"

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
    cout <<  endl;
}

void mostrarI_i(list<list<int>> &K) {
    cout << endl;
    int i = 1;
    for(list<int> I_i: K){
        cout << "I_" << i << ": ";
        for (int v: I_i) {
            cout << v << " ";
        }
        cout << endl;
        i++;
    }

    cout <<  endl;
}

// Comparacion para ordenar
bool compare_actors_importances(const int &first, const int &second) {
    return (red_global.p(first) < red_global.p(second));
}

// _________________________________________________________________________________________________________________________________________

void ejercicio1(Red &red) {
    // Esta funcion recibe el tipo red y devuelve la maxima clique y cual es su influencia total.

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
    buscarMaxInflEj1(Q, K, infl, red);

    // Muestro resultados en consola
    cout << infl_max << endl;
    for (int i: Q_max) // Imprime todos los participantes de la clique mas influyente.
        cout << i << " ";
    cout << endl;

}


void ejercicio2(Red &red) {
    // Esta funcion recibe el tipo red y devuelve la maxima clique y cual es su influencia total.

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

    // Seteo la influencia de la clique actual como 0
    int infl = 0;

    // Inicializo Q_max
    Q_max.clear();

    // Me aseguro que K comience cumpRedliendo sus invariantes.
    // Q comienza conteniendo a todos los amigos de todos.
    agregarCadaAmigoDeTodosLosDemasEnK(Q, actores, infl, red);
    infl_max = infl;

    // Llamada a función recursiva
    // Esta funcion automaticamente actualizara Q_max e infl_max
    //buscarMaxInflEnIndependientes(Q, K, infl, red);
    buscarMaxInflEj2(Q, actores, infl, red);

    // Muestro resultados en consola
    cout << infl_max << endl;
    for (int i: Q_max) // Imprime todos los participantes de la clique mas influyente.
        cout << i << " ";
    cout << endl;

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
        // El primer elemento es siempre el de mayor influencia
        v = I_i.front();
        res += red.p(v);
    }
    return res;
}

int particionarYSumarInfluenciasDeIndependientes(list<int> actores, Red &red) {
    int res = 0;
    int v;
    list<list<int>> particion = {};

    list<int>::iterator it = actores.begin();
    list<int>::iterator it2;
    while (it != actores.end()){
        list<int> I_i = {};
        I_i.push_back(*it);

        // Agrego a I_i todos los no amigos de *it
        it2 = next(it);

        while (it2 != actores.end()){
            //if (!red.sonAmigos(*it, *it2)){
            if (sonTodosNoAmigosDeIter(it2, I_i, red)){
                if(I_i.size() < 2){
                    I_i.push_back(*it2);
                }
                // Lo borro y avanzo al siguiente
                it2 = actores.erase(it2);
            }
            else{
                it2 = next(it2);
            }
        }
        // Lo borro y avanzo al siguiente
        it = actores.erase(it);

        particion.push_back(I_i);
    }

    // Sumo las influencias del primer elemento de cada I_i en K
    for (list<int> I_i: particion) {
        // El primer elemento es siempre el de mayor influencia
        v = I_i.front();
        res += red.p(v);
    }

    return res;
}

int particionarYSumarInfluenciasDeIndependientesGreedy(list<int> actores, Red &red) {
    int res = 0;
    int v;
    list<list<int>> particion = {};

    list<int>::iterator it = actores.begin();
    list<int>::iterator it2;
    while (it != actores.end()){
        list<int> I_i = {};
        I_i.push_back(*it);

        // Agrego a I_i todos los no amigos de *it
        it2 = next(it);

        while (it2 != actores.end()){
            if (sonTodosNoAmigosDeIter(it2, I_i, red)){
                I_i.push_back(*it2);
                // Lo borro y avanzo al siguiente
                it2 = actores.erase(it2);
            }
            else{
                it2 = next(it2);
            }
        }
        // Lo borro y avanzo al siguiente
        it = actores.erase(it);

        particion.push_back(I_i);
    }

    // Sumo las influencias del primer elemento de cada I_i en K
    for (list<int> I_i: particion) {
        // El primer elemento es siempre el de mayor influencia
        v = I_i.front();
        res += red.p(v);
    }

    return res;
}

bool sonTodosAmigosDeIter(list<int>::iterator it, list<int> &Ki, Red &red) {
    // Devuelve true si todos los elementos de un vector de actores son amigos
    // del actor en la posicion i, ignorando todos los indices en usados
    list<int>::iterator it2 = Ki.begin();
    bool res = true;

    while (it2 != Ki.end() and res) {
        // Solo veo los elementos k_j de K que no hayan sido pasados a Q
        if (it != it2) {
            res = res and red.sonAmigos(*it, *it2);
        }
        it2 = next(it2);
    }
    return res;
}

bool sonTodosAmigosDeIter(list<int>::iterator it, set<int> &Q, Red &red) {
    // Devuelve true si todos los elementos de un vector de actores son amigos
    // del actor en la posicion i, ignorando todos los indices en usados
    set<int>::iterator it2 = Q.begin();
    bool res = true;

    while (it2 != Q.end() and res) {
        res = res and red.sonAmigos(*it, *it2);
        it2 = next(it2);
    }
    return res;
}
bool sonTodosNoAmigosEntreSi(list<int> &I_i, Red &red){
    bool res = true;
    list<int>::iterator it = I_i.begin();
    while( it != I_i.end()){
        res = res and sonTodosNoAmigosDeIter(it, I_i, red);
        it = next(it, 1);
    }
    return res;
}

bool sonTodosNoAmigosDeIter(list<int>::iterator it, list<int> &I_i, Red &red) {
    // Devuelve true si todos los elementos de un vector de actores son amigos
    // del actor en la posicion i, ignorando todos los indices en usados
    list<int>::iterator it2 = I_i.begin();
    bool res = true;
    while (it2 != I_i.end() and res) {
        // Solo veo los elementos k_j de K que no hayan sido pasados a Q
        if (it != it2) {
            res = res and !red.sonAmigos(*it, *it2);
        }
        it2 = next(it2, 1);
    }
    return res;
}


list<int>::iterator pasarIterDeKaQ(list<int>::iterator it, set<int> &Qx, list<int> &Kx, int &inflx, Red &red) {
    Qx.insert(*it);
    inflx += red.p(*it);
    // Borra y mueve el puntero
    it = Kx.erase(it);

    return it;
}



void revisarNoAmigosDev(int v, set<int> &Qx, list<int> &Kx, int &inflx, Red &red) {
    // Caso Kx vacio
    if (Kx.size() == 0) {
        // Lista vacia, no hago nada
        return;
    }

    // Caso Kx con unico elemento
    list<int>::iterator it2 = Kx.begin();
    if (Kx.size() == 1) {
        // Lo agrego a Qx y sumo su influencia
        it2 = pasarIterDeKaQ(it2, Qx, Kx, inflx, red);
        return;
    }

    // Caso Kx con 2 o más elementos
    while (it2 != Kx.end()) {
        if (!red.sonAmigos(v, *it2) and sonTodosAmigosDeIter(it2, Kx, red)) {
            // Paso elemento a Q y devuelve iterador a siguiente elemento
            int w = *it2;

            it2 = pasarIterDeKaQ(it2, Qx, Kx, inflx, red);

        } else {
            it2 = next(it2);
        }
    }
    return;
}

void amigosDevEnK(int v, list<int> &K, list<int> &Ki, Red &red) { // Funcion que devuelve todos amigos de una persona entre un vector de personas.
    for (int k_i: K) { // y por cada persona del grupo le pregunto si es amigo de v
        if (red.sonAmigos(v, k_i)){
            Ki.push_back(k_i); // si es amigo de el lo agrego a la respuesta.
        }
    }
}

list<int> amigosDevEnKBKP(int v, set<int> &Qi, list<int> &K, int &infli, Red &red) { // Funcion que devuelve todos amigos de una persona entre un vector de personas.
    list<int> Ki = {}; // originalmente nadie
    for (int k_i: K) { // y por cada persona del grupo le pregunto si es amigo de v
        if (red.sonAmigos(v, k_i)){
            Ki.push_back(k_i); // si es amigo de el lo agrego a la respuesta.
        }
    }
    return Ki;
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
            it = next(it);
        }
    }

}

void revisarInvariante (set<int>& Qi, list<int>& Ki,int& infli, Red& red){
    list<int>::iterator it = Ki.begin();
    while(it != Ki.end()) {
        list<int>::iterator it2 = Ki.begin();
        while (it2 != Ki.end() && (red.sonAmigos(*it,*it2) || *it == *it2)){
            ++it2;
        }
        if (it2 == Ki.end()){
            Qi.insert(*it);
            infli += red.p(*it);
            it = Ki.erase(it);
        }else{
            ++it;
        }
    }
}

void buscarMaxInflEj1(set<int> &Q, list<int> &K, int infl, Red &red) {
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

        // Como esta es la rama en donde asumo que V es parte de la clique,
        // le agrego a la influencia actual la influencia de v
        int infli = infl + red.p(v);
        list<int> Ki = {};

        amigosDevEnK(v, K, Ki, red); // tomo todos los amigos de la persona v en K, y me los guardo en Ki.

        revisarInvariante(Qi, Ki, infli, red);
        revisarNoAmigosDev(v, Q, K, infl, red);

        buscarMaxInflEj1(Qi, Ki, infli,
                         red); // Finalmente llamo al lado en donde agrego a v y considero el resto de posibilidades.
        buscarMaxInflEj1(Q, K, infl, red); // idem con el lado que no agrego a v.
    }
}

void buscarMaxInflEj2(set<int> &Q, list<int> &K, int infl, Red &red) {
    // Funcion que busca maximique clique a tarves de ir partiendo todos los pendientes en si
    // los puedo agregar a mi clique o no e iterando.
    if (K.size() == 0) { // Caso base, si ya no me queda nadie mas posible para agregar
        if (infl > infl_max) { // Entonces me pregunto si la influencia de este grupo es mas que la maxima
            infl_max = infl; // Si lo es, actualizo ambas variables globales.
            Q_max = Q;
        }
    } else { // Caso contrario en el que SI tengo a alguien que seria potencial para agregar a mi clique.
        if (infl + particionarYSumarInfluenciasDeIndependientes(K, red) < infl_max) {
            // Poda pedida en el tp para reducir espacio de busqueda
            return;
        }

        int v = K.front(); // Lo tomo a ese alguien como el mas influyente que tengo disponible.
        K.pop_front(); // Y lo saco de los restantes

        // Me copio el set de la clique hasta el momento
        set<int> Qi = Q;
        // Solo que a esta le agrego ADEMAS  v, el mayor influyente disponible de los usuarios en este momento.
        Qi.insert(v);

        // Como esta es la rama en donde asumo que V es parte de la clique,
        // le agrego a la influencia actual la influencia de v
        int infli = infl + red.p(v);
        list<int> Ki = {};
        amigosDevEnK(v, K, Ki, red); // tomo todos los amigos de la persona v en K, y me los guardo en Ki.

        revisarInvariante(Qi, Ki, infli, red);
        revisarNoAmigosDev(v, Q, K, infl, red);

        buscarMaxInflEj2(Qi, Ki, infli,
                         red); // Finalmente llamo al lado en donde agrego a v y considero el resto de posibilidades.
        buscarMaxInflEj2(Q, K, infl, red); // idem con el lado que no agrego a v.
    }
}

void buscarMaxInflEnIndependientes(set<int> &Q, list<list<int>> &K, int infl, Red &red) {
    // Caso base, si ya no me queda nadie mas posible para
    if (K.size() == 0) {
        // Entonces me pregunto si la influencia de este grupo es mas que la maxima
        if (infl > infl_max) {
            // Si lo es, actualizo ambas variables globales.
            infl_max = infl;
            Q_max = Q;
            cout << "Nuevo infl_max: " << infl_max << endl;
        }
    } else {
        // Todavia tengo elementos por agregar
        if (infl + sumarInfluenciasDeIndependientes(K, red) < infl_max) {
            // Poda pedida en el tp para reducir espacio de busqueda
            return;
        }

        // Iterador al primer I_i
        list<list<int>>::iterator iterK = K.begin();
        // Agarro el primer elemento del primer I_i
        list<int>::iterator it = iterK->begin();

        int v = *it;

        // Me copio el set de la clique hasta el momento
        set<int> Qi = Q;
        bool elementoValido = sonTodosAmigosDeIter(it, Q, red);
        if(elementoValido) {
            // En la rama derecha SOLO borro v de I_i
            // En la rama izquierda agrego v y borro tod o I_i
            Qi.insert(v);
        }

        // Borro el elemento que habia elegido de la lista I_i correspondiente
        it = iterK->erase(it);

        bool borro_I_i_vacio = (iterK->size() == 0);
        if (borro_I_i_vacio){
            // I_i es vacio. Debo borrarlo
            iterK = K.erase(iterK);
        }

        list<list<int>> Ki = K;

        list<list<int>>::iterator itKi = Ki.begin();
        if(!borro_I_i_vacio){
            // ie: Quedaron elementos en I_i, pero ninguno es amigo del que acabo de sacar
            // Iterador al primer I_i que quiero borrar

            // Borro el I_i pues ya puse en Q uno de sus elementos, y el resto son no amigos (ie: los descarto)
            itKi = Ki.erase(itKi);
        }

        bool add_v_first;
        if (K.size() > 1){
            list<list<int>>::iterator iterNext = next(iterK);
            int v_nextI_i = *iterNext->begin();
            int v_nextVal = v; //iterK->front();
            add_v_first = red.p(v_nextVal) > red.p(v_nextI_i);

            // Pruebo hacer una tercer rama
            if(!add_v_first){
                // Salto directamente al proximo I, borrando el I_i actual
                list<list<int>> Kgreed = K;
                if(borro_I_i_vacio){
                    Kgreed.erase(Kgreed.begin());
                }
            }
        }
        else{
            // No next I_i to choose the other path
            add_v_first = true;
        }

        // Finalmente llamo al lado en donde agrego a v y considero el resto de posibilidades.
        if(elementoValido){
            // Agrego a la influencia actual la influencia de v
            int infli = infl + red.p(v);
            // Esta rama solo se llama en caso de que se agregue un elemento a Qi
            buscarMaxInflEnIndependientes(Qi, Ki, infli, red);
        }
        // idem con el lado que no agrego a v.
        buscarMaxInflEnIndependientes(Q, K, infl, red);
    }
}
