#ifndef SEARCH_H
#define SEARCH_H

#include "binaryTree.h"
#include <stdexcept>

template <class t>
int cmp(const t &item1, const t &item2)
{
    if (item1 > item2)
    {
        return 1;
    }
    if (item1 == item2)
    {
        return 0;
    }
    if (item1 < item2)
    {
        return -1;
    }
    return 0;
}

template <class t>
class BinarySearchTree : public BinaryTree<t>
{
public:
    BinarySearchTree(int (*comp)(const t &, const t &) = cmp);
    void insert(const t &insertItem);
    bool search(const t &searchItem) const;
    void deleteNode(const t &deleteItem);

private:
    int (*compare)(const t &item1, const t &item2);
    void deleteFromTree(BinaryNode<t> *&currentNode);
    bool search(const t &searchItem, BinaryNode<t> *currentNode) const;
    void insert(BinaryNode<t> *&insertItem, BinaryNode<t> *&currentNode);
};

template <class t>
inline BinarySearchTree<t>::BinarySearchTree(int (*comp)(const t &, const t &))
{
    this->compare = comp;
}
#endif