
#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include <ostream>

template<typename T>
class binary_tree
{
	class tree_node
	{
	public:
		T data;
		tree_node * pLeft;
		tree_node * pRight;
	
		tree_node(T data_);
		~tree_node();
		tree_node* recursion_insert(T data_);
		void output_tree(std::ostream& ostream);
	};

	tree_node* pRoot;
public:
	binary_tree();
	~binary_tree();
	tree_node* insert(T data_);
	tree_node* recursion_insert(T data_);
	void output_tree(std::ostream& ostream);
};
#endif // !_BINARY_TREE_H_
