#include "Menu.hpp"
#include "Utils.hpp"
#include "Category.hpp"
#include "Product.hpp"
#include "Sale.hpp"
#include <iostream>
#include <limits>

Menu::Menu(const User &user) : currentUser(user) {}

void Menu::displayMainMenu()
{
    std::cout << "\n========================================\n";
    std::cout << "   MANGUI DIEGEULOU SHOP\n";
    std::cout << "========================================\n";
    std::cout << "Utilisateur: " << currentUser.prenom << " " << currentUser.nom << "\n";
    std::cout << "Role: " << (currentUser.role == ROLE_ADMIN ? "Admin" : "Utilisateur") << "\n";
    std::cout << "========================================\n\n";
}

void Menu::displayAdminMenu()
{
    std::cout << "1.  Ajouter un utilisateur\n";
    std::cout << "2.  Liste des utilisateurs\n";
    std::cout << "3.  Bloquer/Debloquer un utilisateur\n";
    std::cout << "4.  Ajouter une categorie\n";
    std::cout << "5.  Liste des categories\n";
    std::cout << "6.  Ajouter un produit\n";
    std::cout << "7.  Modifier un produit\n";
    std::cout << "8.  Supprimer un produit\n";
    std::cout << "9.  Liste des produits\n";
    std::cout << "10. Mettre a jour le stock\n";
    std::cout << "11. Effectuer une vente\n";
    std::cout << "12. Imprimer l'etat d'aujourd'hui\n";
    std::cout << "0.  Deconnexion\n";
}

void Menu::displayUserMenu()
{
    std::cout << "1. Effectuer une vente\n";
    std::cout << "2. Liste des produits\n";
    std::cout << "3. Liste des categories\n";
    std::cout << "4. Imprimer l'etat d'aujourd'hui\n";
    std::cout << "0. Deconnexion\n";
}

void Menu::addUser()
{
    Utils::clearScreen();
    std::cout << "\n===== AJOUTER UN UTILISATEUR =====\n";

    std::string nom, prenom, telephone, login;
    int roleChoice;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Nom: ";
    std::getline(std::cin, nom);

    std::cout << "Prenom: ";
    std::getline(std::cin, prenom);

    std::cout << "Telephone: ";
    std::getline(std::cin, telephone);

    do
    {
        std::cout << "Login (5 caracteres majuscules): ";
        std::cin >> login;

        if (!Utils::isValidLogin(login))
        {
            std::cout << "Login invalide! Doit contenir exactement 5 lettres majuscules.\n";
        }
        else if (UserManager::exists(login))
        {
            std::cout << "Ce login existe deja!\n";
            login = "";
        }
    } while (login.empty() || !Utils::isValidLogin(login));

    std::cout << "Role (0=Utilisateur, 1=Admin): ";
    std::cin >> roleChoice;

    int id = Utils::generateNextId("USERS", sizeof(User));
    User newUser(id, nom, prenom, telephone, login, "passer123",
                 (roleChoice == 1) ? ROLE_ADMIN : ROLE_USER);

    if (UserManager::add(newUser))
    {
        std::cout << "\nUtilisateur ajoute avec succes!\n";
        std::cout << "Mot de passe par defaut: passer123\n";
    }
    else
    {
        std::cout << "\nErreur lors de l'ajout de l'utilisateur.\n";
    }

    Utils::pause();
}

void Menu::addCategory()
{
    Utils::clearScreen();
    std::cout << "\n===== AJOUTER UNE CATEGORIE =====\n";

    std::string libelle;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Libelle de la categorie: ";
    std::getline(std::cin, libelle);

    int id = CategoryManager::getNextId();
    Category cat(id, libelle);

    if (CategoryManager::add(cat))
    {
        std::cout << "\nCategorie ajoutee avec succes! (ID: " << id << ")\n";
    }
    else
    {
        std::cout << "\nErreur lors de l'ajout de la categorie.\n";
    }

    Utils::pause();
}

