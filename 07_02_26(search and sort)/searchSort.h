#ifndef SEARCH_H
#define SEARCH_H

#include <fstream>
#include "unorderedLinkedList.h"

template <class t>
LinkedListIterator<t> seqSearch(UnorderedLinkedList<t> &list, const t &item, int &count)
{
    count = 0;
    bool found = false;
    LinkedListIterator<t> itRet;
    for (LinkedListIterator<t> it = list.begin(); it != list.end() && !found; ++it)
    {
        count++;
        if (*(*it) == item) //(*it) gives us a t*
        {
            found = true;
            itRet = it;
        }
    }
    return itRet;
}

#endif