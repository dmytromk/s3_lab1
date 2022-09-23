#pragma once

#include "LinkedStructs.h"

#include <vector>

namespace tree
{
	template <class T>
	struct MultNode
	{
		T key;
		std::vector<MultNode<T>*> children;
		MultNode(T key)
		{
			this->key = key;
		}
		int size()
		{
			return this->children.size();
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
				root->children.push_back(to_add);
			return;
		}
		MultNode<T>* searchPreOrder(MultNode<T>* root, T key, bool reversal_flag = false)
			//Pre-order
		{
			if (root == nullptr) return nullptr;
			else if (root->key == key) return root;

			int from, to, step;

			if (!reversal_flag)
			{
				//Node-Left-Right
				//None-Reverse
				from = 0;
				to = root->children.size();
				step = 1;
			}
			else
			{
				//Node-Right-Left
				//Reverse
				from = root->children.size()-1;
				to = -1;
				step = -1;
			}

			for (from; from != to; from += step)
					{
						MultNode<T>* temp = searchPreOrder(root->children[from], key);
						if (temp == nullptr)
							continue;
						else if (temp->key == key)
							return temp;
					}		
			return nullptr;
		}
		MultNode<T>* searchPostOrder(MultNode<T>* root, T key, bool reversal_flag = false)
			//Post-order
		{
			if (root == nullptr) return nullptr;

			int from, to, step;

			if (!reversal_flag)
			{
				//Left-Right-Node
				//None-Reverse
				from = 0;
				to = root->children.size();
				step = 1;
			}
			else
			{
				//Right-Left-Node
				//Reverse
				from = root->children.size()-1;
				to = -1;
				step = -1;
			}

			for (from; from != to; from += step)
			{
				MultNode<T>* temp = searchPostOrder(root->children[from], key);
				if (temp == nullptr)
					continue;
				else if (temp->key == key)
					return temp;
			}

			if (root->key == key) return root;

			return nullptr;
		}
		MultNode<T>* searchInOrder(MultNode<T>* root, T key, bool reversal_flag = false)
			//In-order
		{
			if (root == nullptr) return nullptr;

			int from, to, step;

			if (!reversal_flag)
			{
				//Left-Node-Right
				//None-Reverse
				from = 0;
				to = root->children.size() - 1; //Every node except the last one
				if (to < 0) to = 0; //do not check the empty children vector
				step = 1;
			}
			else
			{
				//Right-Node-Left
				//Reverse
				from = root->children.size()-1;
				if (from < 0) from = 0; //do not check the empty children vector
				to = 0; //Every node except the first one
				step = -1;
			}

			for (from; from != to; from += step)
			{
				MultNode<T>* temp = searchInOrder(root->children[from], key);
				if (temp == nullptr)
					continue;
				else if (temp->key == key)
					return temp;
			}

			if (root->key == key) return root;

			if (!reversal_flag) to++; //Check the last node
			else to--; //Check the first node

			if (!root->children.empty())
			{
				MultNode<T>* temp = searchInOrder(root->children[to], key);
				return temp;
			}

			return nullptr;
		}
		MultNode<T>* searchBreadthFirst(MultNode<T>* root, T key)
		{
			//breadth-first search

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

				for (auto temp : iter->children)
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

			for (MultNode<T>* iter : root->children)
				deleteRecurs(iter);

			delete root;

		}
		void deleteNodeIdx(MultNode<T>* root, int idx)
		{
			deleteRecurs(root->children[idx]);
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

					for (int i = 0; i < p->children.size(); i++)
						queue.pushBack(p->children[i]);
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