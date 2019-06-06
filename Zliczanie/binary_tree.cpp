
#include "binary_tree.h"

template<typename T>
binary_tree<T>::tree_node::tree_node(T data_) :pLeft(nullptr), pRight(nullptr), data(data_) {};

template<typename T>
binary_tree<T>::tree_node::~tree_node() {
	delete this->pRight;
	delete this->pLeft;
}

template<typename T>
typename binary_tree<T>::tree_node* binary_tree<T>::tree_node::recursion_insert(T data_) {
	
	if (data_ < this->data)
	{
		if (this->pLeft != nullptr)
		{
			return this->pLeft->recursion_insert(data_);
		}
		else
		{
			return this->pLeft = new tree_node{ data_ };
		}
	}
	else if (data > this->data)
	{
		if (this->pRight != nullptr)
		{
			return this->pRight->recursion_insert(data_);
		}
		else
		{
			return this->pRight = new tree_node{ data_ };
		}
	}
	else if (data_ == this->data)
	{
		return this;
	}
}

template<typename T>
void binary_tree<T>::tree_node::output_tree(std::ostream& ostream)
{
	if (this->pLeft)
	{
		this->pLeft->output_tree(ostream);
	}
	ostream << this->data << "\n";
	if (this->pRight)
	{
		this->pRight->output_tree(ostream);
	}
}

template<typename T>
binary_tree<T>::binary_tree() : pRoot(nullptr) {}

template<typename T>
binary_tree<T>::~binary_tree() {
	delete this->pRoot;
}

template<typename T>
typename binary_tree<T>::tree_node * binary_tree<T>::insert(T data_)
{
	if (this->pRoot == nullptr)
	{
		return this->pRoot = new tree_node{ data_ };
	}
	else {
		auto p = pRoot;
		while (true)
		{
			if (p->data < data_ && p->pLeft)
			{
				p = p->pLeft;
			}
			else if (p->data < data_ && !(p->pLeft))
			{
				return p->pLeft = new tree_node{ data_ };
			}
			else if (p->data > data_ && p->pRight)
			{
				p = p->pRight;
			}
			else if (p->data > data_ && !(p->pRight))
			{
				return p->pRight = new tree_node{ data_ };
			}
			else {
				return p;
			}
		}
	}
}

template<typename T>
typename binary_tree<T>::tree_node* binary_tree<T>::recursion_insert(T data_) {
	if (this->pRoot == nullptr)
	{
		return this->pRoot = new tree_node{ data_ };
	}
	else {
		return this->pRoot->recursion_insert(data_);
	}
}

template<typename T>
void binary_tree<T>::output_tree(std::ostream& ostream) {
	if (this->pRoot)
	{
		if (this->pRoot->pLeft)
		{
			this->pRoot->pLeft->output_tree(ostream);
		}
		ostream << this->pRoot->data << "\n";
		if (this->pRoot->pRight)
		{
			this->pRoot->pRight->output_tree(ostream);
		}
	}
}