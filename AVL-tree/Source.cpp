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


void add(string newIntegerPart, string newDecimalPart, Node*& root) {
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
	else {
		root = new Node;
		root->integerPart = newIntegerPart;
		root->decimalPart = newDecimalPart;
		root->right = NULL;
		root->left = NULL;
	}
}

bool search(string integerPart, string decimalPart, Node* root) {
	while (root != NULL) {
		if (root->integerPart == integerPart && root->decimalPart == decimalPart)
			return true;
		if (integerPart > root->integerPart || (integerPart == root->integerPart && decimalPart > root->decimalPart))
			root = root->right;
		else
			root = root->left;
	}
	return false;
}

int countIntegers(string integerPart, Node* root) {
	int counter = 0;
	if (root != NULL) {
		if (integerPart == root->integerPart) {
			counter++;
			if (root->right != NULL)
				counter += countIntegers(integerPart, root->right);
			if (root->left != NULL)
				counter += countIntegers(integerPart, root->left);
		}
		else {
			if (integerPart > root->integerPart) {
				if (root->right != NULL)
					counter += countIntegers(integerPart, root->right);
			} else
				if (integerPart < root->integerPart) {
					if (root->left != NULL)
						counter += countIntegers(integerPart, root->left);
				}
		}
	}
	return counter;
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
	Node* root = NULL;
	add("1", "8", root);
	add("1", "4", root);
	add("1", "9", root);
	add("1", "7", root);
	add("2", "6", root);
	add("1", "0", root);

	if (search("2", "5", root))
		cout << "TAK" << endl;
	else
		cout << "NIE" << endl;
	cout << countIntegers("2", root) << endl;

	printTree(root);
	getchar();
}