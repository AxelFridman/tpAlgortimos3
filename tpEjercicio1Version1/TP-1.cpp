#include <set>
#include <vector>
#include "red.h"
#include <iostream>
#include "TP-1.h"
using namespace std;

int infl_max;
set<int> Q_max;

void ejercicio1(Red& red){
    set<int> Q, K = red.usuarios();
    int infl = 0;
    infl_max = 0;
    Q_max.clear();
    buscarMaxInfl (Q, K, infl, red);
    cout<<"Influencia maxima es: "<<infl_max<<endl;
    cout<<"La clique mas influyencte: ";
    for (int i: Q_max)
        cout<<i<<" ";
    cout<<endl;
}

void buscarMaxInfl (set<int>& Q, set<int>& K, int infl, Red& red){
    /*cout<<"-------------------"<<endl<<"Q= ";
    for (int i: Q)
        cout<<i<<" ";
    cout<<endl;
    cout<<"K= ";
    for (int i: K)
        cout<<i<<" ";
    cout<<endl;*/
    if(K.empty()){
        if (infl > infl_max){
            infl_max = infl;
            Q_max = Q;
        }
    } else{
        int v = maxInfl(K);
        //cout<<"v: "<<v<<endl;
        set<int> Qi = Q;
        Qi.insert(v);
        set<int> Ki = amigosDexEnY(v,K, red);
        //cout<<"v: "<<v<<endl;
        int infli = infl + red.p(v);
        if (red.esClique(Ki)){
            infli += pasar(Qi, Ki, red);
        }
        /*cout<<"Qi= ";
        for (int i: Qi)
            cout<<i<<" ";
        cout<<endl;
        cout<<"Ki= ";
        for (int i: Ki)
            cout<<i<<" ";
        cout<<endl;*/
        if (red.esClique(K)){
            infl += pasar(Q,K,red);
        }
        /*cout<<"Qd= ";
        for (int i: Q)
            cout<<i<<" ";
        cout<<endl;
        cout<<"Kd= ";
        for (int i: K)
            cout<<i<<" ";
        cout<<endl;*/
        buscarMaxInfl(Qi, Ki, infli,red);
        buscarMaxInfl(Q, K, infl,red);
    }
}

int maxInfl(set<int>& K){
    set<int>::iterator it = K.begin();
    int res = *it;
    K.erase(it);
    return res;
}

set<int> amigosDexEnY(int v, set<int>& K, Red& red){
    set<int> res;
    for (int i: K) {
        if (red.sonAmigos(v,i))
            res.insert(i);
    }
    return res;
}

int pasar(set<int>& Qi, set<int>& Ki, Red& red){
    int res = 0;
    set<int>:: iterator it;
    for (it = Ki.begin(); it != Ki.end(); ++it){
        //cout<<"i: "<<*it<<endl;
        res += red.p(*it);
        Qi.insert(*it);
    }
    Ki.clear();
    return res;
}