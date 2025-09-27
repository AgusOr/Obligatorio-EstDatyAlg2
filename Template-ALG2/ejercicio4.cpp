#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/minHeap.cpp"
#include "tads/ListImp.cpp"

using namespace std;


int main()
{
    int cantListas;
    cin >> cantListas;
    min_heap<int> heap(cantListas);
    for(int i = 0; i < cantListas; i++){
        int cantElemLista;
        cin >> cantElemLista;
        List<int>* lista = new ListImp<int>();
        for(int j = 0; j < cantElemLista; j++){
            int elem;
            cin >> elem;
            lista->insert(elem);
        }
        heap.push(lista);
    }
    while(!heap.isEmpty()){
        heap.pop();
        cout << heap.top() << endl;
    }
    cout << endl;
}