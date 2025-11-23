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
        return List<T>{nullptr, 0};
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
        std::cerr << "Error Allocating Memory!";
        return true;
    }

    template <typename T>
    void PushBack(List<T>* L, const T& value){
        if (IsFull<T>()) return;

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
    void PushFront(List<T>* L, const T& value){
        if (IsFull<T>()) return;

        Node<T>* node = new (std::nothrow) Node<T>{value, nullptr};

            node->Next = L->Head;
            L->Head = node;
        L->Size++;
    }

    template <typename T>
    void PopFront(List<T>* L){
        if (IsEmpty(*L)) return;

        Node<T>* tmp = L->Head;
        L->Head = L->Head->Next;
        delete tmp;
        L->Size--;
    }

    template <typename T>
    void PopBack(List<T>* L){
        if (IsEmpty(*L)) return;
        
        if (L->Size == 1){
            delete L->Head;
            L->Head = nullptr;
        }
        else{
            
            Node<T>* curr = L->Head;
            while (curr->Next->Next){
                curr = curr->Next;
            }
            
            delete curr->Next;
            curr->Next = nullptr;
        }
        L->Size--;
    }

    template <typename T>
    T GetAt(const List<T>& L, int pos){
        if (pos < 1 || pos > L.Size) return T{};

        Node<T>* curr = L.Head;

        for (int i=1; i<pos; i++){
            curr = curr->Next;
        }

        return curr->Data;
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

    template <typename T>
    void Display(const List<T>& L) {
        Node<T>* curr = L.Head;
        while (curr) {
            std::cout << curr->Data;
            if (curr->Next) std::cout << " -> ";
            curr = curr->Next;
        }
        std::cout << " -> nullptr\n";
    }


}

#endif