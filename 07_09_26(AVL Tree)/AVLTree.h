#ifndef AVLTREE_H
#define AVLTREE_H
#include "binarySearchTree.h"
#include "linkedStack.h"
#include <sstream>
#include <iostream>

template <class t>
class AVLTree : public BinarySearchTree
{
public:
    AVLTree(int (*comp)(const t &, const t &) = cmp);
    void deleteNode(const t &deleteItem);
    class Iterator
    {
    public:
        Iterator(BinaryNode<t> *currentNode = nullptr, bool pushSmaller = true);
        bool hasNext();
        Iterator operator++();
        t &operator*();
        bool operator==(const Iterator &other) const;
        bool operator!=(const Iterator &other) const;

    private:
        LinkedStack<BinaryNode<t> *> nodeStack;
        void pushLeftNodes(BinaryNode<t> *node, bool pushSmaller)
    };
    void insert(const t &insertItem);
    Iterator insertAVL(const t &insertItem);
    Iterator begin() { return Iterator(this->root); };
    Iterator end() { return Iterator(nullptr); };
    Iterator find(const t &searchItem) const;
    bool isBalanced();

private:
    void balanceFromLeft(BinaryNode<t> *&currentNode);
    void balanceFromRight(BinaryNode<t> *&currentNode);
    void rotateToLeft(BinaryNode<t> *&currentNode);
    void rotateToRight(BinaryNode<t> *&currentNode);
    void insertIntoAVL(BinaryNode<t> *&currentNode, BinaryNode<t> *newNode, bool &isTaller, Iterator &it);
    Iterator find(const t &searchItem, BinaryNode<t> *currentNode) const;
    int calculateBalance(BinaryNode<t> *currentNode);
    bool isBalanced(BinaryNode<t> *currentNode);
    void balanceTree(BinaryNode<t> *&currentNode);
    void deleteFromTree(BinaryNode<t> *&currentNode, const t &key);
    BinaryNode<t> *findMin(BinaryNode<t> *node) const;
};

#endif

template <class t>
inline void AVLTree<t>::insert(const t &insertItem)
{
    insertAVL(insertItem);
}

template <class t>
inline AVLTree<t>::Iterator AVLTree<t>::insertAVL(const t &insertItem)
{
    bool isTaller = false;
    BinaryNode<t> *newNode = new BinaryNode<t>(insertItem);
    Iterator it;
    insertIntoAVL(this->root, newNode, isTaller, it);

    return it;
}

template <class t>
inline void AVLTree<t>::insertIntoAVL(BinaryNode<t> *&currentNode, BinaryNode<t> *newNode, bool &isTaller, Iterator &it)
{
    if (currentNode == nullptr)
    {
        currentNode = newNode;
        isTaller = true;
        it = Iterator(currentNode, false);
    }
    else
    {
        int compareValue = this->compare(newNode->data, currentNode->data);
        if (compareValue == 0)
        {
            throw std::invalid_argument("No Duplicates Allowed");
        }
        else if (compareValue == -1)
        {
            insertIntoAVL(currentNode->lLink, newNode, isTaller, it);
            if (isTaller)
            {
                switch (currentNode->bfactor)
                {
                case -1:
                    balanceFromLeft(currentNode);
                    isTaller = false;
                    break;
                case 0:
                    currentNode->bfactor = -1;
                    isTaller = true;
                    break;
                case 1:
                    currentNode->bfactor = 0;
                    isTaller = false;
                }
            }
        }
        else
        {
            insertIntoAVL(currentNode->rLink, newNode, isTaller, it);
            if (isTaller)
            {
                switch (currentNode->bfactor)
                {
                case -1:
                    currentNode->bfactor = 0;
                    isTaller = false;
                    break;
                case 0:
                    currentNode->bfactor = 1;
                    isTaller = true;
                    break;
                case 1:
                    balanceFromRight(currentNode);
                    isTaller = false;
                    break;
                }
            }
        }
    }
}
