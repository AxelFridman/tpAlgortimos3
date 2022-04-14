//
// Created by juan on 26/3/22.
//
//#include <cstdlib>
#include <iostream>
#include <vector>
#include <list>
//#include <sys/stat.h>
//#include <sys/errno.h>
//#include <dirent.h>
//#include <algorithm>
#include "red.h"

using namespace std;

Red::Red(string archivo){
    if(archivo == "dummy"){
        // Dummy instance usada en tp1.cpp para reservar espacio en memoria como instancia global necesaria para
        // usar en la funcion de ordenamiento pasada a sort().
        // Esta instancia no es usada, sino pisada con la instancia creada en main.
        return;
    }

    ifstream entradaRed(archivo.c_str());
    if(entradaRed.fail()){
        cout << "Error en archivo " << archivo << endl;
        exit(0);
    }

    string nada;
    entradaRed >> nada >> nada >> _N >> _M;

    //cout << "N: " << _N <<  " M: " << _M << endl;
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

bool Red::esClique(list<int> & Kx) {
    for (list<int>::iterator it = Kx.begin(); it != Kx.end(); it++) {
        for (list<int>::iterator it2 = next(it, 1); it2 != Kx.end(); it2++) {
            if (!sonAmigos(*it, *it2))
                return false;
        }
    }
    return true;
}