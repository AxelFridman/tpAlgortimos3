
#ifndef TPJUANEJ1_RED_H
#define TPJUANEJ1_RED_H


#include <vector>
#include <fstream>
#include <set>
#include <list>

using namespace std;

class Red {
public:
    Red(string);
    set<int> usuarios();
    bool sonAmigos(int, int);
    int cantUsuarios();
    int cantAmistades();
    int p(int);
    bool esClique(list<int>&);

private:
    int _N;
    int _M;
    vector<vector<bool> > _Amistades;
    vector<int> _p;

};
#endif //BACKTRACKING_RED_H
