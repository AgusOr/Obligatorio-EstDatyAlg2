#pragma once
#include <assert.h>
#include "abb.cpp"
#include <stdexcept>

template <class T>
class avl : public bst<T>
{
private:
  struct avl_node
  {
    T ID;
    string nombre;
    int puntaje;
    int height = 1;
    avl_node *left = nullptr;
    avl_node *right = nullptr;

    avl_node(T ID, string nombre = "", int puntaje = 0)
    {
      this->ID = ID;
      this->nombre = nombre;
      this->puntaje = puntaje;
    }
  };

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
      return n->ID;
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
      return n->ID;
    }
  }

  avl_node *leftRotation(avl_node *z){
    avl_node *y = z->right;
    avl_node *T2 = y->left;

    y->left = z;
    z->right = T2;

    z->height = 1 + max(height(z->left), height(z->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
  }

  avl_node *leftRightRotation(avl_node *z){
    z->left = leftRotation(z->left);
    return rightRotation(z);
  }

  avl_node *rightRotation(avl_node *z){
    avl_node *y = z->left;
    avl_node *T3 = z->right;

    y->right = z;
    y->left = T3;

    z->height = 1 + max(height(z->left), height(z->right));
    y->height = 1 + max(height(y->left), height(y->right));

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

  avl_node *insertID(T ID,string nombre, int puntaje avl_node *n) override
  {
    if(contains(ID)){
      return;
    }

    if (n == nullptr)
    {
      this->count++;
      return new avl_node(ID);
    }

    if (ID < n->ID)
    {
      n->left = insertID(ID, n->left);
    }
    else if (ID > n->ID)
    {
      n->right = insertID(ID, n->right);
    }

    n->height = 1 + max(height(n->left), height(n->right));
    n = rebalance(n);
    return n;
  }

  bool contains(T ID, avl_node *n){
    if (n == nullptr)
    {
      return false;
    }

    if (ID == n->ID)
    {
      return true;
    }

    if (ID < n->ID)
    {
      return contains(ID, n->left);
    }
    else if (ID > n->ID)
    {
      return contains(ID, n->right);
    }
  
    // unreachable code
    assert(false);
  }

  virtual void RANK(int puntaje) override
  {
    // TODO Auto-generated method stub
  }
  virtual void TOP1() override  
  {
    // TODO Auto-generated method stub
  }

public:
  avl(){
    this->root = nullptr;
  }
  virtual void insert(T ID,string nombre,int puntaje) override
  {
    this->root = insertID(ID,nombre, puntaje, this->root);
  } 

  virtual void remove(T ID) override
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

  virtual bool contains(T ID) override
  {
    return contains(ID, this->root);
  }

  virtual T get(T ID) override
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
  
  virtual void RANK(int puntaje) override
  {
    // TODO Auto-generated method stub
  }
  virtual void TOP1() override
  {
    // TODO Auto-generated method stub
  }
};