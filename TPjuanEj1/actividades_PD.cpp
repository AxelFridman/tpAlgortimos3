//
// Created by Noé Fabián HSUEH on 06/04/2022.
// ../instancias/instancia_2.txt

#include "actividades_PD.h"
#include <ctime>

// TODO Emprolijar código
// TODO Chequear complejidades

void mostrarVector(const vector<int>& v){
    cout <<"[ ";
    for(int i=0;i<v.size();i++){
        std :: cout << v[i] <<" ";
    }
    std :: cout << " ]" << endl ;
}

Actividades::Actividades(string archivo) {
    ifstream entradaActividades(archivo.c_str());
    if(entradaActividades.fail()){
        cout << "Error en archivo " << archivo << endl;
        exit(0);
    }
    entradaActividades >> _N;
//    cout << "Hay " << _N << " actividades" << endl;
    _S = vector<int>(_N);
    _T = vector<int>(_N);
    _B = vector<int>(_N);
    _W = vector<int>(_N, _N);
    _mem = vector<int>(_N,-1);
    for (int i = 0; i < _N; ++i) {
        entradaActividades >> _S[i] >> _T[i] >> _B[i];
    }
    construirW(_W);
    cout<<endl;
    cout<<"Vector S: ";
    mostrarVector(_S);
    cout<<"Vector T: ";
    mostrarVector(_T);
    cout<<"Vector B: ";
    mostrarVector(_B);
    cout<<"Vector W: ";
    mostrarVector(_W);
}

void Actividades::construirW(vector<int> &v) {
    vector<int> bucket (2*_N+1, -1);
    for (int i = _N - 1; 0 <= i; --i) {
        bucket[_S[i]] = i;
    }
    int rem = _N;
    for (int i = 2*_N; 0 <= i; --i) {
        if (bucket[i] != -1){
            int otro = bucket[i];
            bucket[i] = rem;
            rem = otro;
        }else{
            bucket[i] = rem;
        }
    }
    for (int i = 0; i < _N; ++i) {
        v[i] = bucket[_T[i]];
    }
}

int Actividades::cantActividades() const{
    return _N;
}

int Actividades::buscarBeneficioMax(int i) {
    if (i==_N){
        return  0;
    } else {
        if (_mem[i] == -1) {
            int b1 = buscarBeneficioMax(_W[i])  + _B[i];
            int b2 = buscarBeneficioMax(i + 1);
            _mem[i] = max(b1, b2);
        }
        return _mem[i];
    }
}

void Actividades::ejer3_4() {
    int res = buscarBeneficioMax(0);
    cout<<"El maximo beneficio total es: "<< res <<endl;
}

void Actividades::ejer3_5() {
    cout<<"La suma maxima es: "<<endl;
    int res = bottom_up();
    cout<< res<<endl;
}

void Actividades::reiniciarMem() {
    _mem = vector<int> (_N,-1);
}

int Actividades::bottom_up() {
    _mem[_N-1] = _B[_N-1];
    for (int i = _N-2; i >= 0; --i) {
        int b1 = _B[i];
        if (_W[i] != _N)
            b1 += _mem[_W[i]];
        _mem[i] = max(b1,_mem[i+1]);
    }
    return _mem[0];
}

void Actividades::ejer3_6() {
    cout<<"La suma maxima es "<< buscarBeneficioMax(0)<<endl;
    cout<<"Las actividades correspondientes son: "<<endl;
    vector<int> res = reConstruccionRes();
    mostrarVector(res);
}

vector<int> Actividades::reConstruccionRes(){
    vector<int> res;
    int sumaMax = _mem[0];
    for (int i = 1; i < _N && sumaMax > 0; ++i) {
        if (_mem[i] < sumaMax){
            res.push_back(i-1);
            sumaMax -= _B[i-1];
            i = _W[i-1];
        }
    }
    if (sumaMax != 0)
        res.push_back(_N-1);
    return res;
}