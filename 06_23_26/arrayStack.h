#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H
#include "stackADT.h"
#include <stdexcept>

template <class t>
class ArrayStack : public StackADT
{
public:
    ArrayStack(int = StackADT<t>::DEFAULT_STACK_SIZE);
    ArrayStack(const ArrayStack<t> &);
    const ArrayStack<t> &operator=(const ArrayStack<t> &);
    void initializeStack();
    bool isFullStack() const;
    bool isEmptyStack() const;
    void push(const t &);
    t peek() const;
    t &top();
    t pop();
    ~ArrayStack();

private:
    void copyStack(const ArrayStack<t> &);
    int stackTop;
    int maxStackSize;
    t **list;
};

template <class t>
inline ArrayStack<t>::ArrayStack(int max)
{
    if (max <= 0)
    {
        max = StackADT<t>::DEFAULT_STACK_SIZE;
    }
    maxStackSize = max;
    stackTop = 0;
    list = new t *[maxStackSize];
    for (int i = 0; i < maxStackSize; i++)
    {
        list[i] = nullptr;
    }
}
#endif

template <class t>
inline void ArrayStack<t>::copyStack(const ArrayStack<t> &stackToCopy)
{
    if (!isEmptyStack())
    {
        initializeStack();
    }
    if (this->maxStackSize < stackToCopy.maxStackSize)
    {
        delete[] this->list;
        this->maxStackSize = stackToCopy.maxStackSize;
        this->list = new t *[this->maxStackSize];
    }
    this->stackTop = stackToCopy.stackTop;
    for (int i = 0; i < stackTop; i++)
    {
        this->list[i] = new t(*(stackToCopy.list[i]));
    }
}
