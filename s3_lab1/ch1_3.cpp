#include "ch1_3.h"

#include <string>

template<class T>
linked::LinkedList<T>::Node::Node(T value)
{
	this->value = value;
	next = nullptr;
	prev = nullptr;
}

template<class T>
linked::LinkedList<T>::LinkedList()
{
	head = nullptr;
	tail = nullptr;
}

template<class T>
linked::LinkedList<T>::~LinkedList()
{
	Node* iter = head;
	while (iter != nullptr)
	{
		Node* temp = iter->next;
		delete iter;
		iter = temp;
	}
	head = nullptr;
	tail = nullptr;
}

template<class T>
bool linked::LinkedList<T>::empty()
{
	if (head == nullptr) return true;
	else return false;
}

template<class T>
void linked::LinkedList<T>::print()
{
	Node* iter = head;
	while (iter != nullptr)
	{
		std::cout << iter->value << " ";
		iter = iter->next;
	}
	std::cout << "\n\n";
}

template<class T>
void linked::LinkedList<T>::pushFront(T add)
{
	Node* to_add = new Node(add);
	if (head == nullptr)
	{
		head = node;
		tail = node;
	}
	else
	{
		node->prev = tail;
		tail->next = node;
		tail = node;
	}
}

template<class T>
inline T linked::LinkedStack<T>::top()
{
	if (!this->empty()) return tail->value;
	else
	{
		std::cout << "This queue is empty.\n\n";
		return nullptr;
	}
}

template<class T>
T linked::LinkedStack<T>::popFront()
{
	Node* temp = tail;
	T result = temp->value;

	if (tail == head)
	{
		tail = nullptr;
		head = nullptr;
		delete temp;
		return result;
	}

	else
	{
		tail = tail->prev;
		tail->next = nullptr;
		delete temp;
		return result
	}
}

template<class T>
inline T linked::LinkedQueue<T>::back()
{
	if (!this->empty()) return head->value;
	else
	{
		std::cout << "This queue is empty.\n\n";
		return nullptr;
	}
}

template<class T>
void linked::LinkedQueue<T>::popBack()
{
	Node* temp = head;
	T result = head->value;

	if (head == tail)
	{
		tail = nullptr;
		head = nullptr;
		delete temp;
		return result;
	}

	else
	{
		head = head->next;
		head->prev = nullptr;
		delete temp;
		return result
	}
}

template<class T>
inline void linked::LinkedDeque<T>::pushBack(T add)
{
	Node* to_add = new Node(add);
	if (head == nullptr)
	{
		head = node;
		tail = node;
	}
	else
	{
		node->next = head;
		head->prev = node;
		head = node;
	}
}

