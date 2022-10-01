#pragma once
#include "LinkedStructs.h"

#include <string>
#include <vector>

namespace tree
{
	template <class T>
	struct MultNode
	{
		T key;
		std::vector<MultNode<T>*> children;
		MultNode<T>* parent;
		MultNode(T key)
		{
			this->key = key;
			this->parent = nullptr;
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
			to_add->parent = root;
			if (root == nullptr)
				this->head = to_add;
			else
			{
				root->children.push_back(to_add);
			}
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
				from = root->children.size() - 1;
				to = -1;
				step = -1;
			}

			for (from; from != to; from += step)
			{
				MultNode<T>* temp = searchPreOrder(root->children[from], key, reversal_flag);
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
				from = root->children.size() - 1;
				to = -1;
				step = -1;
			}

			for (from; from != to; from += step)
			{
				MultNode<T>* temp = searchPostOrder(root->children[from], key, reversal_flag);
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
				from = root->children.size() - 1;
				if (from < 0) from = 0; //do not check the empty children vector
				to = 0; //Every node except the first one
				step = -1;
			}

			for (from; from != to; from += step)
			{
				MultNode<T>* temp = searchInOrder(root->children[from], key, reversal_flag);
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
				MultNode<T>* temp = searchInOrder(root->children[to], key, reversal_flag);
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
		void deleteAllChildren(MultNode<T>* root)
		{
			if (root == nullptr) return;

			if (root->children.size() == 0)
			{
				delete root;
				return;
			}

			for (int i = 0; i < root->children.size(); i++)
			{
				MultNode<T>* child = root->children[i];
				deleteAllChildren(child);
				root->children.erase(root->children.begin() + i);
				i--;
			}
			return;
		}
		void deleteByNodeIdx(MultNode<T>* parent, int idx)
		{
			MultNode<T>* root = parent->children[idx];
			deleteAllChildren(root);
			parent->children.erase(parent->children.begin() + idx);
			delete root;
		}
		void deleteByNodeKey(T key, int promote_node = 0)
		{
			//promote_node can be 
			//0 - promote no node and delete all the children,
			//-1 - "all", 
			//n - promote the n-th node

			MultNode<T>* root = searchBreadthFirst(this->head, key);
			if (root == nullptr) 
				return;
			MultNode<T>* parent = root->parent;

			//delete all node children
			if (promote_node == 0)
			{
				deleteAllChildren(root);

				//node is the head
				if (parent == nullptr)
				{
					this->head = nullptr;
					delete root;
					return;
				}

				//node isn't the head
				for (int i = 0; i < parent->children.size(); i++)
				{
					if (parent->children[i] == root)
					{
						parent->children.erase(parent->children.begin() + i);
						delete root;
						return;
					}
				}
			}

			//promote only the first child
			else if (root->children.size() == 1)
			{
				MultNode<T>* one_child = root->children[0];
				one_child->parent = parent;

				//node is the head
				if (parent == nullptr)
				{
					this->head = one_child;
					delete root;
					return;
				}

				//node isn't the head
				for (int i = 0; i < parent->children.size(); i++)
				{
					if (parent->children[i] == root)
					{
						parent->children[i] = one_child;
						delete root;
						return;
					}
				}
			}

			//promote all the children
			else if (promote_node == -1)
			{
				//node is the head 
				//make only the first child as the head
				if (parent == nullptr)
				{
					MultNode<T>* one_child = root->children[0];
					one_child->parent = parent;
					this->head = one_child;
					for (int i = 1; i < root->children.size(); i++)
					{
						MultNode<T>* temp = root->children[i];
						temp->parent = this->head;
						this->head->children.push_back(temp);
					}
					delete root;
					return;
				}

				//node isn't the head
				for (int i = 0; i < parent->children.size(); i++)
				{
					if (parent->children[i] == root)
					{
						for (int j = 0; j < root->children.size(); j++)
						{
							MultNode<T>* temp = root->children[j];
							temp->parent = parent;
							this->head->children.push_back(temp);
						}
						delete root;
						return;
					}
				}
			}

			//promote only the specific child
			else
			{
				MultNode<T>* child = root->children[promote_node - 1];
				child->parent = parent;

				//node is the head 
				if (parent == nullptr)
				{
					this->head = child;
					root->children.erase(root->children.begin() + promote_node - 1);

					for (int i = 0; i < root->children.size(); i++)
					{
						MultNode<T>* temp = root->children[i];
						temp->parent = this->head;
						this->head->children.push_back(temp);
					}
					delete root;
					return;
				}

				//node isn't the head
				for (int i = 0; i < parent->children.size(); i++)
				{
					if (parent->children[i] == root)
					{
						parent->children[i] = child;
						root->children.erase(root->children.begin() + promote_node - 1);
						for (int j = 0; i < root->children.size(); j++)
						{
							MultNode<T>* temp = root->children[j];
							temp->parent = child;
							parent->children.push_back(temp);
						}
						delete root;
						return;
					}
				}
			}
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
			deleteAllChildren(this->head);
			delete this->head;
			this->head = nullptr;
		}
	};
}