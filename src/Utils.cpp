#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <algorithm>

std::string Utils::getCurrentTimestamp()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(4) << (1900 + ltm->tm_year)
        << std::setw(2) << (1 + ltm->tm_mon)
        << std::setw(2) << ltm->tm_mday
        << std::setw(2) << ltm->tm_hour
        << std::setw(2) << ltm->tm_min
        << std::setw(2) << ltm->tm_sec;

    return oss.str();
}

std::string Utils::getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(4) << (1900 + ltm->tm_year)
        << std::setw(2) << (1 + ltm->tm_mon)
        << std::setw(2) << ltm->tm_mday;

    return oss.str();
}

std::string Utils::getDateTime(const std::string &format)
{
    time_t now = time(0);
    char buffer[80];
    strftime(buffer, sizeof(buffer), format.c_str(), localtime(&now));
    return std::string(buffer);
}

std::string Utils::encrypt(const std::string &password)
{
    std::string encrypted = password;
    for (size_t i = 0; i < encrypted.length(); i++)
    {
        encrypted[i] = encrypted[i] ^ 0x2A + (i % 7);
    }
    return encrypted;
}

std::string Utils::decrypt(const std::string &encrypted)
{
    std::string decrypted = encrypted;
    for (size_t i = 0; i < decrypted.length(); i++)
    {
        decrypted[i] = (decrypted[i] - (i % 7)) ^ 0x2A;
    }
    return decrypted;
}

bool Utils::isValidCode(const std::string &code)
{
    return code.length() == 5;
}

bool Utils::isValidLogin(const std::string &login)
{
    if (login.length() != 5)
        return false;
    for (char c : login)
    {
        if (!isupper(c) || !isalpha(c))
            return false;
    }
    return true;
}

int Utils::generateNextId(const std::string &filename, size_t structSize)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file)
        return 1;

    file.seekg(0, std::ios::end);
    int count = file.tellg() / structSize;
    file.close();

    return count + 1;
}

std::string Utils::getSecureInput()
{
    std::string input;
    std::cin >> input;
    return input;
}

void Utils::clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Utils::pause()
{
    std::cout << "\nAppuyez sur Entree pour continuer...";
    std::cin.ignore();
    std::cin.get();
}