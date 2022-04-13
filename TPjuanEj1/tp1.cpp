#include <set>
#include <vector>
#include "red.h"
#include <iostream>
#include "tp1.h"
//Siguiente linea solo para Windows
#include <ctime>
#include <bits/stdc++.h> // Usada para sort
using namespace std;

int infl_max; // Se inicializa la variable del grupo con mayor influencia
set<int> Q_max; // Y el grupo correspondiente a esa mayor influencia.
// Ambos necesarios que sean de un scope global


//../../instancias/brock200_2.clq
// _________________________________________________________________________________________________________________________________________
// _________________________________________________________________________________________________________________________________________

// COMIENZO FUNCIONES AUXILIARES:
void visualizarVector(const vector<int> v, Red r){
    for(int i=0;i<v.size();i++){
        std :: cout << " Es el nodo "<<v[i] << " y su influencia es " << r.p(v[i]) ;
        std :: cout << " "<< endl ;
    }
    std :: cout << " "<< endl ;
}

template<typename tipo>
tipo mergeOrdenado(tipo tA, tipo tB, Red r){ // Esta funcion se encarga de unir en un mismo tipo ordenado, a 2 tipos que ya estan ordenados.
    tipo tC; // Se crea el nuevo tipo que voy a devolver
    int indA= 0; // Inicializo ambos indices en 0, y voy a mover siempre uno a la vez.
    int indB= 0;
    while( indA< tA.size() and  indB< tB.size() ){ // Mientras todavia no haya terminado de recorrer ninguno de las 2 estructuras
        if(r.p(tA[indA])<r.p(tB[indB])){
            tC.push_back(tA[indA]); //Agrego a mi estructura de respuesta el elemento mas chico entre ambos, y le aumento el indice.
            indA ++;
        }
        else{
            tC.push_back(tB[indB]); // Esto es lo mismo en caso de que la segunda estructura tenga el elem mas chico.
            indB ++;
        }
    }
    while( indA< tA.size()){ // Si ya termione de recorrer la segunda estr pero me queda de la primera, debo meter todos los pendientes al final.
        tC.push_back(tA[indA]);
        indA ++;
    }

    while( indB< tB.size()){ // Misma idea si termine la primer estructura pero tengo pendientes de la segunda.
        tC.push_back(tB[indB]);
        indB ++;
    }
    return tC; // Finalmente devuelvo la estructura que me estuve armando de tamanio (tA + tB)
}

template<typename tipo>
void mergeSort(tipo &tA, Red r){ // Esta es una implementacion de mergesort. No es in-place. Ordena ascendente. Se pasa tipo por referencia.
    if(tA.size()<2){ // Caso base si tengo 1 elem o 0 elem, ya esta ordenado. No debo cambiar nada.
        return;
    }
    else{
        if(tA.size() == 2){ // El segundo caso base es si tiene 2 elem, en el cual debo, o swapearlos o no, segun su orden y ya estaria.
            if(r.p(tA[0])>r.p(tA[1])){
                auto aux = tA[0]; // Utilizo una variable para guardar primer elem de manera auxiliar.
                tA[0] = tA[1]; // hago swap
                tA[1] = aux;
            }
        }
        else { // Caso contrario, osea tA tiene MAS de 2 elementos
            int mitad = int(tA.size() / 2); // Me creo un indice que me parta a tA en 2 partes iguales, o casi iguales.
            tipo primeraParte; // Inicializo ambas mitades que me voy a generar. Por esto no es in place.
            tipo segundaParte;
            for(int i=0; i<tA.size(); i++){
                if(i<mitad){
                    primeraParte.push_back(tA[i]); // La mitad la agrego al tipo de la primer mitad
                }
                else{
                    segundaParte.push_back(tA[i]); // La otra mitad del original a la segunda estructura.
                }
            }
            mergeSort(primeraParte, r); // Ahora ordeno cada una de las 2 partes
            mergeSort(segundaParte, r);
            tA = mergeOrdenado( primeraParte, segundaParte, r); // Y finalmente las junto en una misma estructura. ahora que ambas estan ordenadas.
        }
    }
}

template<typename tipo>
void swap(tipo &tA, int i, int j){ // Esta funcion recibe un tipo y 2 indices y los cambia de lugar a los elementos en esos indices.
    auto old = tA[i]; // Utilizo valor auxiliar para no perder info de que hay en tA[i]
    tA[i] = tA[j]; // Y luego cambio sus valores respectivos.
    tA[j] = old;
}

