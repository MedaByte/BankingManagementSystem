#include "../../Include/DataStructures/Queue.h"
#include <iostream>
#include <cassert>

using namespace Queue;

void TestQueue() {
    auto queue = Create<int>();

    assert(IsEmpty(queue));

    Enqueue(&queue, 10);
    Enqueue(&queue, 20);
    Enqueue(&queue, 30);

    std::cout << "After enqueues: ";
    Display(queue);

    assert(Front(queue) == 10);

    Dequeue(&queue);
    std::cout << "After dequeue: ";
    Display(queue);
    assert(Front(queue) == 20);

    Dequeue(&queue);
    Dequeue(&queue);
    assert(IsEmpty(queue));

    std::cout << "Queue tests passed!\n";
}

int main() {
    TestQueue();
    return 0;
}
