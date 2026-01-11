#ifndef MENU_HPP
#define MENU_HPP

#include "User.hpp"

class Menu
{
private:
    User currentUser;

    void displayMainMenu();
    void displayAdminMenu();
    void displayUserMenu();

    // Fonctions Admin
    void addUser();
    void addCategory();
    void addProduct();
    void modifyProduct();
    void deleteProduct();
    void updateStock();
    void listUsers();
    void blockUnblockUser();

    // Fonctions User
    void processSale();
    void printTodayReport();

    // Fonctions communes
    void listProducts();
    void listCategories();

public:
    Menu(const User &user);
    void run();
};

#endif