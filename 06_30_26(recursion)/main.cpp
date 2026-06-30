#include <iostream>
#include <string>
#include <limits>

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

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}