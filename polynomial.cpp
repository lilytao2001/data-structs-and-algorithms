#include "polynomial.h"
//#include "doubly-linked-list.h"
using namespace std;
#include <iostream>

Polynomial::Polynomial(int *A, int size)
{
    size_ = size;
    list_ = new DoublyLinkedList;
    for (int i = 0; i < size; i++)
    {
        list_->insert_back(A[i]);
    }
}

Polynomial* Polynomial::add(Polynomial *rhs)
{
    //*this + *rhs
    int minTerms = 0;
    int maxTerms = 0;
    if (this->size_ < rhs->size_)
    {
        minTerms = this->size_;
        maxTerms = rhs->size_;
    }
    else
    {
        minTerms = rhs->size_;
        maxTerms = this->size_;
    }
    int sums[maxTerms];
    for (int i = 0; i < maxTerms; i++)
    {
        if (i < minTerms)
        {
            sums[i] = (rhs->list_->select(i) + this->list_->select(i));
        }
        else
        {
            if (this->size_ < rhs->size_)
            {
                sums[i] = (rhs->list_->select(i));
            }
            else
            {
                sums[i] = (this->list_->select(i));
            }
        }
    }
    Polynomial *result = new Polynomial(sums, maxTerms);
    return result;
}
Polynomial* Polynomial::sub(Polynomial *rhs)
{
    int minTerms = 0;
    int maxTerms = 0;
    if (this->size_ < rhs->size_)
    {
        minTerms = this->size_;
        maxTerms = rhs->size_;
    }
    else
    {
        minTerms = rhs->size_;
        maxTerms = this->size_;
    }
    int subtract[maxTerms];
    for (int i = 0; i < maxTerms; i++)
    {
        if (i < minTerms)
        {
            subtract[i] = (this->list_->select(i) - rhs->list_->select(i));
        }
        else
        {
            if (this->size_ < rhs->size_)
            {
                subtract[i] = (-1 * (rhs->list_->select(i)));
            }
            else
            {
                subtract[i] = (this->list_->select(i));
            }
        }
    }
    Polynomial *result = new Polynomial(subtract, maxTerms);
    return result;
}
Polynomial* Polynomial::mul(Polynomial *rhs)
{
    int terms = this->size_ + rhs->size_ - 1;
    int product[terms];
    for (int i = 0; i < terms; i++)
    {
        product[i] = 0;
    }
    for (int i = 0; i < this->size_; i++)
    {
        for (int j = 0; j < rhs->size_; j++)
        {
            product[i+j] = product[i+j] + this->list_->select(i) * rhs->list_->select(j);
        }
    }
    Polynomial *result = new Polynomial(product, terms);
    return result;
}
void Polynomial::print()
{
    for (int i = size_ - 1; i >= 0; i--)
    {
        if (list_->select(i) < 0)
        {
            cout << "(" << list_->select(i) << ")" << "x^" << i;
        }
        else
        {
            cout << list_->select(i) << "x^" << i;
        }
        if (i > 0)
        {
            cout << " + ";
        }
    }
    cout << endl;
}
