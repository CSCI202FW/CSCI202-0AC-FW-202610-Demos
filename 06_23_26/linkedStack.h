#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H
#include "stackADT.h"
#include "node.h"
#include <stdexcept>

template <class t>
class LinkedStack : public StackADT
{
public:
    LinkedStack();
    LinkedStack(const LinkedStack<t> &);
    const LinkedStack<t> &operator=(const LinkedStack<t> &);
    void initializeStack();
    bool isFullStack() const;
    bool isEmptyStack() const;
    void push(const t &);
    t peek() const;
    t &top();
    t pop();
    ~LinkedStack();

private:
    void copyStack(const LinkedStack<t> &);
    node<t> *stackTop;
    int count;
};

template <class t>
inline LinkedStack<t>::LinkedStack()
{
    stackTop = nullptr;
    count = 0;
}
#endif

template <class t>
inline void LinkedStack<t>::copyStack(const LinkedStack<t> &stackToCopy)
{
    node<t> *newNode;
    node<t> *current;
    node<t> *last;
    if (!isEmptyStack())
    {
        initializeStack();
    }
    if (stackToCopy.isEmptyStack())
    {
        this->stackTop = nullptr;
        count = 0;
    }
    current = stackToCopy.stackTop;
    this->stackTop = new node<t>(current.data);
    last = this->stackTop;
    current = current->link;
    while (current != nullptr)
    {
        newNode = new node<t>(current.data);
        last->link = newNode;
        last = newNode;
        current = current->link;
    }
    this->count = stackToCopy.count;
}
