#include "order.h"

Order::Order()
{
    donutList = nullptr;
    numDonuts = 0;
}

void Order::operator+(const Donut &d)
{
    numDonuts++;
    if (donutList == nullptr)
    {
        donutList = new Donut[numDonuts];
    }
    else
    {
        Donut *temp = donutList;
        donutList = new Donut[numDonuts];
        for (int i = 0; i < numDonuts - 1; i++)
        {
            donutList[i] = temp[i];
        }
        delete[] temp;
    }
    donutList[numDonuts - 1] = d;
}
Order::~Order()
{
    destroyList();
}

void Order::destroyList()
{
    delete[] donutList;
    donutList = nullptr;
}
