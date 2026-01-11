#include "Product.hpp"
#include "Utils.hpp"
#include "Category.hpp"
#include <fstream>
#include <iostream>
#include <cstring>

const std::string ProductManager::FILENAME = "PRODUCTS";

Product::Product() : price(0.0), quantity(0), categoryId(0)
{
    memset(code, 0, sizeof(code));
    memset(designation, 0, sizeof(designation));
    memset(dateAdded, 0, sizeof(dateAdded));
}

Product::Product(const std::string &code, const std::string &designation,
                 double price, int quantity, int categoryId)
    : price(price), quantity(quantity), categoryId(categoryId)
{

    strncpy(this->code, code.c_str(), sizeof(this->code) - 1);
    this->code[sizeof(this->code) - 1] = '\0';

    strncpy(this->designation, designation.c_str(), sizeof(this->designation) - 1);
    this->designation[sizeof(this->designation) - 1] = '\0';

    std::string date = Utils::getCurrentDate();
    strncpy(this->dateAdded, date.c_str(), sizeof(this->dateAdded) - 1);
    this->dateAdded[sizeof(this->dateAdded) - 1] = '\0';
}

bool ProductManager::add(const Product &product)
{
    if (exists(product.code))
        return false;

    std::ofstream file(FILENAME, std::ios::binary | std::ios::app);
    if (!file)
        return false;

    file.write(reinterpret_cast<const char *>(&product), sizeof(Product));
    file.close();
    return true;
}

bool ProductManager::update(const Product &product)
{
    std::vector<Product> products = getAll();
    bool found = false;

    for (auto &p : products)
    {
        if (strcmp(p.code, product.code) == 0)
        {
            p = product;
            found = true;
            break;
        }
    }

    if (!found)
        return false;

    std::ofstream file(FILENAME, std::ios::binary | std::ios::trunc);
    if (!file)
        return false;

    for (const auto &p : products)
    {
        file.write(reinterpret_cast<const char *>(&p), sizeof(Product));
    }

    file.close();
    return true;
}

bool ProductManager::deleteProduct(const std::string &code)
{
    std::vector<Product> products = getAll();
    std::ofstream file(FILENAME, std::ios::binary | std::ios::trunc);

    if (!file)
        return false;

    bool found = false;
    for (const auto &p : products)
    {
        if (strcmp(p.code, code.c_str()) != 0)
        {
            file.write(reinterpret_cast<const char *>(&p), sizeof(Product));
        }
        else
        {
            found = true;
        }
    }

    file.close();
    return found;
}

Product ProductManager::findByCode(const std::string &code)
{
    std::ifstream file(FILENAME, std::ios::binary);
    Product product;

    while (file.read(reinterpret_cast<char *>(&product), sizeof(Product)))
    {
        if (strcmp(product.code, code.c_str()) == 0)
        {
            file.close();
            return product;
        }
    }

    file.close();
    return Product();
}

std::vector<Product> ProductManager::getAll()
{
    std::vector<Product> products;
    std::ifstream file(FILENAME, std::ios::binary);

    if (!file)
        return products;

    Product product;
    while (file.read(reinterpret_cast<char *>(&product), sizeof(Product)))
    {
        products.push_back(product);
    }

    file.close();
    return products;
}

bool ProductManager::exists(const std::string &code)
{
    Product p = findByCode(code);
    return strlen(p.code) > 0;
}

void ProductManager::displayAll()
{
    std::vector<Product> products = getAll();

    std::cout << "\n===== LISTE DES PRODUITS =====\n";
    std::cout << "Code\tDesignation\t\tPrix\tQuantite\tCategorie\n";
    std::cout << "--------------------------------------------------------------\n";

    for (const auto &p : products)
    {
        Category cat = CategoryManager::findById(p.categoryId);
        std::cout << p.code << "\t"
                  << p.designation << "\t\t"
                  << p.price << "\t"
                  << p.quantity << "\t\t"
                  << cat.libelle << "\n";
    }

    std::cout << "--------------------------------------------------------------\n";
}

bool ProductManager::updateStock(const std::string &code, int newQuantity)
{
    Product p = findByCode(code);
    if (strlen(p.code) == 0)
        return false;

    p.quantity = newQuantity;
    return update(p);
}

bool ProductManager::decreaseStock(const std::string &code, int quantity)
{
    Product p = findByCode(code);
    if (strlen(p.code) == 0 || p.quantity < quantity)
        return false;

    p.quantity -= quantity;
    return update(p);
}