template<typename tipo>
void revertirOrden(tipo &tA){ // La idea de esta funcion es que te "da vuelta" un tipo de dato indexable.
    for(int i=0; i<int(tA.size()/2); i++){ // Itero hasta la mitad del vector.
        swap(tA, i, tA.size()-i-1); // Y swapeo los de una punta con el lado simetrico del otro lado, asi hasta llegar al medio.
    }
}

// FIN FUNCIONES AUXILIARES AJENAS AL TP.
// _________________________________________________________________________________________________________________________________________
// _________________________________________________________________________________________________________________________________________

void ejercicio1(Red& red){ // La idea de esta funcion es que recibe el tipo red y devuelve la maxima clique, y cual es su influencia total.
    cout<<"Usando la ultima version:"<<endl;
    //Siguiente linea solo para Windows
    unsigned t0,t1;
    //Siguiente linea solo para Windows
    t0 = clock();
    set<int> Q; // Seteo a Q como el conjunto vacio pues son los participes de la clique actual.
    vector<int> K = {};
    for (int i: red.usuarios()){
        K.push_back(i); // Mientras que K comienzan siendo todos los usuarios de la red.
    }
    mergeSort(K, red); // Los ordeno de manera ascendente.
    revertirOrden(K); // Los doy vuelta para que sea descendiente. Osea de mayor influencia para abajo.
    //visualizarVector(K, red);
    int infl = 0; // Seteo la influencia de la clique actual como  0
    infl_max = 0; // Y la influencia max global tambien.
    Q_max.clear(); // En caso de que me haya quedado algo guardado, repto que Qmax sea el conjunto vacio.

    //buscarMaxInfl (Q, K, infl, red); // Y llamo a la funcion con los parametros 'completos'.
    vector<int> usados(K.size(), 0);
    buscarMaxInfl (Q, K, 0, usados, infl, red);
    // Esta funcion automaticamente actualizara qmax y infl_max entonces es solo cuestion de imprimirlos
    cout<<"Influencia maxima es: "<<infl_max<<endl;
    cout<<"La clique mas influyente: ";
    for (int i: Q_max) // Imprime todos los participantes de la clique mas influyente.
        cout<<i<<" ";
    cout<<endl;
    //Siguiente linea solo para Windows
    t1 = clock();
    //Siguiente linea solo para Windows
    cout<<"Tiempo: "<<double (t1-t0)/CLOCKS_PER_SEC<<endl;
}

int sumarInfluenciasDe(vector<int>& K, Red& red){
    int res = 0;
    for(int v: K){
        res += red.p(v);
    }
    return res;
}

int sumarInfluenciasDe(vector<int>& K, int idx_K, vector<int>& usados, Red& red){
    int res = 0;
    for(int i=idx_K+1; i<= K.size()-1; i++){
        if(usados[i] == 0){
            // Solo sumo los elementos de K que no hayan sido pasados a Q
            res += red.p(K[i]);
        }
    }
    return res;
}

bool sonTodosAmigosDe(int i, vector<int>& K, Red& red, vector<int>& toErase){
    // Devuelve true si todos los elementos de un vector de actores son amigos
    // del actor en la posicion i, ignorando todos los indices en toErase
    bool res=true;
    int j=0;

    while(j<= K.size() && res){
        if(i != j and count(toErase.begin(), toErase.end(), j) == 0)
            res = res * red.sonAmigos(K[i], K[j]);
        j+=1;
    }
    return res;
}

bool sonTodosAmigosDe(int idx, vector<int>& K, vector<int>& usados, Red& red){
    // Devuelve true si todos los elementos de un vector de actores son amigos
    // del actor en la posicion i, ignorando todos los indices en usados
    bool res=true;
    int j=0;

    while(j <= K.size() && res){
        if(usados[j] == 0 and j != idx){
            // Solo veo los elementos k_j de K que no hayan sido pasados a Q
            res = res * red.sonAmigos(K[idx], K[j]);
        }
        j+=1;
    }
    return res;
}

int sum(vector<int> v){
    // Devuelve la suma de todos los elementos de v
    return accumulate(v.begin(), v.end(), 0);
}

