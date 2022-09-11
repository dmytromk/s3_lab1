#pragma once


namespace linked
{

	template <class T>
	struct LinkedList
	{
		struct Node
		{
			T value;
			Node* next;
			Node* prev;
			Node(T value);
		};
		Node* head;
		Node* tail;
		LinkedList();
		~LinkedList();
		bool empty();
		void print();
		void pushFront(T add);
	};

	template <class T>
	struct LinkedStack : class LinkedList
	{
		T top();
		T popFront();
	};

	template <class T>
	struct LinkedQueue : class LinkedList
	{
		T back();
		void popBack();
	};

	template <class T>
	struct LinkedDeque : class LinkedStack
	{
		void pushBack(T add);
	};
}