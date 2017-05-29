#include <iostream>
#include <vector>


template <typename T>
class BinaryTree
{
public:
	struct Node{
		T data;
		Node *left_child;
		Node *right_child;
	};
private:
	Node *root;
	
	void remove_subtree(Node * node){
		if(node == NULL){ return; }
		Node *left= node->left_child;
		Node *right = node->right_child;
		delete node;
		remove_subtree(left);
		remove_subtree(right);
	}

	bool insert(const T &key, Node *tree, const T &new_data, bool right){
		if(tree != NULL){

			if(tree->data == key){
				if(right){
					tree->right_child = new Node;
					tree->right_child->data = new_data;
				} else {
					tree->left_child = new Node;
					tree->left_child->data = new_data;
				}
				return true;
			}
			if(insert(key, tree->left_child, new_data, right) || 
				insert( key, tree->right_child, new_data, right)){
				return true;
			}
		}
		return false;
	}

	// Answer to Q1 from assignment2
	bool print_ancestors(const T &key, Node *tree, std::vector<T> &ancestors){
		if(tree != NULL){

			if(tree->data == key){
				return true;
			}
			if(print_ancestors(key, tree->left_child, ancestors) || 
				print_ancestors( key, tree->right_child, ancestors)){
				ancestors.push_back(tree->data);
				return true;
			}
		}
		return false;
	}

	// Answer to Q2 from assignment2
	Node* common_ancestor(const T& val1, const T&val2,Node* tree, bool& found){
		if(tree == NULL){
			found = false;
			return NULL;
		}
		bool left = false;
		bool right = false;
		if(tree->data == val1 || tree->data == val2){
			common_ancestor(val1, val2, tree->right_child, right);
			common_ancestor(val1, val2, tree->left_child, left);
			found = right || left;
			if(found) return tree;
			found = true;
			return NULL;
		}
		Node* common = common_ancestor(val1, val2, tree->right_child, right); 
		if(common == NULL){
			common = common_ancestor(val1, val2, tree->left_child, left);
		}
		found = right || left;
		if(right && left) return tree;
		return common;
	}
public:
	BinaryTree(){
		root = NULL; 
	}
	~BinaryTree(){
		if(root != NULL){
			remove_subtree(root);
		}
	}

	void setRoot(const T &key){
		if(root == NULL)
			root = new Node;
		root->data=key;
	}

	bool Insert(const T &key, const T &new_data, bool right){
		return insert(key, root, new_data, right);
	}

	// Wrapper for print_ancestors for Q1
	bool PrintAncestors(const T &key, std::vector<T> &ancestors){
		return print_ancestors(key, root, ancestors);
	}

	// Wrapper for common_ancestors for Q2
	Node * CommonAncestor(const T& val1, const T&val2){
		bool found = false;
		return common_ancestor(val1, val2, root, found); 
	}
	
};

