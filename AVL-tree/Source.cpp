#include <iostream>
using namespace std;

struct Node {
	string integerPart;
	string decimalPart;
	Node* right;
	Node* left;
};

void add(string newIntegerPart, string newDecimalPart, Node* root) {
	while (root != NULL) {
		if (newIntegerPart > root->integerPart ||
			(newIntegerPart == root->integerPart && newDecimalPart > root->decimalPart)) {
			root = root->right;
		}
		else {
			root = root->left;
		}
	}
	root->integerPart = newIntegerPart;
	root->decimalPart = newDecimalPart;
	root->right = NULL;
	root->left = NULL;
}


int main() {
	cout << "hello world";
	
}