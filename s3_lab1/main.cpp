#include "LinkedStructs.h"
#include "ArrayStructs.h"

#include <stack>

#include <iostream>

int main()
{
    array::Deque<int> linked_deque;
    std::cout << linked_deque.empty() << "\n\n";
    linked_deque.pushFront(2);
    linked_deque.pushFront(3);
    linked_deque.print();
    linked_deque.popFront();
    linked_deque.print();
    linked_deque.popFront();
    linked_deque.print();
}

