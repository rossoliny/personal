#include <string>
#include <iostream>
#include <cstring>

using namespace std;


bool strless(const char* a, const char* b) {
	int al = strlen(a);
	int bl = strlen(b);
	if(al < bl) {
		return true;
	}
	else if (al > bl) {
		return false;
	}
	else {
		for(int i = 0; i < al; ++i) {
			if(a[i] < b[i]) {
				return true;
			}
		}
	}
	return false;
}
bool strgreat(const char* a, const char* b) {
	return strless(b, a);
}

bool strequal(const char* a, const char* b) {
	return (!strless(a, b)) && (!strgreat(a, b));
}


struct Tnode {
	char* word;
	int count;
	Tnode* left;
	Tnode* right;
};

void add(Tnode** proot, const char* word) {
	Tnode* root = *proot;

	if(root == nullptr) {
		root = new Tnode;
		int len = strlen(word) + 1;
		root->word = new char[len];
		strncpy(root->word, word, len);
		root->word[len - 1] = '\0';
		root->left = nullptr;
		root->right = nullptr;
		*proot = root;
		return;
	}

	if(strequal(root->word, word)) {
		root->count++;
		return;
	}

	int isless = strless(word, root->word);

	if(isless) {
		add(&(root->left), word);
	} else {
		add(&(root->right), word);
	}
}


void print(const Tnode* root) {
	if(root == nullptr) {
		return;
	}

	cout << root->word << endl;
	print(root->left);
	print(root->right);
}


void printalpha(const Tnode* root) {
	if(root == nullptr) {
		return;
	}

	printalpha(root->left);
	cout << root->word << endl;
	printalpha(root->right);
}


int main(int argc, char** argv) {
	Tnode* root = nullptr;

	const char a[] = "a";
	const char b[] = "b";
	const char c[] = "c";
	const char d[] = "d";

	add(&root, d);
	add(&root, c);
	add(&root, b);
	add(&root, a);

	printalpha(root);

	return 0;
}
