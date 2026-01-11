#if !defined(PRODUCT_HPP)
#define PRODUCT_HPP
#include <string>
using namespace std;

class Product
{
private:
    static int id;
    string code;
    string designation;
    double price;
    int quantity;

public:
    Product();
    ~Product();
};

Product::Product(/* args */)
{
}

Product::~Product()
{
}
