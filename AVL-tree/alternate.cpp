#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;

struct Node {
    string integerPart;
    string decimalPart;

    Node* right;
    Node* left;
};

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

Node* NewNode(string newIntegerPart, string newDecimalPart)
{
    Node* root = new Node;
    root->integerPart = newIntegerPart;
    root->decimalPart = newDecimalPart;
    root->right = NULL;
    root->left = NULL;

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
        cout << setw(indent) << c << ": " << (node->integerPart) << '.' << (node->decimalPart) << endl;
        if (node->left != NULL)
            PrintTree(node->left, indent + 4, 'l');
        if (node->right != NULL)
            PrintTree(node->right, indent + 4, 'p');
    }
}

int main()
{
    int a;
    Node* root = NULL;
    int liczba;
    char skrypt;
    string number, decimal, integer;
    fstream plik("a.txt", ios::in);
    plik >> liczba;
    cout << liczba;

    for (int b = 0; b < liczba + 1; b++) {
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
            root = Add(integer, decimal, root);
        if (skrypt == 'U')
            root = Delete(root, integer, decimal);
        if (skrypt == 'S')
            if (Search(integer, decimal, root) == true)
                cout << "TAK" << endl;
            else
                cout << "NIE" << endl;
        if (skrypt == 'L') {

            cout << CountIntegers(integer, root) << endl;
        }
    }
    PrintTree(root);
    getchar();
}
