#include "actividadesGoloso.h"

void mostrarVector2(const vector<int>& v){
    for(int i=0; i<v.size(); i++){
        std :: cout << v[i] <<" ";
    }
    cout<<endl;
}

ActividadesGoloso:: ActividadesGoloso(string archivo){
    ifstream entradaActividades(archivo.c_str());
    if(entradaActividades.fail()){
        cout << "Error en archivo " << archivo << endl;
        exit(0);
    }
    entradaActividades >> _N;
    _S = vector<int>(_N);
    _T = vector<int>(_N);
    for (int i = 0; i < _N; ++i) {
        entradaActividades >> _S[i] >> _T[i];
    }
}

vector<int> ActividadesGoloso:: ordenarPorT() {
    vector<vector<int>> bucket (2*_N + 1);
    for (int i = 0; i < _N; ++i) {
        bucket[_T[i]].push_back(i);
    }
    vector<int> res;
    for (int i = 0; i < 2*_N + 1; ++i) {
        int n = bucket[i].size();
        for (int j = 0; j < n; ++j) {
            res.push_back(bucket[i][j]);
        }
    }
    return res;
}

int ActividadesGoloso:: buscarMaxBeneficio() {
    vector<int> aux = ordenarPorT();
    int ultimoT = -1, res = 0;
    for (int i = 0; i < _N; ++i) {
        if (_S[aux[i]] > ultimoT){
            res++;
            ultimoT = _T[aux[i]];
        }
    }
    return res;
}

vector<int> ActividadesGoloso:: construirRes() {
    vector<int> aux = ordenarPorT(), res;
    int ultimoT = -1;
    for (int i = 0; i < _N; ++i) {
        if (_S[aux[i]] > ultimoT){
            res.push_back(aux[i]);
            ultimoT = _T[aux[i]];
        }
    }
    return res;
}

void ActividadesGoloso:: ejer4_3() {
    cout<<buscarMaxBeneficio()<<endl;
    mostrarVector2(construirRes());
}
