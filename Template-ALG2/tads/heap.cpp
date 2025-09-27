#pragma once

template <class T> class List;
template <class T>
class heap
{
public:
  virtual void push(List<T>* lst) = 0;

  virtual void pop() = 0;

  virtual T top() = 0;

  virtual int size() = 0;

  virtual bool isEmpty() = 0;

};