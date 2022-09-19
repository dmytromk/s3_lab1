#pragma once

#include <vector>
#include <iostream>

namespace vectorized
{
	template <class T>
	struct List
	{
		std::vector<T> vect;
		List()
		{
			this->vect = {};
		}
		~List()
		{
			this->vect.clear();
		}
		bool empty()
		{
			return (this->vect.empty());
		}
		int size()
		{
			return this->vect.size();
		}
		void print()
		{
			for (auto i: this->vect)
				std::cout << i << " ";
			std::cout << "\n\n";
		}
		void pushBack(T add)
		{
			this->vect.push_back(add);
		}
	};

	template <class T>
	struct Stack :
		virtual List<T>
	{
		using List<T>::List;
		T back()
		{
			if (!this->empty()) return this->vect.back();
			else
			{
				std::cout << "This structure is empty.\n\n";
				std::exit(1);
			}
		}
		void popBack()
		{
			if (this->empty())
			{
				std::cout << "Underflow\n\n";
				std::exit(1);
			}

			else
				this->vect.pop_back();
		}
	};

	template <class T>
	struct Queue :
		virtual List<T>
	{
		using List<T>::List;
		T top()
		{
			if (!this->empty()) return this->vector.front();
			else
			{
				std::cout << "This structure is empty.\n\n";
				std::exit(1);
			}
		}
		void popTop()
		{
			if (this->empty())
			{
				std::cout << "This struct is empty\n\n";
				std::exit(1);
			}

			this->vect.erase(this->vect.begin());
		}
	};

	template <class T>
	struct Deque :
		Stack<T>, Queue<T>
	{
		void pushTop(T add)
		{
			this->vect.insert(this->vect.begin(), add);
		}
	};
}