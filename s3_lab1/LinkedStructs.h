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
		int iSize;
		Node<T>* head;
		Node<T>* tail;
		List()
		{
			this->iSize = 0;
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
		int size()
		{
			return this->iSize;
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
				to_add->prev = this->tail;
				this->tail->next = to_add;
				this->tail = to_add;
			}
			this->iSize++;
		}
	};

	template <class T>
	struct Stack: 
		virtual List<T>
	{
		T back()
		{
			if (!this->empty()) 
				return this->tail->value;
			else
			{
				std::cout << "Underflow.\n\n";
				std::exit(1);
			}

		}
		void popBack()
		{
			if (this->empty())
			{
				std::cout << "Underflow.\n\n";
				std::exit(1);
			}

			Node<T>* temp = this->tail;

			if (this->tail == this->head)
			{
				this->tail = nullptr;
				this->head = nullptr;
				delete temp;
			}

			else
			{
				this->tail = this->tail->prev;
				this->tail->next = nullptr;
				delete temp;
			}
			this->iSize--;
		}
	};

	template <class T>
	struct Queue: 
		virtual List<T>
	{
		T top()
		{
			if (!this->empty()) return this->head->value;
			else 
			{
				std::cout << "Underflow.\n\n";
				std::exit(1);
			}
		}
		void popTop()
		{
			if (this->empty())
			{
				std::cout << "Underflow.\n\n";
				std::exit(1);
			}

			Node<T>* temp = this->head;

			if (this->head == this->tail)
			{
				this->tail = nullptr;
				this->head = nullptr;
				delete temp;
			}

			else
			{
				this->head = this->head->next;
				this->head->prev = nullptr;
				delete temp;
			}

			this->iSize--;
		}
	};

	template <class T>
	struct Deque: 
		Stack<T>, Queue<T>
	{
		void pushTop(T add)
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

			this->iSize++;
		}
	};
}