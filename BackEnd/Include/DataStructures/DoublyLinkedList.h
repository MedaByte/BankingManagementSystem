#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>
#include <new>

namespace Doubly {

    template <typename T>
    struct Node {
        T Data;
        Node<T>* Next;
        Node<T>* Prev;
    };

    template <typename T>
    struct List {
        Node<T>* Head;
        Node<T>* Tail;
        int Size;
    };
    
    template <typename T>
    List<T> Create() {
        return List<T>{nullptr, nullptr, 0};
    }

    template <typename T>
    bool IsEmpty(const List<T>& L) {
        return L.Size == 0; 
        // Check if list contains no elements | Verifica se a lista não contém elementos
    }

    template <typename T>
    bool IsFull() {
        Node<T>* node = new (std::nothrow) Node<T>{};
        if (node) {
            delete node;
            return false; 
        }
        std::cerr << "Error Allocating Memory!"; 
        // Memory allocation failed | Falha ao alocar memória
        return true;
    }

    template <typename T>
    void PushBack(List<T>* L, const T& value) {
        if (IsFull<T>()) return;

        Node<T>* node = new (std::nothrow) Node<T>{value, nullptr, nullptr};

        if (L->Size == 0) {
            L->Head = node; 
            L->Tail = node;
            // First element inserted | Primeiro elemento inserido
        } else {
            node->Prev = L->Tail;
            L->Tail->Next = node;
            L->Tail = node;
            // Insert at end | Inserir no final
        }
        L->Size++;
    }

    template <typename T>
    void PushFront(List<T>* L, const T& value) {
        if (IsFull<T>()) return;

        Node<T>* node = new (std::nothrow) Node<T>{value, nullptr, nullptr};

        if (L->Size == 0) {
            L->Head = node;
            L->Tail = node;
            // First element | Primeiro elemento
        } else {
            node->Next = L->Head;
            L->Head->Prev = node;
            L->Head = node;
            // Insert at beginning | Inserir no início
        }
        L->Size++;
    }

    template <typename T>
    void PopFront(List<T>* L) {
        if (IsEmpty(*L)) return;

        Node<T>* tmp = L->Head;
        L->Head = L->Head->Next;

        if (L->Head)
            L->Head->Prev = nullptr;
        else
            L->Tail = nullptr;

        delete tmp;
        L->Size--;
        // Remove first element | Remove o primeiro elemento
    }

    template <typename T>
    void PopBack(List<T>* L) {
        if (IsEmpty(*L)) return;

        if (L->Size == 1) {
            delete L->Head;
            L->Head = nullptr;
            L->Tail = nullptr;
            // List becomes empty | Lista fica vazia
        } else {
            Node<T>* tmp = L->Tail;
            L->Tail = tmp->Prev;
            L->Tail->Next = nullptr;
            delete tmp;
            // Remove last element | Remove o último elemento
        }
        L->Size--;
    }

    template <typename T>
    void RemoveAt(List<T>* L, int pos) {

        if (pos < 1 || pos > L->Size) return; 

        if (pos == 1) {

            PopFront(L);
            return;
        }
        if (pos == L->Size) {

            PopBack(L);
            return;
        }


        Node<T>* curr = nullptr;

        if (pos < L->Size / 2) {
            curr = L->Head;
            for (int i = 1; i < pos; i++) {
                curr = curr->Next;
            }
            std::cout << "test6";
        } else {
            curr = L->Tail;
            for (int i = L->Size; i > pos; i--) {
                curr = curr->Prev;
            }
        }

        curr->Prev->Next = curr->Next;
        curr->Next->Prev = curr->Prev;

        delete curr;
        L->Size--;
        // Remove element at specific position | Remove elemento em posição específica
    }

    template <typename T>
    T GetAt(const List<T>& L, int pos) {
        if (pos < 1 || pos > L.Size) return T{};
        // Return default if invalid | Retorna padrão se inválido

        Node<T>* curr = L.Head;

        for (int i = 1; i < pos; i++) {
            curr = curr->Next;
        }

        return curr->Data;
        // Get element at position | Pega elemento na posição
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
        L->Tail = nullptr;
        L->Size = 0;
        // Delete all nodes | Deleta todos os nodes
    }

    template <typename T>
    Node<T>* FindByID(List<T>& L, std::string id) {
        Node<T>* curr = L.Head;

        while (curr) {
            if (curr->Data.Id == id)
                return curr; 
                // Found by ID | Encontrado pelo ID
            curr = curr->Next;
        }

        return nullptr;
        // Not found | Não encontrado
    }

    template <typename T>
    void RemoveByNode(List<T>* L, Node<T>* node) {
        if (!L || !node) return;

        if (node == L->Head) {
            PopFront(L);
            return;
        }
        if (node == L->Tail) {
            PopBack(L);
            return;
        }

        node->Prev->Next = node->Next;
        node->Next->Prev = node->Prev;

        delete node;
        L->Size--;
        // Remove given node | Remove o node fornecido
    }

    template <typename T>
    void Display(const List<T>& L) {
        Node<T>* curr = L.Head;

        std::cout << " nullptr <- ";
        while (curr) {
            std::cout << curr->Data;
            if (curr->Next) std::cout << " <-> ";
            curr = curr->Next;
        }
        std::cout << " -> nullptr\n";
        // Display list visually | Mostra a lista visualmente
    }

}

#endif
