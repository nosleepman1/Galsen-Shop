#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

inline string getCurrentDate()
{
    auto t = time(nullptr);
    auto tm = *localtime(&t);
    ostringstream oss;
    oss << put_time(&tm, "%Y%m%d%H%M%S");
    return oss.str();
}

#endif // PRODUCT_HPP