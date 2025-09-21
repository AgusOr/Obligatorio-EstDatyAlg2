#pragma once

template <class T>
class bst
{
public:
  virtual void insert(T ID,std::string nombre, int puntaje) = 0;

  virtual void remove(T ID) = 0;

  virtual int height() = 0;

  virtual int size() = 0;

  virtual bool contains(T ID) = 0;

  virtual std::string FIND(T ID) = 0;

  virtual T get(T ID) = 0;

  virtual T min() = 0;

  virtual T max() = 0;

};