#ifndef STACK_H
#define STACK_H

/** 
 * Your Stack<T> class must be templated and
 * privately inherit from LList<T>. All
 * operations must run in O(1).
 *
 * Both pop() and top() must throw std::underflow_error
 * if the stack is empty.
 */


//linked list into stack
#include <stdexcept>
#include "llist.h"

template <typename T>
class Stack:private LList<T> // complete the declaration and implementation  
//last in first out
{
    public:
        Stack();
        size_t size() const;
        bool empty() const;
        void push(const T& item);
        void pop();
        T const & top() const;

};

//creates stack
template <typename T>
Stack<T>::Stack():LList<T>(){
}



//if empty
template <typename T>
bool Stack<T>::empty() const{
    return LList<T>::empty();
}

//add item to top
template <typename T>
void Stack<T>::push(const T& item){
    LList<T>::push_front(item);
}

//size of stack
template <typename T>
size_t Stack<T>::size() const{
    return LList<T>::size();
}

//remove top item 
template <typename T>
void Stack<T>::pop(){
    LList<T>::remove(0);
}


//returns top item
template <typename T>
T const & Stack<T>::top() const{
    return (LList<T>::operator[](0));
}











#endif
