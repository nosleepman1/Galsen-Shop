#ifndef SALE_HPP
#define SALE_HPP

#include <string>
#include <vector>
#include "User.hpp"
#include "Product.hpp"

struct SaleItem
{
    std::string productCode;
    std::string designation;
    int quantity;
    double unitPrice;
    double total;

    SaleItem(const std::string &code, const std::string &designation,
             int quantity, double unitPrice);
};

class Sale
{
private:
    int id;
    std::string number;
    std::vector<SaleItem> items;
    double totalAmount;
    User seller;

public:
    Sale(int id, const User &seller);

    bool addItem(const Product &product, int quantity);
    void calculateTotal();
    double getTotal() const;
    std::string getNumber() const;
    int getId() const;
    const std::vector<SaleItem> &getItems() const;
    const User &getSeller() const;
};

class SaleManager
{
private:
    static const std::string DIRECTORY;
    static int nextId;

public:
    static bool saveSale(const Sale &sale);
    static std::string generateReceipt(const Sale &sale);
    static bool printDailyReport(const std::string &date);
    static void initializeDirectory();
    static int getNextId();
};

#endif