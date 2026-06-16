#include <iostream>
#include <string>
#include <regex>
#include <format>
#include "date.h"

int main()
{
    std::regex dateRegex(R"((\d{4})(\/|-)(0?[1-9]|1[0-2])(\2)(3[01]|[12][0-9]|0?[1-9])\b)");
    while (true)
    {
        std::cout << "Enter a date (year/month/day) (q=quit): ";
        std::string str;
        if (!getline(std::cin, str) || str == "q")
        {
            break;
        }
        std::smatch m;
        if (std::regex_match(str, m, dateRegex))
        {
            date myDate(stoi(m[3]), stoi(m[5]), stoi(m[1]));
            std::cout << myDate << " valid date" << std::endl;
        }
        else
        {
            std::cout << " invalid date" << std::endl;
        }
    }
    return 0;
}