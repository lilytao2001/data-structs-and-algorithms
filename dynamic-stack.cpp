#include "dynamic-stack.h"
#include <iostream>
using namespace std;


const DynamicStack::StackItem DynamicStack::EMPTY_STACK = 999;

DynamicStack::DynamicStack() {
    capacity_ = 16;
    size_ = 0;
    init_capacity_ = 16;
    items_ = new StackItem[capacity_];
}

DynamicStack::DynamicStack(unsigned int capacity){
    capacity_ = capacity;
    size_ = 0;
    init_capacity_ = capacity;
    items_ = new StackItem[capacity];
}

DynamicStack::~DynamicStack() {
    delete [] items_;
}

bool DynamicStack::empty() const {
    return size_ == 0;
}

int DynamicStack::size() const {
    return size_;
}
int DynamicStack::capacity() const {
    return capacity_;
}

void DynamicStack::push(StackItem value) {
    if (size_ != capacity_){
        items_[size_] = value;
        size_++;
    }
    else {
        capacity_ = capacity_ * 2;
        items_[size_] = value;
        size_++;
        // copy into new array]
        StackItem *new_array;
        StackItem *temp;

        new_array = new StackItem[capacity_];
        for (int i = 0; i < size_; i++) {
            new_array[i] = items_[i];
        }
        temp = items_;
        delete [] temp;
        items_ = new_array;
    }
}

DynamicStack::StackItem DynamicStack::pop() {
    if (empty()){
        return EMPTY_STACK;
    }
    else {
        int top_item = items_[size_ - 1];
        items_[size_ - 1] = 0;
        size_--;
        if (capacity_ <= init_capacity_) {
            // nothing
        }
        else if (size_ <= capacity_ / 4 ){
            capacity_ = capacity_ / 2;
            // copy into new array
            StackItem *new_array;
            StackItem *temp;

            new_array = new StackItem[capacity_];
            for (int i = 0; i < size_; i++) {
                new_array[i] = items_[i];
            }
            temp = items_;
            delete [] temp;
            items_ = new_array;
        }

        // new size
        // less than or equal to quarter array -- halved
        // less than original capacity -- nothing
        // else nothing
        return top_item;
    }
}

DynamicStack::StackItem DynamicStack::peek() const {
    if (empty()) {
        return EMPTY_STACK;
    }
    else {
        return items_[size_ - 1];
    }
}

void DynamicStack::print() const {
    for (int i = size_ - 1; i >= 0; i--){
        cout << items_[i] << " " ;
        if (i == 0) {
            cout << endl;
        }
    }
}