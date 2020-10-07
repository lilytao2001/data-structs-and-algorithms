#include "avl-tree.h";
#include <stack>
#include <iostream>

using namespace std;

bool AVLTree::insert(DataType val)
{
    int balance;
    BinarySearchTree::insert(val);
    //create stack
    stack <BinarySearchTree::Node *> s;
    //s.push(BinarySearchTree::getRootNode());
    //push everything into stack
    Node* temp = BinarySearchTree::getRootNode();
    while (temp != NULL)
    {
        if (temp -> val == val)
        {
            s.push(temp);
            break;
        }
        else if (temp -> val < val)
        {
            s.push(temp);
            temp = temp -> right;
        }
        else
        {
            s.push(temp);
            temp = temp -> left;
        }
    }
    bool imbalanceFound = false;
    while (!s.empty() && !imbalanceFound)
    {
        //BinarySearchTree::Node *temp = s.top();
        BinarySearchTree::updateNodeBalance(s.top());
        balance = s.top() -> avlBalance;
        if (balance != 0 && balance != 1 && balance != -1) // imbalance found
        {
            imbalanceFound = true;
            break;
        }
        s.pop();
    }
    if (imbalanceFound == false)
    {
        // do nothing
        return true;
    }
    else // imbalance
    {
        Node *input = s.top();
        s.pop();
        Node *previous = NULL;

        bool leftRight = false;
        bool rightLeft = false;

        if (!s.empty())
        {
            previous = s.top();
        }
        else
        {
            //nothing
        }
        //left left
        if (balance > 1 && val < input->left->val)
        {
            rightRotate(input, previous, rightLeft);
            return true;
        }
            //right right
        else if (balance < -1 && val > input->right->val)
        {
            leftRotate(input, previous, leftRight);
            return true;
        }
            //left right
        else if (balance > 1 && val > input->left->val)
        {
            leftRight = true;
            leftRotate(input -> left, input, leftRight);
            rightRotate(input, previous, rightLeft);
            return true;
        }
            //right left
        else if (balance < -1 && val < input->right->val)
        {
            rightLeft = true;
            rightRotate(input -> right, input, rightLeft);
            leftRotate(input, previous, leftRight);
            return true;
        }
    }
}
bool AVLTree::remove(DataType val)
{
    int balance;
    BinarySearchTree::remove(val);
    //create stack
    stack <BinarySearchTree::Node *> s;
    s.push(BinarySearchTree::getRootNode());
    //push everything into stack
    Node* temp = BinarySearchTree::getRootNode();
    while (temp != NULL)
    {
        if (temp -> val == val)
        {
            s.push(temp);
            break;
        }
        else if (temp -> val < val)
        {
            s.push(temp);
            temp = temp -> right;
        }
        else
        {
            s.push(temp);
            temp = temp -> left;
        }
    }
    bool imbalanceFound = false;
    while (!s.empty() && !imbalanceFound)
    {
        //BinarySearchTree::Node *temp = s.top();
        BinarySearchTree::updateNodeBalance(s.top());
        balance = s.top() -> avlBalance;
        if (balance != 0 && balance != 1 && balance != -1) // imbalance found
        {
            imbalanceFound = true;
            break;
        }
        s.pop();
    }
    if (imbalanceFound == false)
    {
        // do nothing
        return true;
    }
    else // imbalance
    {
        Node *input = s.top();
        s.pop();
        Node *previous = NULL;

        bool leftRight = false;
        bool rightLeft = false;

        if (!s.empty())
        {
            previous = s.top();
        }
        else
        {
            //nothing
        }
        //left left
        if (balance > 1 && val < input->left->val)
        {
            rightRotate(input, previous, rightLeft);
            return true;
        }
            //right right
        else if (balance < -1 && val > input->right->val)
        {
            leftRotate(input, previous, leftRight);
            return true;
        }
            //left right
        else if (balance > 1 && val > input->left->val)
        {
            leftRight = true;
            leftRotate(input -> left, input, leftRight);
            rightRotate(input, previous, rightLeft);
            return true;
        }
            //right left
        else if (balance < -1 && val < input->right->val)
        {
            rightLeft = true;
            rightRotate(input -> right, input, rightLeft);
            leftRotate(input, previous, leftRight);
            return true;
        }
    }
}
void AVLTree::rightRotate(Node *y, Node *prev, bool rightLeft)
{
    Node *x = y->left;
    Node *tree = x->right;
    //rotation
    x->right = y;
    y->left = tree;

    // set prev
    if (prev != NULL)
    {
        if (rightLeft)
            prev -> right = x;
        else
            prev -> right = x; // changed this
    }
    else //change root
    {
        Node **root = getRootNodeAddress();
        *root = x;
    }
}
void AVLTree::leftRotate(Node *x, Node *prev, bool leftRight)
{
    Node *y = x->right;
    Node *tree = y->left;
    //rotation
    y->left = x;
    x->right = tree;
    // set prev
    if (prev != NULL)
    {
        if (leftRight)
            prev->left = y;
        else
            prev->right = y;
    }
    else // change root
    {
        Node **root = getRootNodeAddress();
        *root = y;
    }
}