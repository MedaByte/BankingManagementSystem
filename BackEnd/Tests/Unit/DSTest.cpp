#include <iostream>
#include <string>

#include "../../Include/DataStructures/SinglyLinkedList.h"
#include "../../Include/DataStructures/DoublyLinkedList.h"
#include "../../Include/DataStructures/Stack.h"
#include "../../Include/DataStructures/Queue.h"
#include "../../Include/Utils/IdGenerator.h"
#include "../../Include/Utils/OriginPath.h"

int main() {

    std::cout << "\n========= TESTING ORIGIN FOLDER =========\n";
    try {
        std::cout << "Origin Folder: " << Utils::GetOriginFolder() << "\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }


    std::cout << "\n========= TESTING ID GENERATOR =========\n";
    std::string idFile = "id_test.txt";
    std::cout << "Generated ID: " << Utils::GenerateId(idFile, "USR") << "\n";
    std::cout << "Next Generated ID: " << Utils::GenerateId(idFile, "USR") << "\n";


    std::cout << "\n========= TESTING SINGLY LINKED LIST =========\n";
    Singly::List<int> SL = Singly::Create<int>();
    Singly::PushBack(&SL, 10);
    Singly::PushBack(&SL, 20);
    Singly::PushFront(&SL, 5);
    Singly::Display(SL);
    std::cout << "SL GetAt(2) = " << Singly::GetAt(SL, 2) << "\n";
    Singly::PopFront(&SL);
    Singly::PopBack(&SL);
    Singly::Display(SL);
    Singly::Clear(&SL);


    std::cout << "\n========= TESTING DOUBLY LINKED LIST =========\n";
    Doubly::List<int> DL = Doubly::Create<int>();
    Doubly::PushBack(&DL, 100);
    Doubly::PushBack(&DL, 200);
    Doubly::PushFront(&DL, 50);
    Doubly::Display(DL);
    std::cout << "DL GetAt(3) = " << Doubly::GetAt(DL, 3) << "\n";
    Doubly::RemoveAt(&DL, 2);
    Doubly::Display(DL);
    Doubly::Clear(&DL);


    std::cout << "\n========= TESTING STACK =========\n";
    Stack::Stack<std::string> S = Stack::Create<std::string>();
    Stack::Push(&S, std::string("ef"));
    Stack::Push(&S, std::string("A"));
    Stack::Push(&S, std::string("B"));
    Stack::Push(&S, std::string("C"));
    Stack::Display(S);
    std::cout << "Top = " << Stack::Top(S) << "\n";
    Stack::Pop(&S);
    Stack::Display(S);
    Stack::Clear(&S);


    std::cout << "\n========= TESTING QUEUE =========\n";
    Queue::Queue<int> Q = Queue::Create<int>();
    Queue::Enqueue(&Q, 1);
    Queue::Enqueue(&Q, 2);
    Queue::Enqueue(&Q, 3);
    Queue::Display(Q);
    std::cout << "Front = " << Queue::Front(Q) << "\n";
    Queue::Dequeue(&Q);
    Queue::Display(Q);
    Queue::Clear(&Q);


    std::cout << "\n\n========= ALL TESTS COMPLETED =========\n";

    return 0;
}
