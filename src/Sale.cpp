#include "Sale.hpp"
#include "Utils.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <sys/stat.h>

const std::string SaleManager::DIRECTORY = "BILLS";
int SaleManager::nextId = 1;

SaleItem::SaleItem(const std::string &code, const std::string &designation,
                   int quantity, double unitPrice)
    : productCode(code), designation(designation), quantity(quantity),
      unitPrice(unitPrice), total(quantity * unitPrice) {}

Sale::Sale(int id, const User &seller)
    : id(id), seller(seller), totalAmount(0.0)
{
    number = Utils::getCurrentTimestamp();
}

bool Sale::addItem(const Product &product, int quantity)
{
    if (quantity > product.quantity)
        return false;

    SaleItem item(product.code, product.designation, quantity, product.price);
    items.push_back(item);
    calculateTotal();

    return true;
}

void Sale::calculateTotal()
{
    totalAmount = 0.0;
    for (const auto &item : items)
    {
        totalAmount += item.total;
    }
}

double Sale::getTotal() const
{
    return totalAmount;
}

std::string Sale::getNumber() const
{
    return number;
}

int Sale::getId() const
{
    return id;
}

const std::vector<SaleItem> &Sale::getItems() const
{
    return items;
}

const User &Sale::getSeller() const
{
    return seller;
}

void SaleManager::initializeDirectory()
{
#ifdef _WIN32
    _mkdir(DIRECTORY.c_str());
#else
    mkdir(DIRECTORY.c_str(), 0777);
#endif
}

int SaleManager::getNextId()
{
    return nextId++;
}

std::string SaleManager::generateReceipt(const Sale &sale)
{
    std::ostringstream receipt;

    receipt << "========================================\n";
    receipt << "   MANGUI DIEGEULOU SHOP\n";
    receipt << "========================================\n";
    receipt << "Date: " << Utils::getDateTime("%d/%m/%Y %H:%M:%S") << "\n";
    receipt << "Numero: " << sale.getNumber() << "\n";
    receipt << "Vendeur: " << sale.getSeller().prenom << " "
            << sale.getSeller().nom << "\n";
    receipt << "========================================\n\n";

    receipt << std::left << std::setw(15) << "Produit"
            << std::setw(10) << "Qte"
            << std::setw(10) << "P.U."
            << std::setw(10) << "Total" << "\n";
    receipt << "----------------------------------------\n";

    for (const auto &item : sale.getItems())
    {
        receipt << std::left << std::setw(15) << item.designation
                << std::setw(10) << item.quantity
                << std::setw(10) << std::fixed << std::setprecision(2) << item.unitPrice
                << std::setw(10) << item.total << "\n";
    }

    receipt << "----------------------------------------\n";
    receipt << "TOTAL: " << std::fixed << std::setprecision(2)
            << sale.getTotal() << " FCFA\n";
    receipt << "========================================\n";
    receipt << "       Merci de votre visite!\n";
    receipt << "========================================\n";

    return receipt.str();
}

bool SaleManager::saveSale(const Sale &sale)
{
    initializeDirectory();

    std::ostringstream filename;
    filename << DIRECTORY << "/RECU_"
             << sale.getNumber() << "_"
             << sale.getId() << "_"
             << sale.getSeller().login << ".txt";

    std::ofstream file(filename.str());
    if (!file)
        return false;

    file << generateReceipt(sale);
    file.close();

    // Mise à jour des stocks
    for (const auto &item : sale.getItems())
    {
        ProductManager::decreaseStock(item.productCode, item.quantity);
    }

    return true;
}

bool SaleManager::printDailyReport(const std::string &date)
{
    std::ostringstream filename;
    filename << "ETAT_" << date << ".txt";

    std::ofstream report(filename.str());
    if (!report)
        return false;

    int totalArticles = 0;
    double totalAmount = 0.0;

    report << "========================================\n";
    report << "   ETAT DES VENTES DU " << date << "\n";
    report << "========================================\n\n";

    // Parcourir les fichiers de ventes du jour
    // Note: Cette implémentation est simplifiée
    // Dans une vraie application, il faudrait parcourir le répertoire BILLS

    report << "Nombre total d'articles vendus: " << totalArticles << "\n";
    report << "Montant total des ventes: " << std::fixed << std::setprecision(2)
           << totalAmount << " FCFA\n";
    report << "========================================\n";

    report.close();

    std::cout << "Rapport genere: " << filename.str() << "\n";
    return true;
}