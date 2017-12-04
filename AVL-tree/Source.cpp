#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Node {
    string integerPart;
    string decimalPart;
    int weight;
    Node* right;
    Node* left;
};

int weight(struct Node* N)
{
    if (N == NULL)
        return 0;

    return N->weight;
}

int CompareIntegerParts(string a, string b)
{
    if (a.length() > b.length())
        return 1;
    if (a.length() < b.length())
        return -1;
    return a.compare(b);
}

int CompareDecimalParts(string a, string b)
{
    return a.compare(b);
}

Node* RotationRR(Node* a)
{
    Node* b = a->left;
    Node* tmp = b->left;

    a->left = tmp;
    b->right = a;

    b->weight = 1 + max(weight(b->left),
                        weight(b->right));
    a->weight = 1 + max(weight(a->left),
                        weight(a->right));

    return b;
}

Node* RotationLL(Node* a)
{
    Node* b = a->right;
    Node* tmp = b->left;

    a->right = tmp;
    b->left = a;

    b->weight = 1 + max(weight(b->left),
                        weight(b->right));
    a->weight = 1 + max(weight(a->left),
                        weight(a->right));

    return b;
}
/*
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
*/

Node* FindMin(Node* root)
{
    Node* temp = root;
    while (temp->left != NULL)
        temp = temp->left;
    return temp;
}

Node* Delete(Node* root, string integerPart, string decimalPart)
{
    if (root == NULL) {
        return NULL;
    }
    if (CompareIntegerParts(integerPart, root->integerPart) < 0 || (CompareDecimalParts(integerPart, root->integerPart) == 0
                                                                       && CompareDecimalParts(decimalPart, root->decimalPart) < 0)) {
        root->left = Delete(root->left, integerPart, decimalPart);
    }
    else if (CompareIntegerParts(integerPart, root->integerPart) > 0 || (CompareDecimalParts(integerPart, root->integerPart) == 0
                                                                            && CompareDecimalParts(decimalPart, root->decimalPart) > 0)) {
        root->right = Delete(root->right, integerPart, decimalPart);
    }
    else {

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
            struct Node* temp = FindMin(root->right);
            root->decimalPart = temp->decimalPart;
            root->integerPart = temp->integerPart;
            root->right = Delete(root->right, temp->integerPart, temp->decimalPart);
        }
    }
    return root;
}

int getBalance(struct Node* N)
{
    if (N == NULL)
        return 0;
    return weight(N->left) - weight(N->right);
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

Node* NewNode(string newIntegerPart, string newDecimalPart)
{
    Node* root = new Node;
    root->integerPart = newIntegerPart;
    root->decimalPart = newDecimalPart;
    root->right = NULL;
    root->left = NULL;
    root->weight = 1;

    return root;
}

Node* Add(string newIntegerPart, string newDecimalPart, Node* root)
{
    if (root == NULL)
        return NewNode(newIntegerPart, newDecimalPart);
    else {
        if (CompareIntegerParts(newIntegerPart, root->integerPart) > 0 || (CompareDecimalParts(newIntegerPart, root->integerPart) == 0
                                                                              && CompareDecimalParts(newDecimalPart, root->decimalPart) > 0)) {
            root->right = Add(newIntegerPart, newDecimalPart, root->right);
        }
        else
            root->left = Add(newIntegerPart, newDecimalPart, root->left);
    }

    root->weight = 1 + max(weight(root->left),
                           weight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && (CompareIntegerParts(newIntegerPart, root->left->integerPart) < 0 || (CompareDecimalParts(newIntegerPart, root->left->integerPart) == 0
                                                                                                && CompareDecimalParts(newDecimalPart, root->left->decimalPart) < 0)))
        return RotationRR(root);

    // Right Right Case
    if (balance < -1 && (CompareIntegerParts(newIntegerPart, root->right->integerPart) > 0 || (CompareDecimalParts(newIntegerPart, root->right->integerPart) == 0
                                                                                                  && CompareDecimalParts(newDecimalPart, root->right->decimalPart) > 0)))
        return RotationLL(root);

    // Left Right Case
    if (balance > 1 && (CompareIntegerParts(newIntegerPart, root->left->integerPart) > 0 || (CompareDecimalParts(newIntegerPart, root->left->integerPart) == 0
                                                                                                && CompareDecimalParts(newDecimalPart, root->left->decimalPart) > 0))) {
        root->left = RotationLL(root->left);
        return RotationRR(root);
    }

    // Right Left Case
    if (balance < -1 && (CompareIntegerParts(newIntegerPart, root->right->integerPart) < 0 || (CompareDecimalParts(newIntegerPart, root->right->integerPart) == 0
                                                                                                  && CompareDecimalParts(newDecimalPart, root->right->decimalPart) < 0))) {
        root->right = RotationRR(root->right);
        return RotationLL(root);
    }

    return root;
}

bool Search(string integerPart, string decimalPart, Node* root)
{
    while (root != NULL) {
        if (CompareIntegerParts(integerPart, root->integerPart) == 0 && CompareDecimalParts(decimalPart, root->decimalPart) == 0)
            return true;
        if (CompareIntegerParts(integerPart, root->integerPart) > 0 || (CompareDecimalParts(integerPart, root->integerPart) == 0
                                                                           && CompareDecimalParts(decimalPart, root->decimalPart) > 0))
            root = root->right;
        else
            root = root->left;
    }
    return false;
}

int CountIntegers(string integerPart, Node* root)
{
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
            else if (CompareIntegerParts(integerPart, root->integerPart) < 0) {
                if (root->left != NULL)
                    counter += CountIntegers(integerPart, root->left);
            }
        }
    }
    return counter;
}

void PrintTree(Node* node, int indent = 0, char c = 'k')
{
    if (node != NULL) {
        cout << setw(indent) << c << ": " << (node->integerPart) << '.' << (node->decimalPart) << "( " << (node->weight) << " )" << endl;
        if (node->left != NULL)
            PrintTree(node->left, indent + 4, 'l');
        if (node->right != NULL)
            PrintTree(node->right, indent + 4, 'p');
    }
}

int main()
{
    Node* root = NULL;
    /*Add("1", "8", root);
Add("1", "4", root);
Add("1", "9", root);
	Add("1","85",root);
	Add("1","851",root);	
Add("1", "7", root);
	Add("1", "6", root);
	Add("1", "0", root);*/

    // if (Search("2", "5", root))
    // 	cout << "TAK" << endl;
    // else
    // 	cout << "NIE" << endl;

    root = Add("20", "0", root);
    root = Add("10", "0", root);
    root = Add("30", "0", root);
    root = Add("25", "0", root);
    root = Add("40", "0", root);
    root = Add("27", "0", root);

    PrintTree(root);

    //	root = RotationLL(root);
    //	PrintTree(root);
    /*cout<<"po usunieciu"<<endl;
	Delete(root,"1","9");
	PrintTree(root);*/
    getchar();
}
