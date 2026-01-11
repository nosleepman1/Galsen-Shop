#include "Category.hpp"
#include "Utils.hpp"
#include <fstream>
#include <iostream>
#include <cstring>

const std::string CategoryManager::FILENAME = "CATEGORIES";

Category::Category() : id(0)
{
    memset(libelle, 0, sizeof(libelle));
}

Category::Category(int id, const std::string &libelle) : id(id)
{
    strncpy(this->libelle, libelle.c_str(), sizeof(this->libelle) - 1);
    this->libelle[sizeof(this->libelle) - 1] = '\0';
}

bool CategoryManager::add(const Category &category)
{
    std::ofstream file(FILENAME, std::ios::binary | std::ios::app);
    if (!file)
        return false;

    file.write(reinterpret_cast<const char *>(&category), sizeof(Category));
    file.close();
    return true;
}

Category CategoryManager::findById(int id)
{
    std::ifstream file(FILENAME, std::ios::binary);
    Category cat;

    while (file.read(reinterpret_cast<char *>(&cat), sizeof(Category)))
    {
        if (cat.id == id)
        {
            file.close();
            return cat;
        }
    }

    file.close();
    return Category();
}

std::vector<Category> CategoryManager::getAll()
{
    std::vector<Category> categories;
    std::ifstream file(FILENAME, std::ios::binary);

    if (!file)
        return categories;

    Category cat;
    while (file.read(reinterpret_cast<char *>(&cat), sizeof(Category)))
    {
        categories.push_back(cat);
    }

    file.close();
    return categories;
}

bool CategoryManager::exists(int id)
{
    Category cat = findById(id);
    return cat.id != 0;
}

void CategoryManager::displayAll()
{
    std::vector<Category> categories = getAll();

    std::cout << "\n===== LISTE DES CATEGORIES =====\n";
    std::cout << "ID\tLibelle\n";
    std::cout << "--------------------------------\n";

    for (const auto &cat : categories)
    {
        std::cout << cat.id << "\t" << cat.libelle << "\n";
    }

    std::cout << "--------------------------------\n";
}

int CategoryManager::getNextId()
{
    return Utils::generateNextId(FILENAME, sizeof(Category));
}