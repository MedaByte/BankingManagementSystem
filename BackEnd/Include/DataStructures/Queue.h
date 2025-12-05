#ifndef QUEUE_H
#define QUEUE_H

#include "SinglyLinkedList.h"

namespace Queue {

    template <typename T>
    struct Queue {
        Singly::List<T> List;   // Underlying Singly Linked List | Lista Singly Linked List usada internamente
    };

    template <typename T>
    Queue<T> Create() {
        return Queue<T>{ Singly::Create<T>() };
        // Create empty queue | Criar uma queue vazia
    }

    template <typename T>
    bool IsEmpty(const Queue<T>& Q) {
        return Singly::IsEmpty(Q.List);
        // True if queue has no elements | Verdadeiro se a queue estiver vazia
    }

    template <typename T>
    void Enqueue(Queue<T>* Q, const T& value) {
        Singly::PushBack(&Q->List, value);
        // Insert element at back (FIFO) | Inserir elemento no final (FIFO)
    }
    
    template <typename T>
    void Dequeue(Queue<T>* Q) {
        Singly::PopFront(&Q->List);
        // Remove element from front | Remover elemento do início
    }

    template <typename T>
    T Front(const Queue<T>& Q) {
        return Singly::GetAt(Q.List, 1);
        // Get first element | Pegar o primeiro elemento
    }

    template <typename T>
    T Back(const Queue<T>& Q) {
        return Singly::GetAt(Q.List, Q.List->Size);
        // Get last element | Pegar o último elemento
    }

    template <typename T>
    void Clear(Queue<T>* Q) {
        Singly::Clear(&Q->List);
        // Clear entire queue | Limpar toda a queue
    }

    template <typename T>
    void Display(const Queue<T>& Q) {
        Singly::Display(Q.List);
        // Print queue elements | Mostrar elementos da queue
    }

}

#endif
