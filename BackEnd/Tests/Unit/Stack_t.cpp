#include "../../Include/DataStructures/Stack.h"
#include <iostream>
#include <cassert>

using namespace Stack;

void TestStack() {
    auto stack = Create<int>();

    assert(IsEmpty(stack));

    Push(&stack, 10);
    Push(&stack, 20);
    Push(&stack, 30);

    std::cout << "After pushes: ";
    Display(stack);

    assert(Top(stack) == 30);

    Pop(&stack);
    std::cout << "After pop: ";
    Display(stack);
    assert(Top(stack) == 20);

    Pop(&stack);
    Pop(&stack);
    assert(IsEmpty(stack));

    Pop(&stack);

    std::cout << "Stack tests passed!\n";
}

int main() {
    TestStack();
    return 0;
}
