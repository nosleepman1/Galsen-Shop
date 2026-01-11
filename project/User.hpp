#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>

enum UserRole
{
    ROLE_USER = 0,
    ROLE_ADMIN = 1
};

struct User
{
    int id;
    char nom[50];
    char prenom[50];
    char telephone[20];
    char login[6];
    char password[100];
    UserRole role;
    bool blocked;
    bool firstLogin;

    User();
    User(int id, const std::string &nom, const std::string &prenom,
         const std::string &telephone, const std::string &login,
         const std::string &password, UserRole role);
};

class UserManager
{
private:
    static const std::string FILENAME;

public:
    static bool add(const User &user);
    static bool update(const User &user);
    static User authenticate(const std::string &login, const std::string &password);
    static User findByLogin(const std::string &login);
    static std::vector<User> getAll();
    static bool exists(const std::string &login);
    static void displayAll();
    static bool blockUser(const std::string &login);
    static bool unblockUser(const std::string &login);
    static bool changePassword(const std::string &login, const std::string &newPassword);
};

#endif