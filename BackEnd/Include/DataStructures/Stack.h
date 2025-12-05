#ifndef STACK_H
#define STACK_H

#include "SinglyLinkedList.h"

namespace Stack {

    template <typename T>
    struct Stack
    {
        Singly::List<T> List; 
        // Underlying list | Lista base
    };

    template <typename T>
    Stack<T> Create() {
        return Stack<T>{ Singly::Create<T>() };
        // Create empty stack | Criar stack vazio
    }

    template <typename T>
    bool IsEmpty(const Stack<T>& S) {
        return Singly::IsEmpty(S.List);
        // Check if empty | Verificar se está vazio
    }

    template <typename T>
    void Push(Stack<T>* S, const T& value) {
        Singly::PushFront(&S->List, value);
        // Push on top | Empurrar no topo
    }
    
    template <typename T>
    void Pop(Stack<T>* S) {
        Singly::PopFront(&S->List);
        // Remove top element | Remover elemento do topo
    }

    template <typename T>
    T& Top(Stack<T>& S) {
        return S.List.Head->Data;
        // Access top | Acessar topo
    }

    template <typename T>
    const T& Top(const Stack<T>& S) {
        return S.List.Head->Data;
        // Access top (const) | Acessar topo (const)
    }
    
    template <typename T>
    void Clear(Stack<T>* S) {
        Singly::Clear(&S->List);
        // Clear stack | Limpar stack
    }
    
    template <typename T>
    void Display(const Stack<T>& S) {
        Singly::Display(S.List);
        // Display stack | Mostrar stack
    }

}

#endif
