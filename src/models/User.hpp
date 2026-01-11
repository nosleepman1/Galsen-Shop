#if !defined(USER_HPP)
#define USER_HPP
#include <string>
using namespace std;

enum UserRole
{
    ROLE_USER = 0,
    ROLE_ADMIN = 1
};

class User
{
private:
    static int id;
    string nom;
    string prenom;
    string telephone;
    string login;
    string password;
    UserRole role;
    bool blocked;

public:
    User(string nom, string prenom, string telephone, string login, string password, UserRole role = ROLE_USER, bool blocked = false)
    {
        this->nom = nom;
        this->prenom = prenom;
        this->telephone = telephone;
        this->login = login;
        this->password = password;
        this->role = role;
        this->blocked = blocked;
        id++;
    }
    ~User();

    string getNom()
    {
        return this->nom;
    }
    string getPrenom()
    {
        return this->prenom;
    }
    string getTelephone()
    {
        return this->telephone;
    }
    string getLogin()
    {
        return this->login;
    }
    string getPassword()
    {
        return this->password;
    }
    UserRole getRole()
    {
        return this->role;
    }
    int getId()
    {
        return this->id;
    }
    bool isBlocked()
    {
        return this->blocked;
    }
};

#endif // USER_HPP
