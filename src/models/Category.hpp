#ifndef CATEGORY__HPP
#define CATEGORY__HPP

#include <string>
using namespace std;

class Category
{
private:
    static int id;
    string libelle;

public:
    Category(string libelle)
    {
        this->libelle = libelle;
        id++;
    }

    ~Category() {}

    int getId()
    {
        return this->id;
    }

    string getLibelle()
    {
        return this->libelle;
    }
};

#endif // CATEGORY__HPP