void Menu::addProduct()
{
    Utils::clearScreen();
    std::cout << "\n===== AJOUTER UN PRODUIT =====\n";

    CategoryManager::displayAll();

    std::string code, designation;
    double price;
    int quantity, categoryId;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    do
    {
        std::cout << "Code du produit (5 caracteres): ";
        std::cin >> code;

        if (!Utils::isValidCode(code))
        {
            std::cout << "Code invalide! Doit contenir exactement 5 caracteres.\n";
        }
        else if (ProductManager::exists(code))
        {
            std::cout << "Ce code existe deja!\n";
            code = "";
        }
    } while (code.empty() || !Utils::isValidCode(code));

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Designation: ";
    std::getline(std::cin, designation);

    std::cout << "Prix: ";
    std::cin >> price;

    std::cout << "Quantite en stock: ";
    std::cin >> quantity;

    do
    {
        std::cout << "ID de la categorie: ";
        std::cin >> categoryId;

        if (!CategoryManager::exists(categoryId))
        {
            std::cout << "Cette categorie n'existe pas!\n";
            categoryId = 0;
        }
    } while (categoryId == 0);

    Product product(code, designation, price, quantity, categoryId);

    if (ProductManager::add(product))
    {
        std::cout << "\nProduit ajoute avec succes!\n";
    }
    else
    {
        std::cout << "\nErreur lors de l'ajout du produit.\n";
    }

    Utils::pause();
}

void Menu::modifyProduct()
{
    Utils::clearScreen();
    std::cout << "\n===== MODIFIER UN PRODUIT =====\n";

    ProductManager::displayAll();

    std::string code;
    std::cout << "\nCode du produit a modifier: ";
    std::cin >> code;

    Product product = ProductManager::findByCode(code);
    if (strlen(product.code) == 0)
    {
        std::cout << "Produit non trouve!\n";
        Utils::pause();
        return;
    }

    std::string designation;
    double price;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Nouvelle designation (actuelle: " << product.designation << "): ";
    std::getline(std::cin, designation);

    std::cout << "Nouveau prix (actuel: " << product.price << "): ";
    std::cin >> price;

    strncpy(product.designation, designation.c_str(), sizeof(product.designation) - 1);
    product.price = price;

    if (ProductManager::update(product))
    {
        std::cout << "\nProduit modifie avec succes!\n";
    }
    else
    {
        std::cout << "\nErreur lors de la modification du produit.\n";
    }

    Utils::pause();
}

void Menu::deleteProduct()
{
    Utils::clearScreen();
    std::cout << "\n===== SUPPRIMER UN PRODUIT =====\n";

    ProductManager::displayAll();

    std::string code;
    std::cout << "\nCode du produit a supprimer: ";
    std::cin >> code;

    if (ProductManager::deleteProduct(code))
    {
        std::cout << "\nProduit supprime avec succes!\n";
    }
    else
    {
        std::cout << "\nProduit non trouve!\n";
    }

    Utils::pause();
}

void Menu::updateStock()
{
    Utils::clearScreen();
    std::cout << "\n===== METTRE A JOUR LE STOCK =====\n";

    ProductManager::displayAll();

    std::string code;
    int newQuantity;

    std::cout << "\nCode du produit: ";
    std::cin >> code;

    Product product = ProductManager::findByCode(code);
    if (strlen(product.code) == 0)
    {
        std::cout << "Produit non trouve!\n";
        Utils::pause();
        return;
    }

    std::cout << "Quantite actuelle: " << product.quantity << "\n";
    std::cout << "Nouvelle quantite: ";
    std::cin >> newQuantity;

    if (ProductManager::updateStock(code, newQuantity))
    {
        std::cout << "\nStock mis a jour avec succes!\n";
    }
    else
    {
        std::cout << "\nErreur lors de la mise a jour du stock.\n";
    }

    Utils::pause();
}

void Menu::listUsers()
{
    Utils::clearScreen();
    UserManager::displayAll();
    Utils::pause();
}

void Menu::blockUnblockUser()
{
    Utils::clearScreen();
    std::cout << "\n===== BLOQUER/DEBLOQUER UN UTILISATEUR =====\n";

    UserManager::displayAll();

    std::string login;
    int choice;

    std::cout << "\nLogin de l'utilisateur: ";
    std::cin >> login;

    std::cout << "1. Bloquer\n";
    std::cout << "2. Debloquer\n";
    std::cout << "Choix: ";
    std::cin >> choice;

    bool success = false;
    if (choice == 1)
    {
        success = UserManager::blockUser(login);
    }
    else if (choice == 2)
    {
        success = UserManager::unblockUser(login);
    }

    if (success)
    {
        std::cout << "\nOperation effectuee avec succes!\n";
    }
    else
    {
        std::cout << "\nErreur lors de l'operation.\n";
    }

    Utils::pause();
}

