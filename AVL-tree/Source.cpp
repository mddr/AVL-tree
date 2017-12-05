#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Node {
	string integerPart;
	string decimalPart;
	int height;
	int weight;
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

int MaxOfTwo(int a, int b) {
	return a > b ? a : b;
}

int GetHeight(Node *node) {
	if (node == NULL)
		return 0;
	return node->height;
}

Node* RotationRR(Node* a) {
	Node *b = a->left;

	a->left = b->right;
	b->right = a;

	b->weight = MaxOfTwo(GetHeight(b->left), GetHeight(b->right));
	a->weight = MaxOfTwo(GetHeight(a->left), GetHeight(a->right));

	return b;
}

Node* RotationLL(Node* a) {
	Node *b = a->right;
	Node *tmp = b->left;

	a->right = b->left;
	b->left = a;

	b->weight = MaxOfTwo(GetHeight(b->left), GetHeight(b->right));
	a->weight = MaxOfTwo(GetHeight(a->left), GetHeight(a->right));

	return b;
}

Node* RotationLR(Node *a) {
	Node *b = a->left;
	Node *c = b->right;

	b->right = c->left;
	a->left = c->right;
	c->left = b;
	c->right = a;

	switch (c->weight) {
	case -1:
		b->weight = 1;
		a->weight = 0;
		break;
	case 0:
		b->weight = 0;
		a->weight = 0;
		break;
	case 1:
		b->weight = 0;
		a->weight = -1;
		break;
	}
	c->weight = 0;

	return c;
}

Node* RotationRL(Node *a) {
	Node *b = a->right;
	Node *c = b->left;

	b->left = c->right;
	a->right = c->left;
	c->left = a;
	c->right = b;

	switch (c->weight) {
	case -1:
		b->weight = 0;
		a->weight = 1;
		break;
	case 0:
		b->weight = 0;
		a->weight = 0;
		break;
	case 1:
		b->weight = -1;
		a->weight = 0;
		break;
	}
	c->weight = 0;

	return c;
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

int CompareNumbers(string int1, string dec1, string int2, string dec2) {
	if (CompareIntegerParts(int1, int2) > 0 || (CompareIntegerParts(int1, int2) == 0 && CompareDecimalParts(dec1, dec2) > 0))
		return 1;
	else
		return -1;
}

Node* Add(string newIntegerPart, string newDecimalPart, Node* root) {
	if (root == NULL) {
		Node *tmp = new Node;
		tmp->integerPart = newIntegerPart;
		tmp->decimalPart = newDecimalPart;
		tmp->right = NULL;
		tmp->left = NULL;
		tmp->weight = 0;
		tmp->height = 1;
		return tmp;
	}
	if (CompareNumbers(newIntegerPart, newDecimalPart, root->integerPart, root->decimalPart) == 1) {
		root->right = Add(newIntegerPart, newDecimalPart, root->right);
	}
	else {
		root->left = Add(newIntegerPart, newDecimalPart, root->left);
	}

	root->height = 1 + MaxOfTwo(GetHeight(root->left), GetHeight(root->right));
	root->weight = GetHeight(root->left) - GetHeight(root->right);

	if (root->weight > 1 && CompareNumbers(newIntegerPart, newDecimalPart, root->left->integerPart, root->left->decimalPart) == -1) {
		return RotationRR(root);
	}
	if (root->weight < -1 && CompareNumbers(newIntegerPart, newDecimalPart, root->left->integerPart, root->left->decimalPart) == 1) {
		return RotationLL(root);
	}
	if (root->weight > 1 && CompareNumbers(newIntegerPart, newDecimalPart, root->left->integerPart, root->left->decimalPart) == 1) {
		return RotationLR(root);
	}
	if (root->weight < -1 && CompareNumbers(newIntegerPart, newDecimalPart, root->left->integerPart, root->left->decimalPart) == -1) {
		return RotationRL(root);
	}

	return root;
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
		cout << setw(indent) << c<<": "<< (node->integerPart) << '.' << (node->decimalPart)<<" ["<<(node->weight)<<"]" << endl;
		if (node->left != NULL)
			PrintTree(node->left, indent + 4, 'l');
		if (node->right != NULL)
			PrintTree(node->right, indent + 4, 'p');
	}
}


int main() {
	Node* root = NULL;
	root = Add("1", "8", root);
	root = Add("1", "4", root);
	root = Add("1", "9", root);
	root = Add("1", "85",root);
	root = Add("1", "851",root);	
	root = Add("1", "7", root);
	root = Add("1", "0", root);
	root = Add("1", "6", root);
/*
	 if (Search("2", "5", root))
	 	cout << "TAK" << endl;
	 else
	 	cout << "NIE" << endl;
*/
	//root = Add("20", "55", root);
	//root = Add("10", "0", root);
	//root = Add("30", "5", root);
	//root = Add("5", "0", root);
	//root = Add("15", "0", root);
	//root = Add("16", "0", root);

	PrintTree(root);
	/*cout<<"po usunieciu"<<endl;
	Delete(root,"1","9");
	PrintTree(root);*/
	getchar();
}
