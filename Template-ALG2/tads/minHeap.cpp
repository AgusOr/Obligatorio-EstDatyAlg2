#pragma once

#include "./heap.cpp"
#include <assert.h>
#include <iostream>
#include "ListImp.cpp"

template <class T>
class min_heap : public heap<T>
{

private:
  List<T>** heap;
  int cantElem;
  int tope;

  T elem(int index) {
    assert(this->cantElem >=1);
    return heap[index]->get(0);
  }

    void swap(int i, int j){
        List<T>* temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void siftUp(int pos) {
    if (pos <= 1){
        return;
    }
    int parent = pos / 2;
    if (elem(pos) >= elem(parent)){
      return;
    }
    else{
      if (elem(pos) < elem(parent)){
        //arr[pos] = parentPair;
        //arr[parent] = p;
        swap(pos, parent);
        siftUp(parent);
      }
    }

  }

   void siftDown(int pos) {
    if(pos*2 > this->cantElem){
      return;
    }
    int parent = pos;
    int hijoIzq = pos*2;
    int hijoDer = pos*2 + 1;
    int hijoMenor = hijoIzq;
    if(hijoDer <= this->cantElem && elem(hijoDer) < elem(hijoIzq)){
      hijoMenor = hijoDer;
    }
    if(elem(parent) > elem(hijoMenor)){
      //arr[pos] = hijoMayorPair;
      //arr[hijoMayor] = parent;
      swap(pos, hijoMenor);
      siftDown(hijoMenor);
      }
    }



public:
  min_heap(int expectedSize)
  {
    this->heap = new List<T>*[expectedSize + 1];
    this->cantElem = 0;
    this->tope = 1;
  }

  virtual void push(List<T>* nuevaLista) override
  {
    heap[tope] = nuevaLista;
    siftUp(tope);
    this->cantElem++;
    this->tope++;
  }

  virtual void pop() override
  {
    assert(this->cantElem >= 1);
    swap(1,tope-1);
    if(!heap[tope-1]->isEmpty()){
      heap[tope-1]->removeAt(0);
      
    }
    if(heap[tope-1]->isEmpty()){
      heap[tope-1] =heap[cantElem];
      heap[cantElem] = NULL;
      cantElem--;
      tope--;
    }
    
    siftDown(1);
    siftUp(tope-1);
  }

  virtual T top() override
  {
    assert(this->cantElem >= 1);
    return heap[1]->get(0);
  }

  virtual int size() override
  {
    return this->cantElem;
  }

  virtual bool isEmpty() override
  {
    return this->cantElem == 0;
  }
};