void Menu::processSale()
{
    Utils::clearScreen();
    std::cout << "\n===== EFFECTUER UNE VENTE =====\n";

    int saleId = SaleManager::getNextId();
    Sale sale(saleId, currentUser);

    bool addingItems = true;

    while (addingItems)
    {
        std::string code;
        int quantity;

        std::cout << "\nCode du produit: ";
        std::cin >> code;

        Product product = ProductManager::findByCode(code);

        if (strlen(product.code) == 0)
        {
            std::cout << "Produit non trouve!\n";
            continue;
        }

        if (product.quantity == 0)
        {
            std::cout << "Article en rupture de stock!\n";
            continue;
        }

        std::cout << "Produit: " << product.designation << "\n";
        std::cout << "Prix: " << product.price << " FCFA\n";
        std::cout << "Stock disponible: " << product.quantity << "\n";
        std::cout << "Quantite a vendre: ";
        std::cin >> quantity;

        if (quantity > product.quantity)
        {
            std::cout << "Quantite insuffisante en stock!\n";
            std::cout << "Voulez-vous prendre la quantite disponible ("
                      << product.quantity << ")? (1=Oui, 0=Non): ";
            int choice;
            std::cin >> choice;

            if (choice == 1)
            {
                quantity = product.quantity;
            }
            else
            {
                continue;
            }
        }

        if (sale.addItem(product, quantity))
        {
            std::cout << "\nProduit ajoute a la commande!\n";
        }

        std::cout << "\nAjouter un autre produit? (1=Oui, 0=Non): ";
        int choice;
        std::cin >> choice;

        addingItems = (choice == 1);
    }

    if (sale.getItems().empty())
    {
        std::cout << "\nAucun article dans la commande. Vente annulee.\n";
        Utils::pause();
        return;
    }

    if (SaleManager::saveSale(sale))
    {
        std::cout << "\n"
                  << SaleManager::generateReceipt(sale);
        std::cout << "\nVente enregistree avec succes!\n";
    }
    else
    {
        std::cout << "\nErreur lors de l'enregistrement de la vente.\n";
    }

    Utils::pause();
}

void Menu::printTodayReport()
{
    Utils::clearScreen();
    std::string today = Utils::getCurrentDate();

    if (SaleManager::printDailyReport(today))
    {
        std::cout << "\nRapport genere avec succes!\n";
    }
    else
    {
        std::cout << "\nErreur lors de la generation du rapport.\n";
    }

    Utils::pause();
}

void Menu::listProducts()
{
    Utils::clearScreen();
    ProductManager::displayAll();
    Utils::pause();
}

void Menu::listCategories()
{
    Utils::clearScreen();
    CategoryManager::displayAll();
    Utils::pause();
}

void Menu::run()
{
    int choice;

    do
    {
        Utils::clearScreen();
        displayMainMenu();

        if (currentUser.role == ROLE_ADMIN)
        {
            displayAdminMenu();
        }
        else
        {
            displayUserMenu();
        }

        std::cout << "\nChoix: ";
        std::cin >> choice;

        if (currentUser.role == ROLE_ADMIN)
        {
            switch (choice)
            {
            case 1:
                addUser();
                break;
            case 2:
                listUsers();
                break;
            case 3:
                blockUnblockUser();
                break;
            case 4:
                addCategory();
                break;
            case 5:
                listCategories();
                break;
            case 6:
                addProduct();
                break;
            case 7:
                modifyProduct();
                break;
            case 8:
                deleteProduct();
                break;
            case 9:
                listProducts();
                break;
            case 10:
                updateStock();
                break;
            case 11:
                processSale();
                break;
            case 12:
                printTodayReport();
                break;
            case 0:
                std::cout << "Deconnexion...\n";
                break;
            default:
                std::cout << "Choix invalide!\n";
                Utils::pause();
            }
        }
        else
        {
            switch (choice)
            {
            case 1:
                processSale();
                break;
            case 2:
                listProducts();
                break;
            case 3:
                listCategories();
                break;
            case 4:
                printTodayReport();
                break;
            case 0:
                std::cout << "Deconnexion...\n";
                break;
            default:
                std::cout << "Choix invalide!\n";
                Utils::pause();
            }
        }

    } while (choice != 0);
}