#include "../../Include/DataStructures/DoublyLinkedList.h"

#include <cassert>
#include <iostream>

using namespace Doubly;

void TestDoublyList() {
    auto list = Create<int>();
    assert(IsEmpty(list));

    PushBack(&list, 10);
    PushBack(&list, 20);
    PushFront(&list, 5);

    std::cout << "After pushes: ";
    Display(list);

    assert(GetAt(list, 1) == 5);
    assert(GetAt(list, 2) == 10);
    assert(GetAt(list, 3) == 20);

    PopFront(&list);
    std::cout << "After PopFront: ";
    Display(list);
    assert(GetAt(list, 1) == 10);

    PopBack(&list);
    std::cout << "After PopBack: ";
    Display(list);
    assert(GetAt(list, 1) == 10);
    assert(list.Size == 1);

    Clear(&list);
    std::cout << "After Clear: ";
    Display(list);
    assert(IsEmpty(list));

    std::cout << "Doubly Linked List tests passed!\n";

}

int main() {
    TestDoublyList();
    return 0;
}