#include "LinkedStructs.h"

#include <iostream>

int main()
{
    linked::Deque<int> linked_deque;
    std::cout << linked_deque.empty() << "\n\n";
    linked_deque.popFront();
    linked_deque.pushFront(2);
    linked_deque.pushFront(3);
    linked_deque.print();
    linked_deque.popFront();
    linked_deque.print();
    linked_deque.popFront();
    linked_deque.print();
}

