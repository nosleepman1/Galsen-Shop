#include <iostream>
#include <limits>
#include <string>
#include "User.hpp"
#include "Menu.hpp"
#include "Utils.hpp"

void initializeSystem()
{
    // Créer un admin par défaut s'il n'existe pas
    if (!UserManager::exists("ADMIN"))
    {
        User admin(1, "Systeme", "Admin", "0000000000", "ADMIN", "admin123", ROLE_ADMIN);
        admin.firstLogin = false;
        UserManager::add(admin);
        std::cout << "Admin par defaut cree (Login: ADMIN, Mot de passe: admin123)\n";
    }
}

bool handleFirstLogin(User &user)
{
    if (!user.firstLogin)
        return true;

    std::cout << "\n===== PREMIERE CONNEXION =====\n";
    std::cout << "Vous devez changer votre mot de passe.\n";

    std::string newPassword, confirmPassword;

    do
    {
        std::cout << "Nouveau mot de passe: ";
        std::cin >> newPassword;

        std::cout << "Confirmer le mot de passe: ";
        std::cin >> confirmPassword;

        if (newPassword != confirmPassword)
        {
            std::cout << "Les mots de passe ne correspondent pas!\n";
        }
    } while (newPassword != confirmPassword);

    if (UserManager::changePassword(user.login, newPassword))
    {
        std::cout << "\nMot de passe change avec succes!\n";
        user.firstLogin = false;
        Utils::pause();
        return true;
    }
    else
    {
        std::cout << "\nErreur lors du changement de mot de passe.\n";
        return false;
    }
}

bool login(User &currentUser)
{
    std::string login, password;

    Utils::clearScreen();
    std::cout << "\n========================================\n";
    std::cout << "   MANGUI DIEGEULOU SHOP\n";
    std::cout << "   SYSTEME DE GESTION DES VENTES\n";
    std::cout << "========================================\n\n";

    std::cout << "Login: ";
    std::cin >> login;

    std::cout << "Mot de passe: ";
    std::cin >> password;

    currentUser = UserManager::authenticate(login, password);

    if (strlen(currentUser.login) == 0)
    {
        std::cout << "\nLogin ou mot de passe incorrect!\n";
        Utils::pause();
        return false;
    }

    if (currentUser.blocked)
    {
        std::cout << "\nVotre compte est bloque! Contactez un administrateur.\n";
        Utils::pause();
        return false;
    }

    return handleFirstLogin(currentUser);
}

int main()
{
    initializeSystem();
    SaleManager::initializeDirectory();

    User currentUser;

    while (true)
    {
        if (login(currentUser))
        {
            Menu menu(currentUser);
            menu.run();
        }

        std::cout << "\nVoulez-vous vous reconnecter? (1=Oui, 0=Non): ";
        int choice;
        std::cin >> choice;

        if (choice != 1)
        {
            std::cout << "\nAu revoir!\n";
            break;
        }
    }

    return 0;
}