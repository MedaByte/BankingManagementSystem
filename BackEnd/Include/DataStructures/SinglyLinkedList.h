#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <iostream>

namespace Singly{

    template <typename T>
    struct Node
    {
        T Data;
        Node<T>* Next;
    };
    
    template <typename T>
    struct List
    {
        Node<T>* Head;
        int Size;
    };
    
    template <typename T>
    List<T> CreateList(){
        
    }
}

#endif