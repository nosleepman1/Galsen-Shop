#ifndef CATEGORY_HPP
#define CATEGORY_HPP

#include <string>
#include <vector>

struct Category
{
    int id;
    char libelle[100];

    Category();
    Category(int id, const std::string &libelle);
};

class CategoryManager
{
private:
    static const std::string FILENAME;

public:
    static bool add(const Category &category);
    static Category findById(int id);
    static std::vector<Category> getAll();
    static bool exists(int id);
    static void displayAll();
    static int getNextId();
};

#endif