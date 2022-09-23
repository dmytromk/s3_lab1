#pragma once

#include "LinkedStructs.h"

#include <vector>

namespace tree
{
	template <class T>
	struct MultNode
	{
		T key;
		std::vector<MultNode<T>*> child;
		MultNode(T key)
		{
			this->key = key;
		}
		int size()
		{
			return this->child.size();
		}
	};

	template <class T>
	struct MultTree
	{
		MultNode<T>* head;
		MultTree()
		{
			this->head = nullptr;
		}
		void add(MultNode<T>* root, T key)
		{
			MultNode<T>* to_add = new MultNode<T>(key);
			if (root == nullptr) 
				this->head = to_add;
			else
				root->child.push_back(to_add);
			return;
		}
		MultNode<T>* searchNLR(MultNode<T>* root, T key)
		{
			if (root == nullptr) return nullptr;
			else if (root->key == key) return root;

			else
			{
				for (auto iter : root->child)
				{
					MultNode<T>* temp = searchNLR(iter, key);
					if (temp == nullptr) 
						continue;
					else if (temp->key == key) 
						return temp;
				}
				return nullptr;
			}
		}
		MultNode<T>* searchNRL(MultNode<T>* root, T key)
		{
			if (root == nullptr) return nullptr;
			else if (root->key == key) return root;

			else
			{
				for (auto iter = root->size()-1; iter >= 0; iter -= 1)
				{
					MultNode<T>* temp = searchNRL(iter, key);
					if (temp == nullptr)
						continue;
					else if (temp->key == key)
						return temp;
				}
				return nullptr;
			}
		}
		MultNode<T>* searchBFS(MultNode<T>* root, T key)
		{
			std::vector<MultNode<T>*> result;
			if (root == nullptr) return nullptr;

			linked::Queue<MultNode<T>*> q;
			q.pushBack(root);

			while (!q.empty())
			{
				MultNode<T>* iter = q.top();
				q.popTop();
				if (iter->key == key)
					return iter;

				for (auto temp : iter->child)
				{
					if (temp->key == key)
						return temp;
					else
						q.pushBack(temp);
				}
			}
			return nullptr;
		}
		void deleteRecurs(MultNode<T>* root)
		{
			if (root == nullptr)
				return;

			for (MultNode<T>* iter : root->child)
				deleteRecurs(iter);

			delete root;

		}
		void deleteNodeIdx(MultNode<T>* root, int idx)
		{
			deleteRecurs(root->child[idx]);
		}
		void deleteNodeKey(T key)
		{
			MultNode<T>* root = searchDFS(this->head, key);
			deleteRecurs(root);
		}
		void print(MultNode<T>* root)
		{
			if (root == nullptr)
				return;
			linked::Queue<MultNode<T>*> queue;
			queue.pushBack(root);
			while (!queue.empty())
			{
				int n = queue.size();

				// If this node has children
				while (n > 0)
				{
					MultNode<T>* p = queue.top();
					queue.popTop();
					std::cout << p->key << " ";

					for (int i = 0; i < p->child.size(); i++)
						queue.pushBack(p->child[i]);
					n--;
				}

				std::cout << std::endl;
			}
			std::cout << "\n\n";
		}
		~MultTree()
		{
			deleteRecurs(this->head);
		}
	};
}