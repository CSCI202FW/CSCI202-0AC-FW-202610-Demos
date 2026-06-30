#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include "linkedStack.h"

const int DEFAULT = 0;

int inputInt(std::string prompt, std::string err, bool (*valid)(int, int, int), int low = DEFAULT, int high = DEFAULT);
bool intInRange(int n, int lower, int upper);
bool intGTX(int n, int x, int = DEFAULT);
bool intLTX(int n, int x, int = DEFAULT);
bool intGTEQ(int n, int x, int = DEFAULT);
bool intLTEQ(int n, int x, int = DEFAULT);

void resetStream();
int factorial(int n);
long fibNum(long f[], long n);
long fibonacci(long f1, long f2, long n);

void moveDisks(int, char source, char destination, char spare);
void moveDisks(int disk, LinkedStack<int> &source, LinkedStack<int> &destination, LinkedStack<int> &spare, char, char, char);
void printTowers(LinkedStack<int> t1, LinkedStack<int> t2, LinkedStack<int> t3);

int main()
{
    int fact = inputInt("Enter a positive number: ", "Please enter a number greater than or equal to 0.", intGTEQ, 0);
    factorial(fact);
    long f[10];
    for (int i = 0; i < 10; i++)
    {
        f[i] = -1;
    }
    f[0] = 1;
    f[1] = 1;
    fibNum(f, 5);
    fibonacci(f[0], f[1], 5);
    LinkedStack<int> source(1);
    LinkedStack<int> destination(3);
    LinkedStack<int> spare(2);
    for (int i = 5; i > 0; i--)
    {
        source.push(i);
    }
    moveDisks(8, 'A', 'C', 'B');
    std::cout << std::endl
              << std::endl;
    moveDisks(5, source, destination, spare, 'A', 'C', 'B');
    return 0;
}

int inputInt(std::string prompt, std::string err, bool (*valid)(int, int, int), int low, int high)
{
    int num;
    std::cout << prompt;
    std::cin >> num;
    std::cout << std::endl;
    if (std::cin && valid(num, low, high))
    {
        return num;
    }
    if (!std::cin) //|| num < low || num > high
    {

        resetStream();
    }
    std::cout << err << std::endl;
    return inputInt(prompt, err, valid, low, high);
}

bool intInRange(int n, int lower, int upper)
{
    return n >= lower && n <= upper;
}

bool intGTX(int n, int x, int)
{
    return n > x;
}

bool intLTX(int n, int x, int)
{
    return n < x;
}

bool intGTEQ(int n, int x, int)
{
    return n >= x;
}

bool intLTEQ(int n, int x, int)
{
    return n <= x;
}

int factorial(int n)
{
    n = abs(n);
    if (n == 0)
    {
        return 1;
    }
    return n * factorial(n - 1);
}

long fibNum(long f[], long n)
{
    if (n <= 0)
    {
        return 0;
    }
    if (f[n - 1] != -1)
    {
        return f[n - 1];
    }
    f[n - 1] = fibNum(f, n - 1) + fibNum(f, n - 2);
    return f[n - 1];
}

long fibonacci(long f1, long f2, long n)
{
    if (n <= 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return f1;
    }
    if (n == 2)
    {
        return f2;
    }
    return fibonacci(f1, f2, n - 1) + fibonacci(f1, f2, n - 2);
}

void moveDisks(int count, char source, char destination, char spare)
{
    if (count > 0)
    {
        moveDisks(count - 1, source, spare, destination);
        std::cout << "Move disk " << count << " from " << source << " to " << destination << std::endl;
        moveDisks(count - 1, spare, destination, source);
    }
}

void moveDisks(int disk, LinkedStack<int> &source, LinkedStack<int> &destination, LinkedStack<int> &spare, char s, char d, char sp)
{
    if (disk == 0)
    {
        return;
    }
    moveDisks(disk - 1, source, spare, destination, s, sp, d);
    destination.push(source.pop());
    std::cout << "Move Disk" << disk << " from " << s << " to " << d << std::endl;
    printTowers(source, destination, spare);
    moveDisks(disk - 1, spare, destination, source, sp, d, s);
}

void printTowers(LinkedStack<int> t1, LinkedStack<int> t2, LinkedStack<int> t3)
{
    LinkedStack<int> *biggest;
    LinkedStack<int> *secondBiggest;
    LinkedStack<int> *smallest;
    biggest = &t1;
    if (t2 > t1)
    {

        if (t3 > t2)
        {
            biggest = &t3;
            secondBiggest = &t2;
            smallest = &t1;
        }
        else if (t3 > t1)
        {
            biggest = &t2;
            secondBiggest = &t3;
            smallest = &t1;
        }
        else
        {
            biggest = &t2;
            secondBiggest = &t1;
            smallest = &t3;
        }
    }
    else if (t3 > t1)
    {
        biggest = &t3;
        secondBiggest = &t1;
        smallest = &t2;
    }
    else if (t2 > t3)
    {
        secondBiggest = &t2;
        smallest = &t3;
    }
    else
    {
        secondBiggest = &t3;
        smallest = &t2;
    }
    int count = smallest->getCount();
    if (count < secondBiggest->getCount())
    {
        count = secondBiggest->getCount();
    }
    if (count < biggest->getCount())
    {
        count = biggest->getCount();
    }
    while (smallest->getCount() < count)
    {
        smallest->push(0);
    }
    while (secondBiggest->getCount() < count)
    {
        secondBiggest->push(0);
    }
    while (biggest->getCount() < count)
    {
        biggest->push(0);
    }
    std::cout << std::setfill('-');
    while (!t1.isEmptyStack() || !t2.isEmptyStack() || !t3.isEmptyStack())
    {
        int s = smallest->pop();
        int sp = secondBiggest->pop();
        int d = biggest->pop();
        if (s != 0)
        {
            std::cout << std::setw(s) << "-" << "\t\t\t";
        }
        else
        {
            std::cout << "|" << "\t\t\t";
        }
        if (sp != 0)
        {
            std::cout << std::setw(sp) << "-" << "\t\t\t";
        }
        else
        {
            std::cout << "|" << "\t\t\t";
        }
        if (d != 0)
        {
            std::cout << std::setw(d) << "-" << std::endl;
        }
        else
        {
            std::cout << "|" << std::endl;
        }
    }
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}