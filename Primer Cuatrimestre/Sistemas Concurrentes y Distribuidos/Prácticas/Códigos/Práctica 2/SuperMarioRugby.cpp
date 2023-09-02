#include <iostream>
#include <iomanip>
#include <cassert>
#include <random>
#include <thread>
#include <vector>
#include "scd.h"

using namespace std ;
using namespace scd ;
/*

g++ -std=c++11 -pthread -I. -o jueguito SuperMarioRugby.cpp scd.cpp*/
//////////////////////////////////////////////////
//Creo la clase del campo
/*
    V- casilla vacía
    A-B-C-D jugador (1-4)
    X enemigo
*/
class Field{
    private:
        vector<vector<char>> matrix;

    public:
        Field(int n);
        void Render();
};
//Constructor
Field::Field(int n){
    for(int i=0; i<n; i++)
    {
        vector<int> fila (n, 'V');
        matrix.push(fila);
    }
}

void Field::Render()
{
    for(vector<vector<int>>::iterator it = matrix.begin(); it!=matrix.end(); ++it) {
        //for(vector<int>::iterator j = it->begin(); j!=it->end(); ++j)
        //    cout << *j;
        cout << endl;
        } 
}


int main(){
    Field gameField(10);
    gameField.Render();
    return(0);
}
