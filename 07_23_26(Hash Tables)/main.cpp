#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unordered_set>
#include <string>
#include <cmath>
#include <vector>
#include <functional>
#include <random>

// M07 lab-b implement Universal Hashing #6 from https://www.geeksforgeeks.org/dsa/hash-functions-and-list-types-of-hash-functions/
// rerun both experiments
// submit the hash function and the experiment results.
const int HT_SIZE = 10007;
void setup();
int hash(int key);
int hashing_midsquare(long key, int size);
int hashing_multiplication(int key);
int folding(int key, int segments);
int main()
{
    setup();
    std::ifstream in("exp.txt");
    int ht[HT_SIZE] = {0};
    int collisions = 0;
    int count = 0;

    while (!in.eof())
    {
        int num;
        in >> num;
        int hashValue = hash(num);
        if (ht[hashValue] == 0)
        {
            ht[hashValue] = num;
            std::cout << num << " inserted at " << hashValue << std::endl;
            count++;
        }
        else
        {
            std::cout << num << " collided with " << ht[hashValue] << std::endl;
            collisions++;
        }
    }
    std::cout << "There were " << collisions << " collisions." << std::endl;
    std::cout << "There were " << count << " items inserted." << std::endl;
}

void setup()
{
    std::ofstream out("exp.txt");
    std::unordered_set<int> randomData;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 1000);
    std::uniform_int_distribution<int> distribution2(1, 9);
    std::uniform_int_distribution<int> distribution3(100000, 999999);
    while (randomData.size() < 5000)
    {
        int num = 0;
        num = distribution2(generator) * 100000 + distribution(generator);
        // num = distribution3(generator);
        randomData.insert(num);
    }
    bool begin = true;
    for (int i : randomData) // range based for loop or for-each for loop
    {
        if (begin)
        {
            out << i;
            begin = false;
        }
        else
        {
            out << std::endl
                << i;
        }
    }

    out.close();
}

int hash(int key)
{
    // return hashing_multiplication(key);
    // return folding(key, 2);
    return hashing_midsquare(key, 5);
    return key % HT_SIZE;
}

int hashing_midsquare(long key, int size)
{
    int squareLen = 0;
    int mid_pos = 0;
    unsigned long keysquare = key * key;
    std::string squaredStr = std::to_string(keysquare);
    squareLen = squaredStr.length();
    if (squareLen < size)
    {
        squaredStr = std::string(size - squareLen, '0') + squaredStr;
        squareLen = size;
    }
    mid_pos = (squareLen - size) / 2;
    std::string midDigits = squaredStr.substr(mid_pos, size);
    return std::stoi(midDigits) % HT_SIZE;
}

int hashing_multiplication(int key)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0, 1);
    static double A = distribution(generator);
    double hash;
    double fraction = std::modf(key * A, &hash);
    hash = HT_SIZE * fraction;
    hash = floor(hash);
    return static_cast<int>(hash);
}

int folding(int key, int segments)
{
    std::string keyStr = std::to_string(key);
    int segLen = keyStr.length() / segments;
    int fold = 0;
    int i = 0;
    while (i < keyStr.length())
    {
        fold += stoi(keyStr.substr(i, i + segLen));
        i = i + segLen;
    }
    return fold % HT_SIZE;
}
