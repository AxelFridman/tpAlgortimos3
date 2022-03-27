#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
using namespace std;
void visualizarVector(const vector<int> v){
    for(int i=0;i<v.size();i++){
        std :: cout << " "<<v[i] ;
    }
    std :: cout << " "<< endl ;
}
void visualizarMatriz(vector<vector<int> > v){
    std :: cout << "--------"<<endl ;
    for(int i=0;i<v.size();i++){
        visualizarVector(v[i]) ;
    }
    std :: cout << "--------"<<endl ;
}
int main() {
    tuple<int, string> tup = make_tuple(13,"hola prueba");
    std::cout << get<1>(tup) << std::endl;
    std::cout << "Hola mundo" << std::endl;
    return 0;
}
