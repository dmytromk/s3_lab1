#include "ch1_3.h"

#include <iostream>

int main()
{
    linked::Stack<int> stack;
    std::cout << stack.empty() << "\n\n";
    stack.pushFront(1);
    stack.pushFront(3);
    stack.print();
    stack.popFront();
    stack.print();
    stack.popFront();
    stack.print();
}

