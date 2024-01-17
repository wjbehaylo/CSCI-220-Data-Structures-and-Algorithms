/*
 * stack.h
 *
 * Implements a simple stack class using dynamic arrays.
 * This may be implemented in 3 stages:
 *   Stage 1: non-template stack class storing strings,
 *            unsafe copies/assignments
 *   Stage 2: template stack class, unsafe copies/assignments
 *   Stage 3: template stack class, safe copies/assignments
 *
 * Note: no underflow detection is performed.  Performing pop() or top()
 * on an empty stack results in undefined behavior (possibly crashing your
 * program)!
 *
 * Author: Your Name
 */

#ifndef _STACK_H
#define _STACK_H

#include <cstddef> // for size_t
#include <string>  // for stage 1

using namespace std;

template <typename T>
class stack{
  public:
    T top(); // non-inline, implemented in stack-stage1.cpp

    // inline definitions, doing nothing at the moment
    void push(const T & new_element);
    void pop();
    size_t size() { return stack_size; }
    bool is_empty();

    stack();

    ~stack(){
        delete[] _data;
    }

    stack(const stack<T>& orig){
        stack_size = orig.stack_size;
        stack_capacity = orig.stack_capacity;
        _data = new T[stack_capacity];

        for(int i = 0; i<stack_size;i++){
            _data[i] = orig._data[i];
        }
    }
    stack& operator=(const stack& orig){
        if(this == &orig) return *this;
        delete[] _data;
        stack_size = orig.stack_size;
        stack_capacity = orig.stack_capacity;
        _data = new T[stack_capacity];
        for(int i = 0; i<stack_size; i++){
            _data[i] = orig._data[i];
        }
        return *this;
    }

  private:
    T* _data;
    size_t stack_size;
    size_t stack_capacity;
};

template<typename T>
T stack<T>::top() {
    return _data[stack_size-1];
}

template<typename T>
void stack<T>::push(const T& new_element){
    if(stack_size == stack_capacity){
        T* new_array = new T[stack_capacity*2];
        for(int i = 0; i<stack_size; i++){ //copy old array
            new_array[i] = _data[i];
        }
        delete[] _data;
        _data = new_array;
        stack_capacity *=2;
    }
    _data[stack_size] = new_element;
    stack_size++; //grow the size of the stack because it had something added
}

template <typename T>
void stack<T>::pop(){
    if(stack_size == 0) return; //if the stack is empty, nothing happens
    stack_size--; //shrink the size of the stack because it had something removed
}

template <typename T>
bool stack<T>::is_empty(){
    if (stack_size ==0){
        return true;
    }
    else return false;
}

template <typename T>
stack<T>::stack(){
    stack_size = 0; //initially a stack is empty
    stack_capacity = 1;
    _data = new T[1]; //so it points to nothing
}

#endif