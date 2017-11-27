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



Node* FindMin(Node* root)
{
    Node* temp = root;
    while (temp->left != NULL)
        temp = temp->left;
    return temp;
}


Node* Delete(Node *root, string integerPart, string decimalPart) {
  if (root == NULL) {
     return NULL;
  }
  if (integerPart < root->integerPart || (integerPart == root->integerPart && decimalPart < root->decimalPart)) { 
      root->left = Delete(root->left, integerPart,decimalPart);
  } else if (integerPart > root->integerPart || (integerPart == root->integerPart && decimalPart > root->decimalPart)) { 
      root->right = Delete(root->right,integerPart,decimalPart);
  } else {
    
     if (root->left == NULL && root->right == NULL) {
        delete(root); 
        root = NULL;
     }
    
     else if (root->left == NULL) {
        struct Node *temp = root; 
        root = root->right;
        delete temp;
     }
     
     else if (root->right == NULL) {
        struct Node *temp = root; 
        root = root->left;
        delete temp;
     }
     
     else {
        struct Node *temp = FindMin(root->right); 
        root->decimalPart = temp->decimalPart; 
        
		root->integerPart = temp->integerPart;
		root->right = Delete(root->right, temp->integerPart,temp->decimalPart); 
     }
  }
  return root; 
}



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
	add("1", "6", root);
	add("1", "0", root);

	if (search("2", "5", root))
		cout << "TAK" << endl;
	else
		cout << "NIE" << endl;
	printTree(root);
	getchar();
}
