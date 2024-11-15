//
//  WorkServices.cpp
//  coursework2
//
//  Created by Ульяна Тозик on 15.11.24.
//


#include "Furniture.h"
#include "AccountsWork.h"
#include "MenuTable.h"
#include "WorkServices.h"
#include <sstream>
 


void WorkWithServices::displayServices() const {
    ifstream ordersFile("orders.txt");
    if (!ordersFile) {
        cout << "Не удалось открыть файл заказов." << endl;
        return;
    }

    cout << "\n|=========================================================================================================================================================|"
         << "\n|                                       CПИСОК ЗАКАЗОВ УСЛУГ                                                                                              |"
    << "\n|=========================================================================================================================================================|" << endl;
    
    string line;
    int i = 1;

    while (getline(ordersFile, line)) {
        istringstream ss(line);
        string type, client, phone, address, details, quantity;

       
        getline(ss, type, ':');
        getline(ss, client, ',');
        getline(ss, phone, ',');
        getline(ss, address, ',');
        getline(ss, details, ',');
        getline(ss, quantity);

        cout << "| " << setw(2) << i++
             << " | " << left << setw(17) << type
             << " | " << left << setw(10) << client
             << " | " << left << setw(12) << phone
             << " | " << left << setw(18) << address
             << " | " << left << setw(20) << details
             << " | " << left << setw(10) << quantity << " |"
             << "\n|---------------------------------------------------------------------------------------------------------------------------------------------------------|"
             << endl;
    }

    ordersFile.close();
}

