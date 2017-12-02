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

int CompareIntegerParts(string a, string b) {
	if (a.length() > b.length())
		return 1;
	if (a.length() < b.length())
		return -1;
	return a.compare(b);
}

int CompareDecimalParts(string a, string b) {	
	return a.compare(b);
}

Node* FindMin(Node* root) {
    Node* temp = root;
    while (temp->left != NULL)
        temp = temp->left;
    return temp;
}

Node* Delete(Node *root, string integerPart, string decimalPart) {
  if (root == NULL) {
     return NULL;
  }
  if (CompareIntegerParts(integerPart, root->integerPart) < 0 || (CompareDecimalParts(integerPart,root->integerPart) == 0 
  		&& CompareDecimalParts(decimalPart, root->decimalPart) < 0)) { 
      root->left = Delete(root->left, integerPart,decimalPart);
  } else if (CompareIntegerParts(integerPart, root->integerPart) > 0 || (CompareDecimalParts(integerPart,root->integerPart) == 0 
  		&& CompareDecimalParts(decimalPart, root->decimalPart) > 0)) { 
      root->right = Delete(root->right,integerPart,decimalPart);
  } else {
    
     if (root->left == NULL && root->right == NULL) {
        delete root; 
        root = NULL;
     }
    
     else if (root->left == NULL) {
       // Node *temp = root; 
        root = root->right;
       // delete temp;
     }
     
     else if (root->right == NULL) {
      //  Node *temp = root; 
        root = root->left;
      //  delete temp;
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

void Add(string newIntegerPart, string newDecimalPart, Node*& root) {
	if (root != NULL) {
		if (CompareIntegerParts(newIntegerPart, root->integerPart) > 0 || (CompareDecimalParts(newIntegerPart,root->integerPart) == 0 
  				&& CompareDecimalParts(newDecimalPart, root->decimalPart) > 0)) {
			if (root->right != NULL)
				Add(newIntegerPart, newDecimalPart, root->right);
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
				Add(newIntegerPart, newDecimalPart, root->left);
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

bool Search(string integerPart, string decimalPart, Node* root) {
	while (root != NULL) {
		if (CompareIntegerParts(integerPart, root->integerPart) == 0 && CompareDecimalParts(decimalPart, root->decimalPart) == 0)
			return true;
		if (CompareIntegerParts(integerPart, root->integerPart) > 0 || (CompareDecimalParts(integerPart,root->integerPart) == 0 
  				&& CompareDecimalParts(decimalPart, root->decimalPart) > 0))
			root = root->right;
		else
			root = root->left;
	}
	return false;
}

int CountIntegers(string integerPart, Node* root) {
	int counter = 0;
	if (root != NULL) {
		if (CompareIntegerParts(integerPart, root->integerPart) == 0) {
			counter++;
			if (root->right != NULL)
				counter += CountIntegers(integerPart, root->right);
			if (root->left != NULL)
				counter += CountIntegers(integerPart, root->left);
		}
		else {
			if (CompareIntegerParts(integerPart, root->integerPart) > 0) {
				if (root->right != NULL)
					counter += CountIntegers(integerPart, root->right);
			}
			else
				if (CompareIntegerParts(integerPart, root->integerPart) < 0) {
					if (root->left != NULL)
						counter += CountIntegers(integerPart, root->left);
				}
		}
	}
	return counter;
}

void PrintTree(Node* node, int indent = 0, char c = 'k') {
	if (node != NULL) {
		cout << setw(indent) << c<<": "<< (node->integerPart) << '.' << (node->decimalPart) << endl;
		if (node->left != NULL)
			PrintTree(node->left, indent + 4, 'l');
		if (node->right != NULL)
			PrintTree(node->right, indent + 4, 'p');
	}
}


int main() {
	Node* root = NULL;
	Add("1", "8", root);
	Add("1", "4", root);
	Add("1", "9", root);
	Add("1","85",root);
	Add("1","851",root);	
	Add("1", "7", root);
	Add("1", "6", root);
	Add("1", "0", root);

	// if (Search("2", "5", root))
	// 	cout << "TAK" << endl;
	// else
	// 	cout << "NIE" << endl;
	PrintTree(root);
	cout<<"po usunieciu"<<endl;
	Delete(root,"1","9");
	PrintTree(root);
	getchar();
}
