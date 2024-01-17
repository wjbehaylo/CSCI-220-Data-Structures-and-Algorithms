/*
 * stack.cpp
 *
 * Method definitions for the stack implementation.
 *
 * Author: Your Name
 */

#include "stack-stage1.h"

string stack::top() {
    return _data[stack_size-1];
}

void stack::push(const string& new_element){
    if(stack_size == stack_capacity){
        string* new_array = new string[stack_capacity*2];
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

void stack::pop(){
    if(stack_size == 0) return; //if the stack is empty, nothing happens
    stack_size--; //shrink the size of the stack because it had something removed
}

bool stack::is_empty(){
    if (stack_size ==0){
        return true;
    }
    else return false;
}

stack::stack(){
    stack_size = 0; //initially a stack is empty
    stack_capacity = 1;
    _data = new string[1]; //so it points to nothing
}