bool todos_unos(vector<int> v){
    // Devuelve true si todos los elementos de v son distintos de cero
    for(int b: v){
        if(b==0){
            return false;
        }
    }
    return true;
}

vector<int> amigosDexEnY(int idx_K, vector<int>& K, vector<int>& usadosi, Red& red){ // Funcion que devuelve todos amigos de una persona entre un vector de personas.
    //vector<int> res = {}; // originalmente nadie
    vector<int> res(K.size(), 0);
    for (int j=idx_K+1; j <= K.size()-1; j++) { // y por cada persona del grupo le pregunto si es amigo de v
        if (usadosi[j]==0){
            if (red.sonAmigos(K[idx_K], K[j])){
                // Si es amigo, lo marco en el vector res, pero todavía no lo uso
                res[j] = 1;
            }
            else{
                // A los no amigos de K[idx_K] los "saco" de los disponibles (ie. los marco como usados)
                usadosi[j] = 1;
            }
        }
    }
    return res;
}

int agregarCliqueDeAmigos(set<int>& Qi, vector<int>& K, int idx_K, vector<int>& usadosi, vector<int>&  amigosDev, Red& red){ //La idea de esta funcion son 2 cosas.
    //por un lado actualizar la influencia de k, sumando toda su influencia.
    // y tambien llevar todos los elementos de k en q.
    int res = 0;
    for (int i=idx_K+1; i < K.size(); i++){
        if (amigosDev[i]==1){
            res += red.p(K[i]); // Sumo todas las influencias de cada persona en k
            Qi.insert(K[i]); // ademas para cada persona en k la agrego a q
            usadosi[i] = 1;
        }
    }
    //Ki.clear(); // vacio k para que sea conjunto vacio
    return res; // devuelvo la inflencia de todos los k originales juntos.
}

int agregarTodoKClique(set<int>& Q, vector<int>& K, int idx_K, vector<int>& usados, Red& red){ //La idea de esta funcion son 2 cosas.
    //por un lado actualizar la influencia de k, sumando toda su influencia.
    // y tambien llevar todos los elementos de k en q.
    int res = 0;
    for (int i=idx_K+1; i < K.size(); i++){
        if (usados[i]==0){
            res += red.p(K[i]); // Sumo todas las influencias de cada persona en k
            Q.insert(K[i]); // ademas para cada persona en k la agrego a q
            usados[i] = 1;
        }
    }
    //Ki.clear(); // vacio k para que sea conjunto vacio
    return res; // devuelvo la inflencia de todos los k originales juntos.
}

