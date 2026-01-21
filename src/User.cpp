#include "User.hpp"
#include "Utils.hpp"
#include <fstream>
#include <iostream>
#include <cstring>

const std::string UserManager::FILENAME = "USERS";

User::User() : id(0), role(ROLE_USER), blocked(false), firstLogin(true)
{
    memset(nom, 0, sizeof(nom));
    memset(prenom, 0, sizeof(prenom));
    memset(telephone, 0, sizeof(telephone));
    memset(login, 0, sizeof(login));
    memset(password, 0, sizeof(password));
}

User::User(int id, const std::string &nom, const std::string &prenom,
           const std::string &telephone, const std::string &login,
           const std::string &password, UserRole role)
    : id(id), role(role), blocked(false), firstLogin(true)
{

    strncpy(this->nom, nom.c_str(), sizeof(this->nom) - 1);
    this->nom[sizeof(this->nom) - 1] = '\0';

    strncpy(this->prenom, prenom.c_str(), sizeof(this->prenom) - 1);
    this->prenom[sizeof(this->prenom) - 1] = '\0';

    strncpy(this->telephone, telephone.c_str(), sizeof(this->telephone) - 1);
    this->telephone[sizeof(this->telephone) - 1] = '\0';

    strncpy(this->login, login.c_str(), sizeof(this->login) - 1);
    this->login[sizeof(this->login) - 1] = '\0';

    std::string encrypted = Utils::encrypt(password);
    strncpy(this->password, encrypted.c_str(), sizeof(this->password) - 1);
    this->password[sizeof(this->password) - 1] = '\0';
}

bool UserManager::add(const User &user)
{
    if (exists(user.login))
        return false;

    std::ofstream file(FILENAME, std::ios::binary | std::ios::app);
    if (!file)
        return false;

    file.write(reinterpret_cast<const char *>(&user), sizeof(User));
    file.close();
    return true;
}

bool UserManager::update(const User &user)
{
    std::vector<User> users = getAll();
    bool found = false;

    for (auto &u : users)
    {
        if (strcmp(u.login, user.login) == 0)
        {
            u = user;
            found = true;
            break;
        }
    }

    if (!found)
        return false;

    std::ofstream file(FILENAME, std::ios::binary | std::ios::trunc);
    if (!file)
        return false;

    for (const auto &u : users)
    {
        file.write(reinterpret_cast<const char *>(&u), sizeof(User));
    }

    file.close();
    return true;
}

User UserManager::authenticate(const std::string &login, const std::string &password)
{
    User user = findByLogin(login);

    if (strlen(user.login) == 0)
        return User();
    if (user.blocked)
        return User();

    std::string decrypted = Utils::decrypt(user.password);
    if (decrypted != password)
        return User();

    return user;
}

User UserManager::findByLogin(const std::string &login)
{
    std::ifstream file(FILENAME, std::ios::binary);
    User user;

    while (file.read(reinterpret_cast<char *>(&user), sizeof(User)))
    {
        if (strcmp(user.login, login.c_str()) == 0)
        {
            file.close();
            return user;
        }
    }

    file.close();
    return User();
}

std::vector<User> UserManager::getAll()
{
    std::vector<User> users;
    std::ifstream file(FILENAME, std::ios::binary);

    if (!file)
        return users;

    User user;
    while (file.read(reinterpret_cast<char *>(&user), sizeof(User)))
    {
        users.push_back(user);
    }

    file.close();
    return users;
}

bool UserManager::exists(const std::string &login)
{
    User u = findByLogin(login);
    return strlen(u.login) > 0;
}

void UserManager::displayAll()
{
    std::vector<User> users = getAll();

    std::cout << "\n===== LISTE DES UTILISATEURS =====\n";
    std::cout << "ID\tLogin\tNom\t\tPrenom\t\tRole\t\tBloque\n";
    std::cout << "----------------------------------------------------------------\n";

    for (const auto &u : users)
    {
        std::cout << u.id << "\t"
                  << u.login << "\t"
                  << u.nom << "\t\t"
                  << u.prenom << "\t\t"
                  << (u.role == ROLE_ADMIN ? "Admin" : "User") << "\t\t"
                  << (u.blocked ? "Oui" : "Non") << "\n";
    }

    std::cout << "----------------------------------------------------------------\n";
}

bool UserManager::blockUser(const std::string &login)
{
    User u = findByLogin(login);
    if (strlen(u.login) == 0)
        return false;

    u.blocked = true;
    return update(u);
}

bool UserManager::unblockUser(const std::string &login)
{
    User u = findByLogin(login);
    if (strlen(u.login) == 0)
        return false;

    u.blocked = false;
    return update(u);
}

bool UserManager::changePassword(const std::string &login, const std::string &newPassword)
{
    User u = findByLogin(login);
    if (strlen(u.login) == 0)
        return false;

    std::string encrypted = Utils::encrypt(newPassword);
    strncpy(u.password, encrypted.c_str(), sizeof(u.password) - 1);
    u.password[sizeof(u.password) - 1] = '\0';
    u.firstLogin = false;

    return update(u);
}