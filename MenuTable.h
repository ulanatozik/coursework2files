

 
//
//  Header.h
//  mycoursework
//
//  Created by Ульяна Тозик on 15.09.24.
//

#ifndef MENUTABLE_H
#define MENUTABLE_H
 

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

#include "AccountsWork.h"
#include "Furniture.h"

using namespace std;

class SortProducts {
public:
    bool isSortByPrice(const Furniture& price_a, const Furniture& price_b) const;
    bool isSortByAmount(const Furniture& amount_a, const Furniture& amount_b) const;
    bool isSortByBrand(const Furniture& brand_a, const Furniture& brand_b) const;
    bool isSortByMaterial(const Furniture& material_a, const Furniture& material_b) const;
    bool isSortByColor(const Furniture& color_a, const Furniture& color_b) const;
};

// Класс для поиска продуктов
class SearchProducts {
public:
    void searchPrice() const;
    void searchAmount() const;
    void searchProductType() const;
    void searchMaterial() const;
    void searchBrand() const;
    void searchColor() const;
};

class Tables {
public:
    void headTable() const;
    void printAccountsTable(const vector<shared_ptr<User>>& accounts) const;
    void printUsersTable(const vector<shared_ptr<User>>& users) const;
    void printFurnitureTable(const vector<Furniture>& furnitureProducts) const;
};

class Menu {
public:
    virtual void startMenu() const;
    virtual void menuWorkWithUser() const;
    virtual void menuWorkWithFurniture() const;
    virtual void menuSort() const;
    virtual void menuSearch() const;
    virtual void menuUser() const;
    virtual void menuAdministrator() const;
    virtual void menuService() const;
    virtual void menuWorkWithFurnitureStart() const;
    virtual void menuWorkWithServices() const;
};


#endif // Header_h/
