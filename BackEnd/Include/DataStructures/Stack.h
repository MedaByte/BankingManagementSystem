#ifndef STACK_H
#define STACK_H

#include "SinglyLinkedList.h"


namespace Stack{

    template <typename T>
    struct Stack
    {
        Singly::List List;

    };

    template <typename T>
    Stack<T> Create(){
        return Stack<T>{Singly::Create<T>()};
    }

    template <typename T>
    bool IsEmpty(const Stack<T>& S){
        return Singly::IsEmpty(&S.List);
    }

    template <typename T>
    void Push(Stack<T>* S, T value){
        Singly::PushFront(S->List, value);
    }
    
    
}

#endif