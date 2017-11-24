#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Node {
	string integerPart;
	string decimalPart;
	Node* right;
	Node* left;
};

void add(string newIntegerPart, string newDecimalPart, Node* root) {
	if (root != NULL) {
		if (newIntegerPart > root->integerPart || (newIntegerPart == root->integerPart && newDecimalPart > root->decimalPart)) {
			if (root->right != NULL)
				add(newIntegerPart, newDecimalPart, root->right);
			else {
				root->right = new Node;
				root->right->integerPart = newIntegerPart;
				root->right->decimalPart = newDecimalPart;
				root->right->right = NULL;
				root->right->left = NULL;
			}
		}
		else {
			if (root->left != NULL)
				add(newIntegerPart, newDecimalPart, root->left);
			else {
				root->left = new Node;
				root->left->integerPart = newIntegerPart;
				root->left->decimalPart = newDecimalPart;
				root->left->right = NULL;
				root->left->left = NULL;
			}
		}
	}
}

void printTree(Node* node, int indent = 0) {
	if (node != NULL) {
		cout << setw(indent) << (node->integerPart) << '.' << (node->decimalPart) << endl;
		if (node->left != NULL)
			printTree(node->left, indent + 4);
		if (node->right != NULL)
			printTree(node->right, indent + 4);
	}
}


int main() {
	Node* root = new Node;
	root->left = NULL;
	root->right = NULL;
	root->decimalPart = "6";
	root->integerPart = "1";
	add("1", "8", root);
	add("1", "4", root);
	add("1", "9", root);
	add("1", "7", root);
	add("1", "6", root);
	add("1", "0", root);

	printTree(root);
	getchar();
}