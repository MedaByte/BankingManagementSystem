#ifndef STACK_H
#define STACK_H

#include "SinglyLinkedList.h"


namespace Stack{

    template <typename T>
    struct Stack
    {
        Singly::List<T> List;

    };

    template <typename T>
    Stack<T> Create(){
        return Stack<T>{Singly::Create<T>()};
    }

    template <typename T>
    bool IsEmpty(const Stack<T>& S){
        return Singly::IsEmpty(S.List);
    }

    template <typename T>
    void Push(Stack<T>* S,const T& value){
        Singly::PushFront(&S->List, value);
    }
    
    template <typename T>
    void Pop(Stack<T>* S){
        Singly::PopFront(&S->List);
    }

    template <typename T>
    T& Top(Stack<T>& S){
        return S.List.Head->Data;
    }

    template <typename T>
    const T& Top(const Stack<T>& S){
        return S.List.Head->Data;
    }
    
    template <typename T>
    void Clear(Stack<T>* S){
        Singly::Clear(&S->List);
    }
    
    template <typename T>
    void Display(const Stack<T>& S){
        Singly::Display(S.List);
    }
}

#endif