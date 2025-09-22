#pragma once
#include <assert.h>
#include "abbPuntaje.cpp"
#include <stdexcept>
#include <string>

template <class T>
class avlPuntaje : public bstPuntaje<T>
{
private:
  struct avl_node
  {
    T puntaje;
    std::string nombre;
    int ID;
    int height = 1;
    int cantSubarbol = 1;
    avl_node *left = nullptr;
    avl_node *right = nullptr;

    avl_node(T puntaje, std::string nombre = "", int ID = 0)
    {
      this->puntaje = puntaje;
      this->nombre = nombre;
      this->ID = ID;
    }
  };
  avl_node *maxNodePtr = nullptr; 
  avl_node *root;
  int count = 0;

  int max(int a, int b)
  {
    if (a > b)
    {
      return a;
    }
    return b;
  }

  int height(avl_node *n)
  {
    if (n == nullptr)
    {
      return 0;
    }

    return n->height;
  }

  T minNode(avl_node *n)
  {
    assert(n != nullptr);

    if (n->left != nullptr)
    {
      return minNode(n->left);
    }
    else
    {
      return n->puntaje;
    }
  }

  T maxNode(avl_node *n)
  {
    assert(n != nullptr);

    if (n->right != nullptr)
    {
      return maxNode(n->right);
    }
    else
    {
      return n->puntaje;
    }
  }

  avl_node *leftRotation(avl_node *z){
    avl_node *y = z->right;
    avl_node *T2 = y->left;

    y->left = z;
    z->right = T2;

    z->height = 1 + max(height(z->left), height(z->right));
    z->cantSubarbol = cantSubarbol(z);
    y->height = 1 + max(height(y->left), height(y->right));
    y->cantSubarbol = cantSubarbol(y);
    
    return y;
  }

  avl_node *leftRightRotation(avl_node *z){
    z->left = leftRotation(z->left);
    return rightRotation(z);
  }

  avl_node *rightRotation(avl_node *z){
    avl_node *y = z->left;
    avl_node *T3 = y->right;

    y->right = z;
    z->left = T3;

    z->height = 1 + max(height(z->left), height(z->right));
    z->cantSubarbol = cantSubarbol(z);
    y->height = 1 + max(height(y->left), height(y->right));
    y->cantSubarbol = cantSubarbol(y);

    return y;
  }

  avl_node *rightLeftRotation(avl_node *z){
    z->right = rightRotation(z->right);
    return leftRotation(z);
  }

  avl_node *rebalance(avl_node *n)
  {
    int bF = height(n->left) - height(n->right);

    if (bF < -1)
    { // desbalance der-?
      avl_node *aux = n->right;
      bF = height(aux->left) - height(aux->right);

      if (bF < 0)
      { // desbalance der-der
        n = leftRotation(n);
      }
      else
      { // desbalance der-izq
        // bF > 0
        n = rightLeftRotation(n);
      }
    }
    else if (bF > 1)
    { // desbalance izq-?
      avl_node *aux = n->left;
      bF = height(aux->left) - height(aux->right);

      if (bF < 0)
      { // desbalance izq-der
        n = leftRightRotation(n);
      }
      else
      { // desbalance izq-izq
        // bF > 0
        n = rightRotation(n);
      }
    }

    return n;
  }

  avl_node *insertP(T puntaje,std::string nombre, int ID, avl_node *n)
  {

    if (n == nullptr)
    {
      this->count++;
      avl_node *nuevo = new avl_node(puntaje,nombre,ID);
      if(!maxNodePtr || puntaje > maxNodePtr->puntaje || (puntaje == maxNodePtr->puntaje && ID < maxNodePtr->ID)){
        maxNodePtr = nuevo;
      }
      return nuevo;
    }

    if (puntaje < n->puntaje)
    {
      n->left = insertP(puntaje,nombre,ID, n->left);
    }
    else if (puntaje > n->puntaje)
    {
      n->right = insertP(puntaje,nombre,ID, n->right);
    }
    // a diferencia del arbol por ID, pueden haber puntajes iguales, en esos casos compara por ID
    else{
      if(ID < n->ID){
        n->left = insertP(puntaje,nombre,ID, n->left);
      }
      else if(ID > n->ID){
        n->right = insertP(puntaje,nombre,ID, n->right);
      }
    }

    n->height = 1 + max(height(n->left), height(n->right));
    n->cantSubarbol = cantSubarbol(n);
    n = rebalance(n);
    return n;
  }
  // funcion que calcula cantidad de nodos del subarbol
  // se usa cada vez que insertamos y rebalanceamos, necesaria para rank
  int cantSubarbol(avl_node *n){
    if(n == NULL){
      return 0;
    }    
    int cant = 1;
    if (n->left){
      cant += n->left->cantSubarbol;
    }
    if(n->right){
      cant += n->right->cantSubarbol;
    }
    return cant;
  }
  
  std::string contains(T puntaje, avl_node *n){
    if (n == nullptr)
    {
      return "jugador_no_encontrado";
    }

    if (puntaje == n->puntaje)
    {
      return n->nombre + " " + std::to_string(n->puntaje);
    }

    if (puntaje < n->puntaje)
    {
      return contains(puntaje, n->left);
    }
    else if (puntaje > n->puntaje)
    {
      return contains(puntaje, n->right);
    }
  
    // unreachable code
    assert(false);
  }


  int rankRec(avl_node *n, int puntaje){

    if(n==nullptr){
      return 0;
    }
    if(n->puntaje < puntaje){
      return rankRec(n->right,puntaje);
    }
    if(n->puntaje >= puntaje){
      if(n->right){
        return 1 + n->right->cantSubarbol + rankRec(n->left,puntaje);
      }
      else{
        return 1 + rankRec(n->left,puntaje);
      }
    }
  }

  

public:
  avlPuntaje(){
    this->root = nullptr;
  }
  virtual void insertPuntaje(T puntaje,std::string nombre,int ID) override
  {
    this->root = insertP(puntaje,nombre, ID, this->root);
  } 

  virtual void remove(T puntaje) override
  {
    // TODO Auto-generated method stub
  }

  virtual int height() override
  {
    return height(this->root);
  }

  virtual int size() override
  {
    return this->count;
  }

  virtual std::string contains(T puntaje) override
  {
    return contains(puntaje, this->root);
  }

  virtual T get(T puntaje) override
  {
    // TODO Auto-generated method stub
  }

  virtual T min() override
  {
    return minNode(this->root);
  }

  virtual T max() override
  {
    return maxNode(this->root);
  }

  virtual int RANK(int puntaje) override
  {
    return rankRec(this->root, puntaje);
    
  }
  virtual std::string TOP1() override
  {
    if (!this->maxNodePtr) {
      throw std::runtime_error("No hay jugadores");
    }
    return this->maxNodePtr->nombre + " " + std::to_string(this->maxNodePtr->puntaje);
  }
};