//
// Created by juan on 26/3/22.
//
//#include <cstdlib>
#include <iostream>
#include <vector>
//#include <sys/stat.h>
//#include <sys/errno.h>
//#include <dirent.h>
//#include <algorithm>
#include "red.h"

using namespace std;

Red::Red(string archivo){
    ifstream entradaRed(archivo.c_str());
    if(entradaRed.fail()){
        cout << "Error en archivo " << archivo << endl;
        exit(0);
    }

    string nada;
    entradaRed >> nada >> nada >> _N >> _M;

    cout << "N: " << _N <<  " M: " << _M << endl;
    _p = vector<int> (_N);
    _Amistades = vector<vector<bool>> (_N, vector<bool> (_N,false));
    for (int i = 0; i < _N; ++i) {
        int actor;
        entradaRed >> nada >> actor >> _p[actor-1];
    }
    for (int i = 0; i < _M; ++i) {
        int actor1, actor2;
        entradaRed >> nada >> actor1 >> actor2;
        _Amistades [actor1-1][actor2-1] = true;
        _Amistades [actor2-1][actor1-1] = true;
    }
}

set<int> Red::usuarios() {
    set<int> res;
    for (int i = 1; i < _N+1; ++i) {
        res.insert(i);
    }
    return res;
}

bool Red::sonAmigos(int i, int j) {
    //cout<<"i: "<<i<<endl;
    if (i <= 0 || i > _N || j <= 0 || j > _N){
        cout<<"NO EXISTEN ESOS USUARIOS: "<< i<< " " << j<< endl;
        exit(0);
    }
    return _Amistades[i-1][j-1];
}

int Red::cantUsuarios() {
    return _N;
}

int Red::cantAmistades() {
    return _M;
}

int Red::p(int i) {
    if (i <= 0 || i > _N){
        cout<<"NO EXISTE ESE USUARIO"<< endl;
        exit(0);
    }
    return _p[i-1];
}

bool Red::esClique(vector<int> & K) {
    for (int i=0; i<K.size(); i++) {
        for (int j=i+1; j<K.size(); j++) {
            if (!sonAmigos(K[i], K[j]))
                return false;
        }
    }
    return true;
}