#pragma once
#include "LinkedStructs.h"

#include <string>
#include <vector>

namespace tree
{
	template <typename T>
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

	template <typename T>
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

	template <typename T>
	struct BinNode
	{
		T key;
		BinNode<T>* parent;
		BinNode<T>* left;
		BinNode<T>* right;
		BinNode(T key)
		{
			this->key = key;
			this->parent = nullptr;
			this->left = nullptr;
			this->right = nullptr;
		}
	};

	template <typename T>
	struct BinTree
	{
		BinNode<T>* head;
		BinTree()
		{
			this->head = nullptr;
		}
		void add(BinNode<T>* root, T key)
		{
			BinNode<T>* to_add = new BinNode<T>(key);

			if (root == nullptr)
			{
				if(this->head == nullptr) this->head = to_add;
				return;
			}

			linked::Queue<BinNode<T>*> q;
			q.pushBack(root);

			while (!q.empty())
			{
				BinNode<T>* iter = q.top();
				q.popTop();

				if (iter->left == nullptr)
				{
					to_add->parent = iter;
					iter->left = to_add;
					return;
				}
				else
					q.pushBack(iter->left);

				if (iter->right == nullptr)
				{
					to_add->parent = iter;
					iter->right = to_add;
					return;
				}
				else
					q.pushBack(iter->right);
			}
		}
		BinNode<T>* searchPreOrder(BinNode<T>* root, T key, bool reversal_flag = false)
			//Pre-order
		{
			if (root == nullptr) return nullptr;
			else if (root->key == key) return root;

			if (!reversal_flag)
			{
				//Node-Left-Right
				//None-Reverse
				BinNode<T>* first = searchPreOrder(root->left, key, reversal_flag);
				if (first)
					if(first->key == key)
						return first;

				BinNode<T>* second = searchPreOrder(root->right, key, reversal_flag);
				if (second)
					if (second->key == key)
						return second;
			}

			if (reversal_flag)
			{
				//Node-Right-Left
				//Reverse
				BinNode<T>* first = searchPreOrder(root->right, key, reversal_flag);
				if (first)
					if (first->key == key)
						return first;

				BinNode<T>* second = searchPreOrder(root->left, key, reversal_flag);
				if (second)
					if (second->key == key)
						return second;
			}

			return nullptr;
		}
		BinNode<T>* searchPostOrder(BinNode<T>* root, T key, bool reversal_flag = false)
			//Post-order
		{
			if (root == nullptr) return nullptr;

			if (!reversal_flag)
			{
				//Left-Right-Node
				//None-Reverse
				BinNode<T>* first = searchPostOrder(root->left, key, reversal_flag);
				if (first)
					if (first->key == key)
						return first;

				BinNode<T>* second = searchPostOrder(root->right, key, reversal_flag);
				if (second)
					if (second->key == key)
						return second;
			}

			if (reversal_flag)
			{
				//Right-Left-Node
				//Reverse
				BinNode<T>* first = searchPostOrder(root->right, key, reversal_flag);
				if (first)
					if (first->key == key)
						return first;

				BinNode<T>* second = searchPostOrder(root->left, key, reversal_flag);
				if (second)
					if (second->key == key)
						return second;
			}

			if (root->key == key)
				return root;

			return nullptr;
		}
		BinNode<T>* searchInOrder(BinNode<T>* root, T key, bool reversal_flag = false)
			//In-order
		{
			if (root == nullptr) return nullptr;

			if (!reversal_flag)
			{
				//Left-Node-Right
				//None-Reverse
				BinNode<T>* first = searchInOrder(root->left, key, reversal_flag);
				if (first)
					if (first->key == key)
						return first;

				if (root->key == key)
					return root;

				BinNode<T>* second = searchInOrder(root->right, key, reversal_flag);
				if (second)
					if (second->key == key)
						return second;
			}

			if (reversal_flag)
			{
				//Right-Left-Node
				//Reverse
				BinNode<T>* first = searchInOrder(root->right, key, reversal_flag);
				if (first)
					if (first->key == key)
						return first;

				if (root->key == key)
					return root;

				BinNode<T>* second = searchInOrder(root->left, key, reversal_flag);
				if (second)
					if (second->key == key)
						return second;
			}

			return nullptr;
		}
		BinNode<T>* searchBreadthFirst(BinNode<T>* root, T key)
			//breadth-first search
		{
			BinNode<T>* result;
			if (root == nullptr) return nullptr;

			linked::Queue<BinNode<T>*> q;
			q.pushBack(root);

			while (!q.empty())
			{
				BinNode<T>* iter = q.top();
				q.popTop();
				if (iter->key == key)
					return iter;

				if (iter->left->key == key)
					return iter->left;
				else
					q.pushBack(iter->left);

				if (iter->right->key == key)
					return iter->right;
				else
					q.pushBack(iter->right);
			}
			return nullptr;
		}
		void deleteAllChildren(BinNode<T>* root)
		{
			if (root == nullptr) return;

			deleteAllChildren(root->left);
			deleteAllChildren(root->right);

			if (root == this->head)
			{
				delete root;
				this->head = nullptr;
				return;
			}

			delete root;
			root = nullptr;
		}
		void deleteAllChildrenByNodeKey(T key, int idx)
		{
			MultNode<T>* root = searchBreadthFirst(this->head, key);
			deleteAllChildren(root);
			delete root;
		}
		void print(BinNode<T>* root)
		{
			if (root == nullptr)
				return;
			linked::Queue<BinNode<T>*> queue;
			queue.pushBack(root);
			while (!queue.empty())
			{
				int n = queue.size();

				// If this node has children
				while (n > 0)
				{
					BinNode<T>* p = queue.top();
					queue.popTop();
					std::cout << p->key << " ";
					if(p->left) queue.pushBack(p->left);
					if(p->right) queue.pushBack(p->right);
					n--;
				}
				std::cout << std::endl;
			}
			std::cout << "\n\n";
		}
	};
}