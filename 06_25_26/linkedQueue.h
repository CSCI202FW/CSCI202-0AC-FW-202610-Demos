#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H
#include "queueADT.h"
#include "node.h"

template <class t>
class LinkedQueue : public QueueADT<t>
{
public:
    LinkedQueue();
    LinkedQueue(const LinkedQueue<t> &);
    const LinkedQueue<t> &operator=(const LinkedQueue<t> &);
    ~LinkedQueue();
    bool isEmptyQueue() const;
    bool isFullQueue() const;
    void initializeQueue();
    t front() const;
    t back() const;
    void enqueue(const t &queueElement);
    t dequeue();

private:
    node<t> *queueFront;
    node<t> *queueRear;
    void copyQueue(const LinkedQueue<t> &);
};

#endif

template <class t>
inline LinkedQueue<t>::LinkedQueue()
{
    queueFront = nullptr;
    queueRear = nullptr;
}

template <class t>
inline LinkedQueue<t>::~LinkedQueue()
{
    initializeQueue();
}

template <class t>
inline bool LinkedQueue<t>::isEmptyQueue() const
{
    return queueFront == nullptr;
}

template <class t>
inline bool LinkedQueue<t>::isFullQueue() const
{
    return false;
}

template <class t>
inline void LinkedQueue<t>::initializeQueue()
{
    if (!isEmptyQueue())
    {
        node<t> *temp;
        while (this->queueFront != nullptr)
        {
            temp = queueFront;
            queueFront = queueFront->link;
            delete temp;
        }
        queueRear = nullptr;
    }
}

template <class t>
inline t LinkedQueue<t>::front() const
{
    if (isEmptyQueue())
    {
        throw std::out_of_range("Cannot get the first item of an empty queue");
    }
    return queueFront->data;
}

template <class t>
inline t LinkedQueue<t>::back() const
{
    if (isEmptyQueue())
    {
        throw std::out_of_range("Cannot get the last item of an empty queue");
    }
    return queueRear->data;
}
