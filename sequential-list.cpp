#include "sequential-list.h"
#include <iostream>
using namespace std;

SequentialList::SequentialList(unsigned int cap)
{
    data_ = new DataType [cap];
    capacity_ = cap;
    size_ = 0;
}

SequentialList::~SequentialList()
{
    delete [] data_;
    data_ = nullptr;
}

unsigned int SequentialList::size() const
{
    return size_;
}

unsigned int SequentialList::capacity() const
{
    return capacity_;
}

bool SequentialList::empty() const
{
    return size_ == 0;
}

bool SequentialList::full() const
{
    return size_ == capacity_;
}

SequentialList::DataType SequentialList::select(unsigned int index) const
{
    if (index < size_ && index >= 0)
    {
        return data_[index];
    }
    else
    {
        cout << data_[size_ - 1] << endl;
        return data_[size_ - 1];
    }
}

unsigned int SequentialList::search(DataType val) const
{
    for (int i = 0; i < size_; i++)
    {
        if (data_[i] == val)
        {
            return i;
        }
    }
    return size_;
}

void SequentialList::print() const
{
    for (int i = 0; i < size_; i++)
    {
        cout << data_[i] << " ";
    }
    cout << endl;
}

bool SequentialList::insert(DataType val, unsigned int index)
{
    if (full())
    {
        return false;
    }
    if (index > size_ || index < 0)
    {
        return false;
    }
    else
    {
        for (int i = size_ - 1; i >= index  && i >= 0; i--)
        {
            data_[i + 1] = data_[i];
        }
        data_[index] = val;
        size_++;
        return true;
    }
}

bool SequentialList::insert_front(DataType val)
{
    if (full())
    {
        return false;
    }
    else
    {
        for (int i = size_ - 1; i >= 0; i--)
        {
            data_[i + 1] = data_[i];
        }
        data_[0] = val;
        size_++;
        return true;
    }
}

bool SequentialList::insert_back(DataType val)
{
    if (full())
    {
        return false;
    }
    else
    {
        data_[size_] = val;
        size_++;
        return true;
    }
}

bool SequentialList::remove(unsigned int index)
{
    if (index >= size_ || index < 0)
    {
        return false;
    }
    if (empty())
    {
        return false;
    }
    else
    {
        for (int i = index; i < size_; i++) {
            data_[i] = data_[i + 1];
        }
        data_[size() - 1] = NULL;
        size_--;
        return true;
    }
}

bool SequentialList::remove_front()
{
    if (empty())
    {
        return false;
    }
    else
    {
        for (int i = 0; i < size_; i++)
        {
            data_[i] = data_[i + 1];
        }
        size_--;
        return true;
    }
}

bool SequentialList::remove_back()
{
    if (empty())
    {
        return false;
    }
    else
    {
        data_[size() - 1] = NULL;
        size_--;
        return true;
    }
}

bool SequentialList::replace(unsigned int index, DataType val)
{
    if (empty())
    {
        return false;
    }
    if (index >= size_ || index < 0)
    {
        return false;
    }
    else
    {
        data_[index] = val;
        return true;
    }
}

