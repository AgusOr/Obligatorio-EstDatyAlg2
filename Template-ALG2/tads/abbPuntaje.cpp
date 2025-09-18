#pragma once

template <class T>
class bstPuntaje
{
public:
  virtual void insertPuntaje(T puntaje,string nombre, int ID) = 0;

  virtual void remove(T puntaje) = 0;

  virtual int height() = 0;

  virtual int size() = 0;

  virtual bool contains(T puntaje) = 0;

  virtual T get(T puntaje) = 0;

  virtual T min() = 0;

  virtual T max() = 0;

  virtual void RANK(int puntaje) = 0; 

  virtual maxPuntaje TOP1() = 0;
};