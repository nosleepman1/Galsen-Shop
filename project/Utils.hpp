#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <ctime>

namespace Utils
{
    // Génération de timestamps
    std::string getCurrentTimestamp();
    std::string getCurrentDate();
    std::string getDateTime(const std::string &format);

    // Cryptage simple
    std::string encrypt(const std::string &password);
    std::string decrypt(const std::string &encrypted);

    // Validation
    bool isValidCode(const std::string &code);
    bool isValidLogin(const std::string &login);

    // Génération automatique d'IDs
    int generateNextId(const std::string &filename, size_t structSize);

    // Utilitaires de saisie
    std::string getSecureInput();
    void clearScreen();
    void pause();
}

#endif