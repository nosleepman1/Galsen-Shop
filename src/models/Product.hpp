#if !defined(PRODUCT_HPP)
#define PRODUCT_HPP

#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include ""

using namespace std;

auto t = std::time(nullptr);
auto tm = *std::localtime(&t);

class Product
{
private:
    static int id;
    string code;
    string designation;
    double price;
    int quantity;
    string dateAdded;
    int categoryId;
    // current date

public:
    Product(string code, string designation, double price, int quantity, int categoryId, string dateAdded =)
    {
        this->code = code;
        this->designation = designation;
        this->price = price;
        this->quantity = quantity;
        this->categoryId = categoryId;
        this->dateAdded = dateAdded;
        id++;
    };

    ~Product();

    string getCode()
    {
        return this->code;
    }
    string getDesignation()
    {
        return this->designation;
    }
    double getPrice()
    {
        return this->price;
    }
    int getQuantity()
    {
        return this->quantity;
    }
    int getId()
    {
        return this->id;
    }
};

#endif // PRODUCT_HPP