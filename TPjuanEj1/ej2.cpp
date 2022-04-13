#include <set>
#include <vector>
#include "red.h"
#include <iostream>
#include "tp1.h"
//Siguiente linea solo para Windows
#include <ctime>
#include <bits/stdc++.h> // Usada para sort
#include "tp1.cpp"
#include "ej2.h"

using namespace std;

// Observación importante: Las variables globales infl_max y Q_max son importadas de tp1.cpp

void ejercicio2(Red& red){ // La idea de esta funcion es que recibe el tipo red y devuelve la maxima clique, y cual es su influencia total.
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
    //revertirOrden(K); // Los doy vuelta para que sea descendiente. Osea de mayor influencia para abajo.
    visualizarVector(K, red);
    int infl = 0; // Seteo la influencia de la clique actual como  0
    infl_max = 0; // Y la influencia max global tambien.
    Q_max.clear(); // En caso de que me haya quedado algo guardado, repto que Qmax sea el conjunto vacio.

    buscarMaxInflIndependientes (Q, K, infl, red); // Y llamo a la funcion con los parametros 'completos'.
    // Esta funcion automaticamente actualizara qmax y infl_max entonces es solo cuestion de imprimirlos
    cout<<"Influencia maxima es: "<<infl_max<<endl;
    cout<<"La clique mas influyencte: ";
    for (int i: Q_max) // Imprime todos los participantes de la clique mas influyente.
        cout<<i<<" ";
    cout<<endl;
    //Siguiente linea solo para Windows
    t1 = clock();
    //Siguiente linea solo para Windows
    cout<<"Tiempo: "<<double (t1-t0)/CLOCKS_PER_SEC<<endl;
}

bool noSonAmigos(int w, int z, Red& red){
    return not red.sonAmigos(w, z);
};



void buscarMaxInflIndependientes (set<vector<int>>& Q, vector<int>& K, int infl, Red& red){
    // EJ2: Busco clique máximo a partir de disjuntar K en conjuntos de no amigos entre sí.
    if(K.size()==0){ // Caso base, si ya no me queda nadie mas posible para agregar
        if (infl > infl_max){ // Entonces me pregunto si la influencia de este grupo es mas que la maxima
            infl_max = infl; // Si lo es, actualizo ambas variables globales.
            Q_max = Q;
        }
    }
    else{ // Caso contrario en el que SI tengo a alguien que seria potencial para agregar a mi clique.
        if(infl + sumarInfluenciasDe(K, red) < infl_max){
            // Poda pedida en el tp para reducir espacio de busqueda
            return;
        }

        for (int i=K.size()-1; i>=0; i++){
            int w_i = K[K.size()-1]; // Lo tomo a ese alguien como el mas influyente que tengo disponible.
            //K.erase(K.begin()); // Y lo saco de los restantes

            vector<int> I_i(K.size(), 0);
            //I_i.push_back(w_i);
            // Pongo un 1 en la posición i de w_i
            I_i[K.size()-1] = 1;
            //K.pop_back(); // Borro el último elemento (ie: w_i)

            //for(int j=K.size()-1; j>=0; j++){
            int j = K.size()-2;
            while(j >= 0){
                if (not red.sonAmigos(w_i, K[j])){
                    // Lo meto también en I_i
                    //I_i.push_back(K[j]);
                    I_i[j] = 1;
                    //K.erase(K.begin()+j);
                }
                j-=1;
            }

            Qi.push_back(I_i)
        }

        set<vector<int>> Qi = Q; // Me copio el set de la clique hasta el momento
        Qi.insert(I_i); // Solo que a esta le agrego ADEMAS  v, el mayor influyente disponible de los usuarios en este momento.
        vector<int> Ki = amigosDexEnY(v,K, red); // tomo todos los amigos de la persona v en K, y me los guardo en Ki.
        int infli = infl + red.p(v); // Como esta es la rama en donde asumo que V es parte de la clique,
        // le agrego a la influencia actual la influencia de v

        vector<int> toErase = {};
        for (int i=0; i<K.size(); i++){
            if(sonTodosAmigosDe(i, K, red, toErase)){
                Qi.insert(K[i]);
                vector<int> Ki = amigosDexEnY(K[i],K, red);
                infli += red.p(K[i]);
                toErase.push_back(i);
            }
        }
        // Ordeno indices de mayor a menor para borrarlos de atrás hacia adelante
        sort(toErase.begin(), toErase.end(), greater<int>());
        for (int i: toErase) {
            K.erase(K.begin() + i);
        }

        if (red.esClique(Ki)){ // Si en Ki todos son amigos con todos debo actualizar influencia y ponerlos todos en Q
            infli += agregarTodosLosKenQeInfluenciaK(Qi, Ki, red);
        }

        if (red.esClique(K)){ // Si en K todos son amigos con todos debo actualizar influencia y ponerlos todos en K
            infl += agregarTodosLosKenQeInfluenciaK(Q,K,red);
        }

        buscarMaxInfl(Qi, Ki, infli,red); // Finalmente llamo al lado en donde agrego a v y considero el resto de posibilidades.
        buscarMaxInfl(Q, K, infl,red); // idem con el lado que no agrego a v.
    }
}