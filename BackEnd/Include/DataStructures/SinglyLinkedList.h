#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <iostream>
#include <new>

namespace Singly {

    template <typename T>
    struct Node {
        T Data;                // Stored value | Valor armazenado
        Node<T>* Next;         // Pointer to next node | Ponteiro para o próximo node
    };
    
    template <typename T>
    struct List {
        Node<T>* Head;         // First element | Primeiro elemento
        int Size;              // Number of elements | Quantidade de elementos
    };
    
    template <typename T>
    List<T> Create() {
        return List<T>{ nullptr, 0 };
        // Create empty list | Criar lista vazia
    }

    template <typename T>
    bool IsEmpty(const List<T>& L) {
        return L.Size == 0;
        // True if list has no nodes | Verdadeiro se a lista estiver vazia
    }

    template <typename T>
    bool IsFull() {
        Node<T>* node = new (std::nothrow) Node<T>{};
        if (node) {
            delete node;
            return false;
        }
        std::cerr << "Error Allocating Memory!";
        return true;  
        // Check allocation failure | Verifica falha de alocação
    }

    template <typename T>
    void PushBack(List<T>* L, const T& value) {
        if (IsFull<T>()) return;

        Node<T>* node = new (std::nothrow) Node<T>{ value, nullptr };

        if (L->Size == 0) {
            L->Head = node;
        } else {
            Node<T>* curr = L->Head;
            while (curr->Next) {
                curr = curr->Next;
            }
            curr->Next = node;  
        }
        L->Size++;
        // Insert element at end | Inserir elemento no final
    }

    template <typename T>
    void PushFront(List<T>* L, const T& value) {
        if (IsFull<T>()) return;

        Node<T>* node = new (std::nothrow) Node<T>{ value, nullptr };

        node->Next = L->Head;
        L->Head = node;
        L->Size++;
        // Insert element at beginning | Inserir elemento no início
    }

    template <typename T>
    void PopFront(List<T>* L) {
        if (IsEmpty(*L)) return;

        Node<T>* tmp = L->Head;
        L->Head = L->Head->Next;
        delete tmp;
        L->Size--;
        // Remove first element | Remover o primeiro elemento
    }

    template <typename T>
    void PopBack(List<T>* L) {
        if (IsEmpty(*L)) return;
        
        if (L->Size == 1) {
            delete L->Head;
            L->Head = nullptr;
        } else {
            Node<T>* curr = L->Head;
            while (curr->Next->Next) {
                curr = curr->Next;
            }
            delete curr->Next;
            curr->Next = nullptr;
        }
        L->Size--;
        // Remove last element | Remover o último elemento
    }

    template <typename T>
    T GetAt(const List<T>& L, int pos) {
        if (pos < 1 || pos > L.Size) return T{};
        // Invalid index | Índice inválido

        Node<T>* curr = L.Head;

        for (int i = 1; i < pos; i++) {
            curr = curr->Next;
        }

        return curr->Data;
        // Return element at position | Retorna elemento da posição
    }

    template <typename T>
    void Clear(List<T>* L) {
        Node<T>* curr = L->Head;

        while (curr) {
            Node<T>* tmp = curr;
            curr = curr->Next;
            delete tmp;
        }
        L->Head = nullptr;
        L->Size = 0;
        // Clear entire list | Limpar toda a lista
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
        // Print list | Mostrar lista
    }

    template <typename T, typename Predicate>
    Node<T>* Find(List<T>& L, Predicate pred) {
        Node<T>* curr = L.Head;
        while (curr) {
            if (pred(curr->Data)) return curr;
            curr = curr->Next;
        }
        return nullptr;
        // Find node by condition | Encontrar node pela condição
    }

}

#endif
