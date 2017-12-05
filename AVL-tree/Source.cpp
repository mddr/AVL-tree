#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

struct Node {
	string integer;
	string decimal;
	Node *left;
	Node *right;
	int height;
	int weight;
};

int GetHeight(Node *N) {
	if (N == NULL)
		return 0;
	return N->height;
}

int MaxOfTwo(int a, int b) {
	return (a > b) ? a : b;
}

Node *RotateRight(Node*& a) {
	Node *b = a->left;
	Node *T2 = b->right;

	b->right = a;
	a->left = T2;

	a->height = MaxOfTwo(GetHeight(a->left), GetHeight(a->right)) + 1;
	b->height = MaxOfTwo(GetHeight(b->left), GetHeight(b->right)) + 1;

	a->weight = 0;
	b->weight = 0;

	return b;
}

Node *RotateLeft(Node*& a) {
	Node *b = a->right;
	Node *T2 = b->left;

	b->left = a;
	a->right = T2;

	a->height = MaxOfTwo(GetHeight(a->left), GetHeight(a->right)) + 1;
	b->height = MaxOfTwo(GetHeight(b->left), GetHeight(b->right)) + 1;

	a->weight = 0;
	b->weight = 0;

	return b;
}

Node* RotateLeftRight(Node*& a) {
	Node *b = a->left;
	Node *c = b->right;
	if (c==NULL)
		return c;
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

Node* RotateRightLeft(Node*& a) {
	Node *b = a->right;
	Node *c = b->left;
	if (c==NULL)
		return c;
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

int GetBalance(struct Node *N) {
	if (N == NULL)
		return 0;
	return GetHeight(N->left) - GetHeight(N->right);
}

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

int CompareNumbers(string int1, string dec1, string int2, string dec2) {
	if (CompareIntegerParts(int1, int2) > 0 || (CompareIntegerParts(int1, int2) == 0 && CompareDecimalParts(dec1, dec2) > 0))
		return 1;
	else if (CompareIntegerParts(int1, int2) < 0 || (CompareIntegerParts(int1, int2) == 0 && CompareDecimalParts(dec1, dec2) < 0))
		return -1;
	else
		return 0;
}

Node* NewNode(string i, string d) {
	Node* node = new Node;
	node->integer = i;
	node->decimal = d;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	node->weight = 0;
	return(node);
}

Node* Add(Node* node, string i, string d) {
	if (node == NULL)
		return NewNode(i, d);
	if (CompareNumbers(i, d, node->integer, node->decimal) > 0) {
		node->right = Add(node->right, i, d);
	}
	else if (CompareNumbers(i, d, node->integer, node->decimal) < 0) {
		node->left = Add(node->left, i, d);
	}
	node->weight = GetHeight(node->left) - GetHeight(node->right);

	if (node->weight == 2 && node->left->weight == -1) {
		return RotateLeftRight(node);
	}
	if (node->weight == 2 && node->left->weight == 1) {
		return RotateRight(node);
	}
	if (node->weight == -2 && node->right->weight == -1) {
		return RotateLeft(node);
	}
	if (node->weight == -2 && node->right->weight == 1) {
		return RotateRightLeft(node);
	}
	node->height = 1 + MaxOfTwo(GetHeight(node->right), GetHeight(node->left));
	return node;
}

Node *MinValueNode(Node* node) {
	struct Node* currentNode = node;

	while (currentNode->left != NULL)
		currentNode = currentNode->left;

	return currentNode;
}

Node* Delete(Node* node, string i, string d) {
	if (node == NULL)
		return node;
	if (CompareNumbers(i, d, node->integer, node->decimal) < 0) {
		node->left = Delete(node->left, i, d);
	}
	else if (CompareNumbers(i, d, node->integer, node->decimal) > 0) {
		node->right = Delete(node->right, i, d);
	}
	else {
		if (node->left == NULL && node->right == NULL) {
			delete node;
			node = NULL;
		}
		else if (node->left == NULL) {
			return node->right;
		}
		else if (node->right == NULL) {
			return node->left;
		}
		else {
			Node *tmp = MinValueNode(node->right);
			node->integer = tmp->integer;
			node->decimal = tmp->decimal;
			node->right = Delete(node->right, tmp->integer, tmp->decimal);
		}
	}
	if (node == NULL)
		return node;

	node->weight = GetHeight(node->left) - GetHeight(node->right);
	//node->height = 1 + MaxOfTwo(GetHeight(node->right), GetHeight(node->left));

	if (node->weight == 2 && node->left->weight == -1) {
		return RotateLeftRight(node);
	}
	if (node->weight == 2 && node->left->weight >= 0) {
		return RotateRight(node);
	}
	if (node->weight == -2 && node->right->weight <= 0) {
		return RotateLeft(node);
	}
	if (node->weight == -2 && node->right->weight == 1) {
		return RotateRightLeft(node);
	}	
	node->height = 1 + MaxOfTwo(GetHeight(node->right), GetHeight(node->left));
	return node;
}

void PrintTree(Node* node, int indent = 0, char c = 'k') {
	if (node != NULL) {
		cout << setw(indent) << c << ": " << (node->integer) << '.' << (node->decimal)<<" ["<<node->weight<<"]"<< endl;
		if (node->left != NULL)
			PrintTree(node->left, indent + 4, 'l');
		if (node->right != NULL)
			PrintTree(node->right, indent + 4, 'p');
	}
}

bool Search(string integerPart, string decimalPart, Node* root) {
	while (root != NULL) {
		if (CompareNumbers(integerPart, decimalPart, root->integer, root->decimal) == 0)
			return true;
		if (CompareNumbers(integerPart, decimalPart, root->integer, root->decimal) > 0)
			root = root->right;
		else
			root = root->left;
	}
	return false;
}

int CountIntegers(string integerPart, Node* root) {
	int counter = 0;
	if (root != NULL) {
		if (CompareIntegerParts(integerPart, root->integer) == 0) {
			counter++;
			if (root->right != NULL)
				counter += CountIntegers(integerPart, root->right);
			if (root->left != NULL)
				counter += CountIntegers(integerPart, root->left);
		}
		else {
			if (CompareIntegerParts(integerPart, root->integer) > 0) {
				if (root->right != NULL)
					counter += CountIntegers(integerPart, root->right);
			}
			else if (CompareIntegerParts(integerPart, root->integer) < 0) {
				if (root->left != NULL)
					counter += CountIntegers(integerPart, root->left);
			}
		}
	}
	return counter;
}

int main()
{
	Node* root = NULL;
	long long liczba;
	char skrypt;
	string number, decimal, integer;
	fstream plik("in.txt", ios::in);
	fstream out("out.txt", ios::out);

	if (plik.good()) {
		plik >> liczba;	
		for (long long b = 0; b < liczba; b++) {
			long long a;
			plik >> skrypt;
			plik >> number;
			for (a = 0; a < number.length(); a++) {
				if (number[a] == ',')
					break;
			}

			integer = number.substr(0, a);
			if (a != number.length())
				decimal = number.substr(a + 1, number.length());

			if (skrypt == 'W')
				root = Add(root,integer, decimal);
			if (skrypt == 'U')
				root = Delete(root, integer, decimal);
			if (skrypt == 'S')
				if (Search(integer, decimal, root) == true)
					out << "TAK" << endl;
				else
					out << "NIE" << endl;
			if (skrypt == 'L') {
				out << CountIntegers(integer, root) << endl;
			}
		}
	}
	else {
		cout << "blad odczytu" << endl;
	}

	return 0;
}