#include "binary-search-tree.h"
#include <queue>

#include <iostream>
using namespace std;

BinarySearchTree::Node::Node(DataType newval)
{
    left = NULL;
    right = NULL;
    val = newval;
}

int BinarySearchTree::getNodeDepth(Node* n) const
{
    if (n == NULL)
    {
        return 0;
    }
    else
    {
        int left_depth = getNodeDepth(n -> left);
        int right_depth = getNodeDepth(n -> right);
        if (left_depth > right_depth)
            return (left_depth + 1);
        else
            return (right_depth + 1);
    }
}

BinarySearchTree::BinarySearchTree()
{
    size_ = 0;
    root_ = NULL;
}

BinarySearchTree::~BinarySearchTree()
{
    if (root_ == NULL)
        return;
    queue < Node *> q;
    q.push(root_);
    while (q.empty() == false)
    {
        //print front of queue and then remove from queue
        Node* front_node = q.front();

        if (front_node -> left != NULL)
            q.push(front_node -> left);

        if (front_node -> right != NULL)
            q.push(front_node -> right);
        delete front_node;
        front_node = NULL;
        q.pop();
    }

}

unsigned int BinarySearchTree::size() const
{
    return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const
{
    Node* temp = root_;
    while (temp -> right != NULL)
    {
        temp = temp -> right;
    }
    return temp -> val;
}

BinarySearchTree::DataType BinarySearchTree::min() const
{
    Node* temp = root_;
    while (temp -> left != NULL)
    {
        temp = temp -> left;
    }
    return temp -> val;
}

unsigned int BinarySearchTree::depth() const
{
    return getNodeDepth(root_) - 1;
}

void BinarySearchTree::print() const
{
    if (root_ == NULL)
        return;
    queue < Node *> q;
    q.push(root_);
    while (q.empty() == false)
    {
        //print front of queue and then remove from queue
        Node* front_node = q.front();
        cout << front_node -> val << " ";
        q.pop();

        if (front_node -> left != NULL)
            q.push(front_node -> left);

        if (front_node -> right != NULL)
            q.push(front_node -> right);
    }
    cout << endl;
}

bool BinarySearchTree::exists(DataType val) const
{
    Node* temp = root_;
    while (temp != NULL)
    {
        if (temp -> val == val)
        {
            return true;
        }
        else if (temp -> val < val)
        {
            temp = temp -> right;
        }
        else
        {
            temp = temp -> left;
        }
    }
    return false;
}

BinarySearchTree::Node* BinarySearchTree::getRootNode()
{
    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress()
{
    return &root_;
}

bool BinarySearchTree::insert(DataType val)
{
    if (exists(val))
    {
        return false;
    }
    else if (size_ == 0)
    {
        root_ = new Node(val);
        size_++;
        return true;
    }
    else
    {
        Node* temp = root_;
        Node* trail = NULL;
        while (temp != NULL)
        {
            trail = temp;
            if (val < temp -> val)
            {
                temp = temp -> left;
            }
            else
            {
                temp = temp -> right;
            }
        }
        if (val < trail -> val)
        {
            trail -> left = new Node(val);
        }
        else
        {
            trail -> right = new Node(val);
        }
        size_++;
        return true;
    }
}

bool BinarySearchTree::remove(DataType val)
{
    if (root_ == NULL)
    {
        return false;
    }
    Node* temp = root_;
    Node* trail = NULL;
    while (temp != NULL && temp -> val != val)
    {
        trail = temp;
        if (temp -> val < val)
            temp = temp -> right;
        else
            temp = temp -> left;
    }
    //cout << temp -> val << endl;
    if (temp == NULL)
    {
        return false;
    }
    // no children
    if (temp -> left == NULL && temp -> right == NULL)
    {
        if (temp == root_) // if deleting the root node
        {
            root_ = NULL;
        }
        else
        {
            if (trail -> left == temp)
                trail -> left = NULL;
            else
                trail -> right = NULL;
        }
        delete temp;
        temp = NULL;
        size_--;
        return true;
    }
    // one child
    if (temp -> left == NULL || temp -> right == NULL)
    {
        Node* replace;

        if (temp -> left == NULL)
            replace = temp -> right;
        else
            replace = temp -> left;
        if (trail == NULL) // deleting root node
        {
            if (temp -> left == NULL)
                root_ = temp -> right;
            else
                root_ = temp -> left;
            delete temp;
            temp = NULL;
            size_--;
            return true;
        }
        if (temp == trail -> left)
        {
            trail -> left = replace;
            delete temp;
            temp = NULL;
            size_--;
            return true;
        }
        else
        {
            trail -> right = replace;
            delete temp;
            temp = NULL;
            size_--;
            return true;
        }
    }
    // two children
    else
    {
        //find predecessor
        Node* predecessor = temp -> left;
        Node* predecessor_prev = temp;
        while (predecessor -> right != NULL)
        {
            predecessor_prev = predecessor;
            predecessor = predecessor -> right;
        }
        temp -> val = predecessor -> val;
        // if successor is temp -> left
        if (predecessor_prev == temp)
            temp -> left = predecessor -> left;

        // regular case
        else //(successor_prev -> left == successor)
        {
            if (predecessor -> left == NULL)
                predecessor_prev -> right = NULL;
            else
                predecessor_prev -> right = predecessor -> left;
        }

        delete predecessor;
        predecessor = NULL;
        size_--;
        return true;
    }
}

void BinarySearchTree::updateNodeBalance(Node *n)
{
    if (n == NULL)
        n -> avlBalance = 0;
    else
        n -> avlBalance = getNodeDepth(n -> left) - getNodeDepth(n -> right);
}