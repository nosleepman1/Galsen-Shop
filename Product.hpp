#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
#include <vector>

struct Product
{
    char code[6];
    char designation[100];
    double price;
    int quantity;
    int categoryId;
    char dateAdded[20];

    Product();
    Product(const std::string &code, const std::string &designation,
            double price, int quantity, int categoryId);
};

class ProductManager
{
private:
    static const std::string FILENAME;

public:
    static bool add(const Product &product);
    static bool update(const Product &product);
    static bool deleteProduct(const std::string &code);
    static Product findByCode(const std::string &code);
    static std::vector<Product> getAll();
    static bool exists(const std::string &code);
    static void displayAll();
    static bool updateStock(const std::string &code, int newQuantity);
    static bool decreaseStock(const std::string &code, int quantity);
};

#endif