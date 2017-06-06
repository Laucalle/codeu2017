#include <iostream>
#include <vector>


template <typename T>
class BinaryTree
{
private:
	struct Node{
		T data;
		Node *left_child;
		Node *right_child;
	};

	Node *root;
	
	void remove_subtree(Node * node){
		if(node == nullptr){ return; }
		Node *left= node->left_child;
		Node *right = node->right_child;
		delete node;
		remove_subtree(left);
		remove_subtree(right);
	}

	bool insert(const T &parent_key, Node *tree, const T &new_data, bool right){
		if(tree != nullptr){

			if(tree->data == parent_key){
				if(right){
					tree->right_child = new Node;
					tree->right_child->data = new_data;
				} else {
					tree->left_child = new Node;
					tree->left_child->data = new_data;
				}
				return true;
			}
			if(insert(parent_key, tree->left_child, new_data, right) || 
				insert( parent_key, tree->right_child, new_data, right)){
				return true;
			}
		}
		return false;
	}

	// Answer to Q1 from assignment2
	// Ancestors to key are saved into ancestors vector
	bool print_ancestors(const T &key, Node *tree, std::vector<T>* ancestors){
		if(tree != nullptr){

			if(tree->data == key){
				return true;
			}
			if(print_ancestors(key, tree->left_child, ancestors) || 
				print_ancestors( key, tree->right_child, ancestors)){
				ancestors->push_back(tree->data);
				return true;
			}
		}
		return false;
	}

	// Answer to Q2 from assignment2
	// Returns lowest common ancestor of val1 and val2, given keys are unique 
	// and val1 != val2(in which case nullptr is returned.
	// If one of them is absent, it will return a nullptr
	Node* common_ancestor(const T& val1, const T&val2,Node* tree, bool& found){
		if(tree == nullptr){
			found = false;
			return nullptr;
		}
		bool left = false;
		bool right = false;
		if(tree->data == val1 || tree->data == val2){
			common_ancestor(val1, val2, tree->right_child, right);
			common_ancestor(val1, val2, tree->left_child, left);
			found = right || left;
			if(found) return tree;
			found = true;
			return nullptr;
		}
		Node* common = common_ancestor(val1, val2, tree->right_child, right); 
		if(common == nullptr){
			common = common_ancestor(val1, val2, tree->left_child, left);
		}
		found = right || left;
		if(right && left) return tree;
		return common;
	}
public:
	BinaryTree(){
		root = nullptr; 
	}
	~BinaryTree(){
		remove_subtree(root);
	}

	// Set root's value
	void setRoot(const T &key){
		if(root == nullptr)
			root = new Node;
		root->data=key;
	}

	// Inserts new_data as a child of parent_key.
	bool Insert(const T &parent_key, const T &new_data, bool right){
		return insert(parent_key, root, new_data, right);
	}

	// Wrapper for print_ancestors for Q1
	// Saves ancestors to key in ancestors vector (reverse order)
	bool PrintAncestors(const T &key, std::vector<T> *ancestors){
		return print_ancestors(key, root, ancestors);
	}

	// Wrapper for common_ancestors for Q2
	// Returns pointer to data of the lowest common ancestor of val1 and val2,
	// given that all keys are unique and val1 != val2. If one of them is
	// not in the tree, nullptr is returned.
	T * CommonAncestor(const T& val1, const T&val2){
		if( val1 == val2) return nullptr;
		bool found = false;
		Node * common = common_ancestor(val1, val2, root, found); 
		if(common != nullptr) return &(common->data);
		return nullptr;
	}
	
};

int main(){
	BinaryTree<int> tree;

	tree.setRoot(16);
	tree.Insert(16, 9, false);
	tree.Insert(9, 3, false);
	tree.Insert(3, 1, false);
	tree.Insert(3, 5, true);
	tree.Insert(9, 14, true);
	tree.Insert(16, 18, true);
	tree.Insert(16, 19, true);

	int* a = tree.CommonAncestor(5,14);
	if(a == nullptr){
		std::cerr << "CommonAncestor: error\n";
	}
	else if (*a == 9) std::cout << "CommonAncestor: correct\n";
	else std::cerr << "CommonAncestor: wrong value\n"; 

	// one of the keys is not in tree
	int* b = tree.CommonAncestor(5,4);
	if(b == nullptr){
		std::cout << "CommonAncestor: correct\n";
	}
	else std::cerr << "CommonAncestor: error\n";

	// one of the keys is ancestor to the other
	int* c = tree.CommonAncestor(9,3);
	if(c == nullptr){
		std::cerr << "CommonAncestor: error\n";
	}
	else if(*c == 9) {
		std::cout << "CommonAncestor: correct\n";
	}
	
	std::vector<int> ancestors;
	std::vector<int> test_solution({3,9,16});
	tree.PrintAncestors(5, &ancestors);

	bool correct = true;
	if(ancestors.size() == test_solution.size()){
		for(int i = 0; i<ancestors.size() && correct; i++){
			correct = ancestors[i] == test_solution[i];
		}
	} else correct = false;
	if(correct) std::cout << "PrintAncestors: correct\n";
	else std::cerr << "PrintAncestors: error\n";

	ancestors.clear();
	tree.PrintAncestors(2, &ancestors);
	if(ancestors.empty()) std::cout << "PrintAncestors: correct\n";
	else std::cerr << "PrintAncestors: error\n";

}
