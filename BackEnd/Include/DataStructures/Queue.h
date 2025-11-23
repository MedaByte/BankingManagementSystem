#ifndef QUEUE_H
#define QUEUE_H

#include "SinglyLinkedList.h"

namespace Queue{
    template <typename T>
    struct Queue
    {
        Singly::List<T> List;

    };

    template <typename T>
    Queue<T> Create(){
        return Queue<T>{Singly::Create<T>()};
    }

    template <typename T>
    bool IsEmpty(const Queue<T>& Q){
        return Singly::IsEmpty(Q.List);
    }

    template <typename T>
    void Enqueue(Queue<T>* Q,const T& value){
        Singly::PushBack(&Q->List, value);
    }
    
    template <typename T>
    void Dequeue(Queue<T>* Q){
        Singly::PopFront(&Q->List);
    }

    template <typename T>
    T Front(const Queue<T>& Q){
        return Singly::GetAt(Q.List, 1);
    }

    template <typename T>
    T Back(const Queue<T>& Q){
        return Singly::GetAt(Q.List, Q.List->Size);
    }

    template <typename T>
    void Clear(Queue<T>* Q){
        Singly::Clear(&Q->List);
    }
}
#endif