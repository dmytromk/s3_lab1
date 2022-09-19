#include "LinkedStructs.h"
#include "ArrayStructs.h"
#include "VectorStructs.h"

#include "Trees.h"

#include <stack>

#include <iostream>

int main()
{
    vectorized::Deque<int> ddeque;
    std::cout << ddeque.empty() << "\n\n";
    ddeque.pushBack(2);
    ddeque.pushBack(3);
    ddeque.print();
    ddeque.pushBack(4);
    ddeque.print();
    ddeque.pushTop(5);
    ddeque.print();

    std::cout << "/////////////////////////////////////////////\n\n";

    array::Deque<int> linked_deque;
    std::cout << linked_deque.empty() << "\n\n";
    linked_deque.pushBack(2);
    linked_deque.pushBack(3);
    linked_deque.print();
    linked_deque.pushBack(4);
    linked_deque.print();
    linked_deque.pushTop(5);
    linked_deque.print();

    std::cout << "/////////////////////////////////////////////\n\n";

    tree::MultTree<int> lol;
    lol.add(lol.head, 10);
    lol.add(lol.head, 12);
    lol.print(lol.head);
    lol.print(lol.head);
}