void buscarMaxInfl (set<int>& Q, vector<int>& K, int idx_K, vector<int>& usados, int infl, Red& red){ // Funcion que busca maximique clique a tarves de ir partiendo todos los pendientes en si
                                                                      // los puedo agregar a mi clique o no e iterando.
    //if(K.size()==0){ // Caso base, si ya no me queda nadie mas posible para agregar
    //cout << sum(usados) << endl;

    if(todos_unos(usados)){
        if (infl > infl_max){ // Entonces me pregunto si la influencia de este grupo es mas que la maxima
            /*
            cout << "idx_K: " << idx_K << endl << endl;
            for(int u: usados){
                cout << u << " ";
            }
            cout << endl;
            */
            infl_max = infl; // Si lo es, actualizo ambas variables globales.
            Q_max = Q;
        }
    }
    else{ // Caso contrario en el que SI tengo a alguien que seria potencial para agregar a mi clique.
        if(infl + sumarInfluenciasDe(K, idx_K, usados, red) < infl_max){
            // Poda pedida en el tp para reducir espacio de busqueda
            return;
        }

        int v = K[idx_K]; // Lo tomo a ese alguien como el mas influyente que tengo disponible.
        //K.erase(K.begin()); // Y lo saco de los restantes  // Nota: El erase borra la primera posicion, pero mueve todos los valores siguientes una posición, por lo que tarda O(#K-1) en borrar un elemento.
        usados[idx_K] = 1;
        vector<int> usadosi = usados; // El elemento idx_K de K queda SIEMPRE marcado como usado, en cualquiera de las dos ramas
        set<int> Qi = Q; // Me copio el set de la clique hasta el momento
        Qi.insert(v); // Solo que a esta le agrego ADEMAS  v, el mayor influyente disponible de los usuarios en este momento.
        //vector<int> Ki = amigosDexEnY(idx_K, K, red); // tomo todos los amigos de la persona v en K, y me los guardo en Ki.
        vector<int> amigosDev = amigosDexEnY(idx_K, K, usadosi, red); // Devuelve un vector de unos y ceros indicando los amigos, y marca los no-amigos como usados en usadosi

        /*
        cout << "amigosDev: " << v << " suman:"<< sum(amigosDev) << endl;
        for(int u: amigosDev){
            cout << u << " ";
        }
        cout << endl;
        return;
        */
        int infli = infl + red.p(v); // Como esta es la rama en donde asumo que V es parte de la clique,
                                    // le agrego a la influencia actual la influencia de v
        /*
        //vector<int> toErase = {};
        for (int i=0; i < K.size(); i++){
            //if(sonTodosAmigosDe(i, K, red, toErase)){
            if(sonTodosAmigosDe(i, K, usadosi, red)){
                Qi.insert(K[i]);
                vector<int> Ki_ = amigosDexEnY(K[i], K, usadosi, red);  // TODO: Revisar esto!
                infli += red.p(K[i]);
                //toErase.push_back(i);
                usadosi[i] = 1;
            }
        }
        */
        // TODO: Ver cómo hacer esto de abajo! <<<<<<<<<<<<<<<<< !!!

        /*vector<int> Ki = {};
        for(int i=idx_K; i < K.size(); i++){
            if(usadosi[i]==0 and amigosDev[i]==1){
                Ki.push_back(K[i]);
                //usadosi[i] = 1; // Como estos elementos van a ser agregados luego, ya los marco como usados
            }
        }*/

        if (red.indicadosEsClique(K, idx_K, amigosDev)){ // Si en Ki todos son amigos con todos debo actualizar influencia y ponerlos todos en Q
            //cout << infli << " ";
            infli += agregarCliqueDeAmigos(Qi, K, idx_K, usadosi, amigosDev, red);
            //cout << infli << endl;
            //cout << "entra aca" << endl;
        }

        // Si en K todos son amigos con todos debo actualizar influencia y ponerlos todos en Q
        if (red.noIndicadosEsClique(K, idx_K, usados)){
            //cout << infl << " ";
            infl += agregarTodoKClique(Q, K, idx_K, usados, red);
            //cout << infl << " idx_K:" << idx_K << endl;
            //cout << "entra aca tambien" << endl;
        }

        idx_K = idx_K + 1; // Siempre me muevo al menos un lugar en K
        buscarMaxInfl(Q, K, idx_K, usados, infl, red); // Caso en que no agrego a v.

        // Salteo los k_i que ya hayan sido usados y busco el primero libre
        while(usadosi[idx_K]==1 and idx_K <= K.size()-1) {
            idx_K = idx_K + 1;
        }
        buscarMaxInfl(Qi, K, idx_K, usadosi,infli, red); // Finalmente llamo al lado en donde agrego a v y considero el resto de posibilidades.
    }
}

vector<int> amigosDexEnY(int v, vector<int>& K, Red& red){ // Funcion que devuelve todos amigos de una persona entre un vector de personas.
    vector<int> res = {}; // originalmente nadie
    for (int i=0; i<K.size(); i++) { // y por cada persona del grupo le pregunto si es amigo de v
        if (red.sonAmigos(v,K[i]))
            res.push_back(K[i]); // si es amigo de el lo agrego a la respuesta.
    }
    return res;
}



int agregarTodosLosKenQeInfluenciaK(set<int>& Qi, vector<int>& Ki, Red& red){ //La idea de esta funcion son 2 cosas.
                                                                //por un lado actualizar la influencia de k, sumando toda su influencia.
                                                                // y tambien llevar todos los elementos de k en q.
    int res = 0;
    for (int i=0; i<Ki.size(); i++){
        res += red.p(Ki[i]); // Sumo todas las influencias de cada persona en k
        Qi.insert(Ki[i]); // ademas para cada persona en k la agrego a q
    }
    Ki.clear(); // vacio k para que sea conjunto vacio
    return res; // devuelvo la inflencia de todos los k originales juntos.
}
// ../../instancias/brock200_1.clq
// /Users/imac/Documents/tp1algo3/TPjuanEj1/instancias/brock200_1.clq