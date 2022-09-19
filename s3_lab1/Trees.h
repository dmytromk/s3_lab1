#pragma once

#include "LinkedStructs.h"

#include <vector>

namespace tree
{
	template <class T>
	struct MultNode
	{
		T key;
		std::vector<MultNode*> child;
		MultNode(T key)
		{
			this->key = key;
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
		MultNode<T>* searchDFS(MultNode<T>* root, T key)
		{
			if (root == nullptr) return nullptr;
			else if (root->key == key) return root;

			else
			{
				for (MultNode<T>* iter : root->child)
				{
					MultNode<T>* temp = searchDFS(iter, key);
					if (temp->key == key) return temp;
				}
				return nullptr;
			}
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