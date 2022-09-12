#pragma once

#include <iostream>

namespace linked
{
	template <class T>
	struct Node
	{
		T value;
		Node<T>* next;
		Node<T>* prev;
		Node(T value)
		{
			this->value = value;
			next = nullptr;
			prev = nullptr;
		}
	};

	template <class T>
	struct List
	{
		Node<T>* head;
		Node<T>* tail;
		List()
		{
			this->head = nullptr;
			this->tail = nullptr;
		}
		~List()
		{
			Node<T>* iter = this->head;
			while (iter != nullptr)
			{
				Node<T>* temp = iter->next;
				delete iter;
				iter = temp;
			}
			this->head = nullptr;
			this->tail = nullptr;
		}
		bool empty()
		{
			return (head == nullptr);
		}
		void print()
		{
			Node<T>* iter = this->head;
			while (iter != nullptr)
			{
				std::cout << iter->value << " ";
				iter = iter->next;
			}
			std::cout << "\n\n";
		}
		void pushFront(T add)
		{
			Node<T>* to_add = new Node<T>(add);
			if (this->head == nullptr)
			{
				this->head = to_add;
				this->tail = to_add;
			}
			else
			{
				to_add->prev = this->tail;
				this->tail->next = to_add;
				this->tail = to_add;
			}
		}
	};

	template <class T>
	struct Stack: 
		List<T>
	{
		T top()
		{
			if (!this->empty()) return this->tail->value;
			else
			{
				std::cout << "This queue is empty.\n\n";
				return nullptr;
			}
		}
		T popFront()
		{
			Node<T>* temp = this->tail;
			T result = temp->value;

			if (this->tail == this->head)
			{
				this->tail = nullptr;
				this->head = nullptr;
				delete temp;
				return result;
			}

			else
			{
				this->tail = this->tail->prev;
				this->tail->next = nullptr;
				delete temp;
				return result;
			}
		}
	};

	template <class T>
	struct Queue: 
		List<T>
	{
		T back()
		{
			if (!this->empty()) return this->head->value;
			else
			{
				std::cout << "This queue is empty.\n\n";
				return nullptr;
			}
		}
		T popBack()
		{
			Node<T>* temp = this->head;
			T result = this->head->value;

			if (this->head == this->tail)
			{
				this->tail = nullptr;
				this->head = nullptr;
				delete temp;
				return result;
			}

			else
			{
				this->head = this->head->next;
				this->head->prev = nullptr;
				delete temp;
				return result;
			}
		}
	};

	template <class T>
	struct Deque: 
		Stack<T>, Queue<T>
	{
		void pushBack(T add)
		{
			Node<T>* to_add = new Node<T>(add);
			if (this->head == nullptr)
			{
				this->head = to_add;
				this->tail = to_add;
			}
			else
			{
				to_add->next = this->head;
				this->head->prev = to_add;
				this->head = to_add;
			}
		}
	};
}