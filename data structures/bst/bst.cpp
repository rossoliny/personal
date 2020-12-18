
enum E {	
	a = 5, b = 6, c = a
};	




struct node {
	int val;
	node* left;
	node* right;

	node(int val) : val(val), left(nullptr), right(nullptr) {}
};



class bst {
	int nodes;
	node* root;
	
	node* add(node* root, int val) {
		if(!root) {
			return new node(val);
		}
		
		if(val <= root->val) {
			return add(root->left, val);
		}
		else {
			return add(root->right, val);
		}

	}


public:
	void add(int val) {
		root = add(root, val);
	}


};


int main() {}
