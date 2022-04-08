//
// Created by Noé Fabián HSUEH on 06/04/2022.
// ../instancias/instancia_2.txt

#include "actividades_PD.h"

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
    mostrarVector(_S);
    mostrarVector(_T);
    mostrarVector(_B);
    mostrarVector(_W);
}

void Actividades::construirW(vector<int> &v) {
    // TODO Usar una especie de búsqueda binaria
    for (int i = 0; i < v.size(); ++i) {
        bool b=true;
        for (int j = i+1; j < v.size() && b; ++j) {
            if (!haySolapamiento(i,j)){
                v[i] = j;
                b = false;
            }
        }
    }
}

int Actividades::cantActividades() const{
    return _N;
}

bool Actividades::haySolapamiento(int &i, int &j) const{
    return _T[i] > _S[j];
}

int Actividades::buscarBeneficioMax(int i, vector<int>& v, int sum) {
    /*if (_mem[i] != -1){
        return _mem[i];
    } else {*/
        if (i==_N){
            if (sumaMax < sum){
                sumaMax = sum;
                sol_optima = v;
            }
            return  sum;
        }else {
                if (_mem[i] == -1) {
                    v.push_back(i);
                    int b1 = buscarBeneficioMax(_W[i], v, sum + _B[i]);
                    v.pop_back();
                    int b2 = buscarBeneficioMax(i + 1, v, sum);
                    //_mem[i] = max(buscarBeneficioMax(i), _B[i] + buscarBeneficioMax(_W[i]));
                    _mem[i] = max(b1, b2);
                }
                return _mem[i];
        }
}



int Actividades::ejer3_4() {
    sumaMax = 0;
    vector<int> sol;
    return buscarBeneficioMax(0, sol, 0);
}

void Actividades::mostrarSolucion() {
    mostrarVector(sol_optima);
}
