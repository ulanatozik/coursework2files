//
//  AccountsWork.h
//  coursework2
//
//  Created by Ульяна Тозик on 15.11.24.
//

 
//
//  Header.h
//  mycoursework
//
//  Created by Ульяна Тозик on 15.09.24.
///

#ifndef ACCOUNTSWORK_H
#define ACCOUNTSWORK_H
#define service_hpp

#include <stdio.h>
 
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <unistd.h>
#include <termios.h>
#include <functional>
#include <locale.h>
#include <curses.h>
#include <memory>

#include "Furniture.h"

using namespace std;

class User {
protected:
    string login;
    string password;
    bool isAdmin;

public:
    User() = default;

    User(const std::string& login, const std::string& password, bool isAdmin)
        : login(login), password(password), isAdmin(isAdmin) {}

    virtual ~User() = default;

    virtual void displayInfo() const {
        cout << "Login: " << login << ", Admin: " << (isAdmin ? "Yes" : "No") << endl;
    }

    const string& getLogin() const { return login; }
    const string& getPassword() const { return password; }
    bool getIsAdmin() const { return isAdmin; }

    void setLogin(const string& newLogin) { login = newLogin; }
    void setPassword(const string& newPassword) { password = newPassword; }
    void setIsAdmin(bool newIsAdmin) { isAdmin = newIsAdmin; }

    // Перегрузка оператора присваивания
    User& operator=(const User& other) {
        if (this != &other) { // предотвращаем самоприсваивание
            login = other.login;
            password = other.password;
            isAdmin = other.isAdmin;
        }
        return *this;
    }
};


 
class AdminUser : public User {
public:
    AdminUser(const std::string& login, const std::string& password)
        : User(login, password, true) {}

    void displayInfo() const override {
        User::displayInfo();
        cout << "Role: Admin" << endl;
    }
};

 
class RegularUser : public User {
public:
    RegularUser(const std::string& login, const std::string& password)
        : User(login, password, false) {}

    void displayInfo() const override {
        User::displayInfo();
        cout << "Role: Regular User" << endl;
    }
};

// Класс для работы с аккаунтами
class WorkWithAccounts {
public:
    void addAccount() const;
    void deleteAccount() const;
    void editAccount() const;
    void approve() const;
};

// Класс для системы входа
class EnterSystem {
public:
    bool checkLoginAndPassword(const vector<shared_ptr<User>>& users, const string& login, const string& password) const;
    bool checkLoginAndPasswordRegist(const vector<shared_ptr<User>>& users, const string& login, const string& password, bool isAdmin) const;
    void authorization() const;
    void registration() const;
    string encrypt(const string& input) const;
    string decrypt(const string& input) const;
};


class WorkWithFiles {
public:
    void writeUsersToFile(const vector<shared_ptr<User>>& users) const; // Запись пользователей в файл
    vector<shared_ptr<User>> readUsersFromFile() const; // Чтение пользователей из файла
    void writeFurnitureToFile(const vector<Furniture>& furnitureProducts) const; // Запись мебели в файл
    vector<Furniture> readFurnitureFromFile() const; // Чтение мебели из файла
    void writeAccountsToFile(const vector<shared_ptr<User>>& accounts) const; // Запись аккаунтов в файл
    vector<shared_ptr<User>> readAccountsFromFile() const; // Чтение аккаунтов из файла
    void saveReportToFile(const std::string& reportContent, const std::string& filePath) const;
};

class ProgrammChecks {
public:
    string checkSize(const string& input);
    string checkString();
    bool isNumberNumeric();
    bool isNumberRangeCorrect(int number, int left_range, int right_range);
    int inputNumber(int left_range, int right_range);
};

 


#endif // Header_h
