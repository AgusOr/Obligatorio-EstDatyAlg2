#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "avl.cpp"
#include "avlPuntaje.cpp"

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
            arbolID ->insert(ID,nombre , puntaje);
            arbolPuntaje ->insertPuntaje(puntaje,nombre,ID);
        }

        if(operacion == "FIND"){
            int ID;
            cin >> ID;            
            arbolID ->contains(ID);
        }

        if(operacion == "RANK"){
            int puntaje;
            cin >> puntaje;            
            arbolPuntaje ->RANK(puntaje);
        }

        if(operacion == "TOP1"){
            arbolPuntaje ->TOP1();
        }

        if(operacion == "COUNT"){
            cout << arbolID ->size() << endl;
        }

    }

}