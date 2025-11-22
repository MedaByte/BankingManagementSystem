#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <iostream>
#include <new>

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
    List<T> Create(){
        List<T> L;
        L.Head = nullptr;
        L.Size = 0;
        return L;
    }

    template <typename T>
    bool IsEmpty(const List<T>& L){
        return L.Size == 0;
    }

    template <typename T>
    bool IsFull(){
        Node<T>* node = new (std::nothrow) Node<T>{};
        if (node){
            delete node;
            return false;
        }
        return true;
    }

    template <typename T>
    void PushBack(List<T>* L, const T& value){
        if (IsFull()){
            return;
        }

        Node<T>* node = new (std::nothrow) Node<T>{value, nullptr};

        if (L->Size == 0){
            L->Head = node;
        }
        else{
            Node<T>* curr = L->Head;
            while (curr->Next){
                curr = curr->Next;
            }
            curr->Next = node;  
        }
        L->Size++;
    }

    template <typename T>
    void PopFront(List<T>* L){
        if (L->Size == 0) return;

        Node<T>* tmp = L->Head;
        L->Head = L->Head->Next;
        delete tmp;
        L->Size--;
    }

    template <typename T>
    void Clear(List<T>* L){
        Node<T>* curr = L->Head;

        while (curr){
            Node<T>* tmp = curr;
            curr = curr->Next;
            delete tmp;
        }
        L->Head = nullptr;
        L->Size = 0;
    }
    
}

#endif