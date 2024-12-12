

 
//
//  Header.h
//  mycoursework
//
//  Created by Ульяна Тозик on 15.09.24.
//

#ifndef WORKSERVICES_H
#define WORKSERVICES_H
 

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

using namespace std;

class WorkWithServices
{
public:
    void orderServiceIndividual() const;
    void orderServiceRedo() const;
    void orderServiceFix() const;
    void displayServices() const;
    void editExistingServices() const;
};

struct Order {
    string type;       // Тип заказа (например, "индивидуальный", "перетяжка", "ремонт")
    string client;     // Имя клиента
    string phone;      // Телефон клиента
    string address;    // Адрес клиента
    string details;    // Детали заказа
    int quantity;      // Количество

    // Для сортировки заказов по типу
    bool operator<(const Order& other) const {
        return type < other.type;
    }
};

#endif // Header_h
