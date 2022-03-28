//
// Created by juan on 26/3/22.
//

#ifndef BACKTRACKING_RED_H
#define BACKTRACKING_RED_H
#include <vector>
//#include <map>
#include <fstream>
//#include <algorithm>
#include <set>
//#include <boost/date_time.hpp>

using namespace std;

class Red {
    public:
            Red(string);
            set<int> usuarios();
            bool sonAmigos(int, int);
            int cantUsuarios();
            int cantAmistades();
            int p(int);
            bool esClique(set<int>&);

    private:
            int _N;
            int _M;
            vector<vector<bool> > _Amistades;
            vector<int> _p;

};
#endif //BACKTRACKING_RED_H