void WorkWithServices::orderServiceIndividual() const {
        Tables tableObj;
        ProgrammChecks checker;

        cout << "--Индивидуальный заказ мебели--" << endl;
        cout << "Введите ваши предпочтения для индивидуального заказа:" << endl;

         // Сбор информации о заказе
        string clientName;
        string clientPhone;
        string clientAddress;
        string productType;
        string material;
        string color;
        int quantity;
    
        cout << "Введите ваше имя для оформления заказа: ";
        cin.ignore(); // Очистка буфера перед вводом строки
        getline(cin, clientName);
    
        cout << "Введите ваш номер телефона: ";
        cin >> clientPhone;

        cout << "Введите ваш адрес: ";
        cin.ignore(); // Очистка буфера перед вводом строки
        getline(cin, clientAddress);

        cout << "Введите тип мебели (например, 'стол', 'стул', и т.д.): ";
        cin >> productType;
        
        cout << "Введите материал (например, 'дерево', 'металл', и т.д.): ";
        cin >> material;

        cout << "Введите цвет (например, 'белый', 'черный', и т.д.): ";
        cin >> color;

        cout << "Введите количество: ";
        quantity = checker.inputNumber(1, 100); // Ограничиваем количество

        // Здесь можно добавить дополнительные проверки на допустимость заказа
        cout << "Вы уверены, что хотите оформить индивидуальный заказ?" << endl;
        cout << "1. Да" << endl;
        cout << "2. Нет" << endl;
        cout << "Ваш выбор: ";

        int choice;
        cin >> choice;
        switch (choice) {
        case 1: {
            // Запись информации о заказе в файл
            ofstream ordersFile("orders.txt", ios::app); // Открываем файл в режиме добавления
            if (ordersFile.is_open()) {
                ordersFile << "Индивидуальный заказ:" << endl;
                ordersFile << "Имя клиента: " << clientName << ", Телефон: " << clientPhone
                           << ", Адрес: " << clientAddress << "Тип: " << productType << ", Материал: " << material
                           << ", Цвет: " << color << ", Количество: " << quantity << endl;
                ordersFile.close();
            } else {
                cout << "Не удалось открыть файл для записи." << endl;
            }

            cout << "Ваш индивидуальный заказ оформлен. Ожидайте ответа администратора для подтверждения." << endl;
            sleep(3);
            cout << "Заказ принят. Мы свяжемся с вами для уточнения деталей." << endl;

            break;
        }
        case 2: {
            cout << "Вы отменили индивидуальный заказ." << endl;
            return;
        }
        default: {
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
        }
}




void WorkWithServices::orderServiceRedo() const {
        Tables tableObj;
        ProgrammChecks checker;

        cout << "--Заказ на перетяжку мебели--" << endl;

        // Сбор информации о заказе
        string clientName;
        string clientPhone;
        string clientAddress;
        string furnitureType;
        string material;
        int quantity;

        cout << "Введите ваше имя для оформления заказа: ";
        cin.ignore(); // Очистка буфера перед вводом строки
        getline(cin, clientName);
        
        cout << "Введите ваш номер телефона: ";
        cin >> clientPhone;

        cout << "Введите ваш адрес: ";
        cin.ignore(); // Очистка буфера перед вводом строки
        getline(cin, clientAddress);

        cout << "Введите тип мебели для перетяжки (например, 'стул', 'диван', и т.д.): ";
        cin >> furnitureType;

        cout << "Введите желаемый материал для перетяжки (например, 'ткань', 'кожа', и т.д.): ";
        cin >> material;

        cout << "Введите количество предметов для перетяжки: ";
        quantity = checker.inputNumber(1, 100); // Ограничиваем количество

        cout << "Вы уверены, что хотите оформить заказ на перетяжку мебели?" << endl;
        cout << "1. Да" << endl;
        cout << "2. Нет" << endl;
        cout << "Ваш выбор: ";

        int choice;
        cin >> choice;
        switch (choice) {
        case 1: {
            // Запись информации о заказе в файл
            ofstream ordersFile("orders.txt", ios::app); // Открываем файл в режиме добавления
            if (ordersFile.is_open()) {
                ordersFile << "Заказ на перетяжку:" << endl;
                ordersFile << "Имя клиента: " << clientName << ", Телефон: " << clientPhone
                           << ", Адрес: " << clientAddress << ", Тип мебели: " << furnitureType
                           << ", Материал: " << material << ", Количество: " << quantity << endl;
                ordersFile.close();
            } else {
                cout << "Не удалось открыть файл для записи." << endl;
            }

            cout << "Ваш заказ на перетяжку мебели оформлен. Ожидайте ответа администратора для подтверждения." << endl;
            sleep(3);
            cout << "Заказ принят. Мы свяжемся с вами для уточнения деталей." << endl;

            break;
        }
        case 2: {
            cout << "Вы отменили заказ на перетяжку мебели." << endl;
            return;
        }
        default: {
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
        }
    }


void WorkWithServices::orderServiceFix() const {
        Tables tableObj;
        ProgrammChecks checker;

        cout << "--Заказ на ремонт мебели--" << endl;

        // Сбор информации о заказе
        string clientName;
        string clientPhone;
        string clientAddress;
        string furnitureType;
        string repairDetails;
        int quantity;

        cout << "Введите имя клиента: ";
        cin.ignore(); // Очистка буфера перед вводом строки
        getline(cin, clientName);
        
        cout << "Введите телефон клиента: ";
        cin >> clientPhone;

        cout << "Введите адрес клиента: ";
        cin.ignore(); // Очистка буфера перед вводом строки
        getline(cin, clientAddress);

        cout << "Введите тип мебели для ремонта (например, 'стул', 'стол', 'шкаф', и т.д.): ";
        cin >> furnitureType;

        cout << "Опишите детали ремонта (например, 'замена ножек', 'покраска', 'сборка', и т.д.): ";
        cin.ignore(); // Очистка буфера перед вводом строки
        getline(cin, repairDetails);

        cout << "Введите количество предметов для ремонта: ";
        quantity = checker.inputNumber(1, 100); // Ограничиваем количество

        cout << "Вы уверены, что хотите оформить заказ на ремонт мебели?" << endl;
        cout << "1. Да" << endl;
        cout << "2. Нет" << endl;
        cout << "Ваш выбор: ";

        int choice;
        cin >> choice;
        switch (choice) {
        case 1: {
            // Запись информации о заказе в файл
            ofstream ordersFile("orders.txt", ios::app); // Открываем файл в режиме добавления
            if (ordersFile.is_open()) {
                ordersFile << "Заказ на ремонт:" << endl;
                ordersFile << "Имя клиента: " << clientName << ", Телефон: " << clientPhone
                           << ", Адрес: " << clientAddress << ", Тип мебели: " << furnitureType
                           << ", Детали ремонта: " << repairDetails << ", Количество: " << quantity << endl;
                ordersFile.close();
            } else {
                cout << "Не удалось открыть файл для записи." << endl;
            }

            cout << "Ваш заказ на ремонт мебели оформлен. Ожидайте ответа администратора для подтверждения." << endl;
            sleep(3);
            cout << "Заказ принят. Мы свяжемся с вами для уточнения деталей." << endl;

            break;
        }
        case 2: {
            cout << "Вы отменили заказ на ремонт мебели." << endl;
            return;
        }
        default: {
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
        }
}

void WorkWithServices::editExistingServices() const {
    ifstream ordersFile("orders.txt");
    if (!ordersFile) {
        cout << "Не удалось открыть файл заказов." << endl;
        return;
    }

    // Чтение всех заказов и вывод их на экран
    vector<string> orders;
    string line;
    int i = 1;
    while (getline(ordersFile, line)) {
        orders.push_back(line);
        istringstream ss(line);
        string type, client, phone, address, details, quantity;
        getline(ss, type, ':');
        getline(ss, client, ',');
        getline(ss, phone, ',');
        getline(ss, address, ',');
        getline(ss, details, ',');
        getline(ss, quantity);

        cout << "| " << setw(2) << i++
             << " | " << left << setw(17) << type
             << " | " << left << setw(10) << client
             << " | " << left << setw(12) << phone
             << " | " << left << setw(18) << address
             << " | " << left << setw(20) << details
             << " | " << left << setw(10) << quantity << " |"
             << "\n|---------------------------------------------------------------------------------------------------------------------------------------------------------|"
             << endl;
    }
    ordersFile.close();

    // Запрос на редактирование
    int orderIndex;
    cout << "Введите номер заказа для редактирования (0 для отмены): ";
    cin >> orderIndex;

    if (orderIndex == 0 || orderIndex > orders.size()) {
        cout << "Некорректный номер заказа." << endl;
        return;
    }

    // Извлечение данных выбранного заказа
    istringstream ss(orders[orderIndex - 1]);
    string type, client, phone, address, details, quantity;
    getline(ss, type, ':');
    getline(ss, client, ',');
    getline(ss, phone, ',');
    getline(ss, address, ',');
    getline(ss, details, ',');
    getline(ss, quantity);

    // Вывод текущих данных заказа
    cout << "\nТекущие данные заказа:" << endl;
    cout << "Имя клиента: " << client << endl;
    cout << "Телефон: " << phone << endl;
    cout << "Адрес: " << address << endl;
    cout << "Детали заказа: " << details << endl;
    cout << "Количество: " << quantity << endl;

    // Запрос на изменение каждого поля
    string newClient, newPhone, newAddress, newDetails, newQuantity;
    cout << "\nВведите новое имя клиента (оставьте пустым для без изменений): ";
    cin.ignore(); // Очистка буфера
    getline(cin, newClient);
    if (!newClient.empty()) client = newClient;

    cout << "Введите новый телефон (оставьте пустым для без изменений): ";
    getline(cin, newPhone);
    if (!newPhone.empty()) phone = newPhone;

    cout << "Введите новый адрес (оставьте пустым для без изменений): ";
    getline(cin, newAddress);
    if (!newAddress.empty()) address = newAddress;

    cout << "Введите новые детали заказа (оставьте пустым для без изменений): ";
    getline(cin, newDetails);
    if (!newDetails.empty()) details = newDetails;

    cout << "Введите новое количество (оставьте пустым для без изменений): ";
    getline(cin, newQuantity);
    if (!newQuantity.empty()) quantity = newQuantity;

    // Сборка обновленного заказа
    string updatedOrder = type + ": " + client + ", " + phone + ", " + address + ", " + details + ", " + quantity;

    // Перезапись файла с изменениями
    ofstream ordersFileOut("orders.txt");
    if (!ordersFileOut) {
        cout << "Не удалось открыть файл для записи." << endl;
        return;
    }

    // Перезаписываем все заказы, включая обновленный
    for (int j = 0; j < orders.size(); ++j) {
        if (j == orderIndex - 1) {
            ordersFileOut << updatedOrder << endl; // Обновляем выбранный заказ
        } else {
            ordersFileOut << orders[j] << endl; // Оставляем остальные без изменений
        }
    }

    ordersFileOut.close();
    cout << "Заказ успешно обновлен!" << endl;
}
