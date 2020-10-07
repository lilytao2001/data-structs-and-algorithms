#include "doubly-linked-list.h"
#include <iostream>
using namespace std;

DoublyLinkedList::Node::Node(DataType data)
{
    value = data;
    next = NULL;
    prev = NULL;
}

DoublyLinkedList::DoublyLinkedList()
{
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
    while (head_ != NULL)
    {
        Node *temp = head_;
        head_ = head_ -> next;
        delete temp;
        temp = NULL;
    }
}

unsigned int DoublyLinkedList::size() const
{
    return size_;
}

unsigned int DoublyLinkedList::capacity() const
{
    return CAPACITY;
}

bool DoublyLinkedList::empty() const
{
    return size_ == 0;
}

bool DoublyLinkedList::full() const
{
    return size_ == CAPACITY;
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
    if (index >= 0 && index < size_)
    {
        Node *temp = head_;
        for (int i = 0; i < index; i++)
        {
            temp = temp -> next;
        }
        return temp -> value;
    }
    else
    {
        return tail_ -> value;
    }
}

unsigned int DoublyLinkedList::search(DataType value) const
{
    Node *temp = head_;
    for (int i = 0; i < size_; i++)
    {
        if (temp -> value == value)
        {
            return i;
        }
        else
        {
            temp = temp -> next;
        }
    }
    return size_;
}

void DoublyLinkedList::print() const
{
    if (size_ == 0)
    {
        return;
    }

        Node *temp = head_;
        for (int i = 0; i < size_; i++)
        {
            cout << temp -> value << "->";
            temp = temp -> next;
        }
        cout << endl;
        return;

}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
    Node *temp = head_;
    for (int i = 0; i < index; i++)
    {
        temp = temp -> next;
    }
    return temp;
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
    if (size_ == CAPACITY)
    {
        return false;
    }
    else if (index < 0 || index > size_)
    {
        return false;
    }
    else if (index == 0)
    {
        if (size_ == CAPACITY)
        {
            return false;
        }
        else if (size_ == 0)
        {
            head_ = new Node (value);
            tail_ = head_;
            size_++;
            return true;
        }
        else
        {
            Node *newNode = new Node (value);
            newNode -> next = head_;
            head_ -> prev = newNode;
            head_ = newNode;
            size_++;
            return true;
        }
    }
    else if (index == size_)
    {
        if (size_ == CAPACITY)
        {
            return false;
        }
        else if (size_ == 0)
        {
            tail_ = new Node (value);
            head_ = tail_;
            size_++;
            return true;
        }
        else
        {
            Node *temp = new Node (value);
            Node *current = tail_;
            tail_ = temp;
            current -> next = temp;
            temp -> prev = current;
            size_++;
            return true;
        }
    }
    else
    {
        Node *previous = head_;
        Node *current = head_->next;
        Node *temp = new Node (value);
        for (int i = 0; i < index - 1; i++) {
            previous = current;
            current = current -> next;
        }
        temp -> next = current;
        temp -> prev = previous;
        current -> prev = temp;
        previous -> next = temp;
        size_++;
        return true;
    }
}

bool DoublyLinkedList::insert_front(DataType value)
{
    if (size_ == CAPACITY)
    {
        return false;
    }
    else if (size_ == 0)
    {
        head_ = new Node (value);
        tail_ = head_;
        size_++;
        return true;
    }
    else
    {
        Node *newNode = new Node (value);
        newNode -> next = head_;
        head_ -> prev = newNode;
        head_ = newNode;
        size_++;
        return true;
    }
}

bool DoublyLinkedList::insert_back(DataType value)
{
    if (size_ == CAPACITY)
    {
        return false;
    }
    else if (size_ == 0)
    {
        tail_ = new Node (value);
        head_ = tail_;
        size_++;
        return true;
    }
    else
    {
        Node *temp = new Node (value);
        Node *current = tail_;
        tail_ = temp;
        current -> next = temp;
        temp -> prev = current;
        size_++;
        return true;
    }
}

bool DoublyLinkedList::remove(unsigned int index)
{
    Node *current = head_;
    Node *currentNext = head_ -> next;
    if (index < 0 || index >= size_)
    {
        return false;
    }
    else if (size_ == 0)
    {
        return false;
    }
    else if (index == 0)
    {
        head_ = head_ -> next;
        delete current;
        current = nullptr;
        size_--;
        return true;

    }
    else if (index == size_ - 1)
    {
        current = tail_;
        tail_ = tail_ -> prev;
        delete current;
        current = nullptr;
        size_--;
        return true;
    }
    else
    {
        for (int i = 0; i < index; i++)
        {
            current = currentNext;
            currentNext = currentNext -> next;
        }
        currentNext -> prev = current -> prev;
        Node *temp = current -> prev;
        temp -> next = currentNext;
        delete current;
        current = nullptr;
        size_--;
        return true;
    }
}

bool DoublyLinkedList::remove_front()
{
    if (size_ == 0)
    {
        return false;
    }
    if (size_ == 1)
    {
        Node *temp = tail_;
        tail_ = NULL;
        head_ = NULL;
        delete temp;
        temp = nullptr;
        size_--;
        return true;
    }
    else
    {
        Node *temp = head_;
        head_ = head_ -> next;
        delete temp;
        temp = nullptr;
        size_--;
        return true;
    }
}

bool DoublyLinkedList::remove_back()
{
    if (size_ == 0)
    {
        return false;
    }
    if (size_ == 1)
    {
        Node *temp = tail_;
        tail_ = NULL;
        head_ = NULL;
        delete temp;
        temp = nullptr;
        size_--;
        return true;
    }
    else
    {
        Node *temp = tail_;
        tail_ = tail_ -> prev;
        tail_ -> next = NULL;
        delete temp;
        temp = nullptr;
        size_--;
        return true;
    }
}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
    if (index < 0 || index > size_)
    {
        return false;
    }
    else
    {
        Node *temp = head_;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        temp -> value = value;
        return true;
    }
}

