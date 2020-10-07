#include "circular-queue.h"
#include <iostream>
using namespace std;

const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = 999;

CircularQueue::CircularQueue() {
    capacity_ = 16;
    items_ = new QueueItem [capacity_];
    head_ = 0;
    tail_ = 0;
    size_ = 0;

}

CircularQueue::CircularQueue(unsigned int capacity) {
    capacity_ = capacity;
    items_ = new QueueItem [capacity_];
    head_ = 0;
    tail_ = 0;
    size_ = 0;
}

CircularQueue::~CircularQueue() {
    delete [] items_;
}

bool CircularQueue::empty() const {
    return size_ == 0;
}

bool CircularQueue::full() const {
    return size_ == capacity_;
}

int CircularQueue::size() const {
    return size_;
}

bool CircularQueue::enqueue(QueueItem value) {
    if (size_ == capacity_)
    {
        return false;
    }
    else
    {

        items_ [tail_] = value;
        if (tail_ == capacity_ - 1)
        {
            tail_ = 0;
        }
        else
        {
            tail_++;
        }
        size_++;
        return true;
    }
}

CircularQueue::QueueItem CircularQueue::dequeue() {
    if (empty())
    {
        return EMPTY_QUEUE;
    }
    else
    {
        QueueItem front_item = items_ [head_];
        items_[head_] = 0;
        if (head_ == capacity_ - 1)
        {
            head_ = 0;
        }
        else
        {
            head_++;
        }
        size_--;
        return front_item;
    }
}

CircularQueue::QueueItem CircularQueue::peek() const {
    if (empty())
    {
        return EMPTY_QUEUE;
    }
    else
    {
        return items_[head_];
    }
}

void CircularQueue::print() const {

   int counter = 0;
   int position = head_;
   while (counter < size_)
   {
       cout << items_[position] << " ";
       if (position == capacity_ - 1)
       {
           position = 0;
       }
       else
       {
           position++;
       }
       counter++;
   }

   cout << endl;
}

