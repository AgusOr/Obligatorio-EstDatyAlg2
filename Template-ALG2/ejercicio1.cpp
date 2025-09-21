#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/avl.cpp"
#include "tads/avlPuntaje.cpp"

using namespace std;

int main()
{        
    int n;
    cin >> n;

    bst<int> *arbolID = new avl<int>();
    bstPuntaje<int> *arbolPuntaje = new avlPuntaje<int>();

    for(int i = 0; i < n; i++){
        string operacion;
        cin >> operacion;

        if(operacion == "ADD"){
            int ID;
            int puntaje;
            string nombre;
            cin >> ID;
            cin >> nombre;
            cin >> puntaje;
            if(!arbolID ->contains(ID)){
            arbolID ->insert(ID,nombre , puntaje);
            arbolPuntaje ->insertPuntaje(puntaje,nombre,ID);
            }
        }

        if(operacion == "FIND"){
            int ID;
            cin >> ID;            
            cout << arbolID ->FIND(ID) << endl;
            
        }

        if(operacion == "RANK"){
            int puntaje;
            cin >> puntaje;            
            int r = arbolPuntaje ->RANK(puntaje);
            cout << r << endl;
        }

        if(operacion == "TOP1"){
           cout << arbolPuntaje ->TOP1() << endl;
        }

        if(operacion == "COUNT"){
            cout << arbolID ->size() << endl;
        }

    }

}