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
    setlocale(LC_ALL, "ru_RU.UTF-8");

    string filepath = "/Users/ulanatozik/Материалы по учебе (БГУИР)/2 курс/Курсовая 1 семестр/курсовая код/coursework2/coursework2/list_services3.txt";
    ifstream ordersFile(filepath);
    if (!ordersFile) {
        cout << "Не удалось открыть файл заказов." << endl;
        return;
    }

    vector<Order> orders;
    string line;

    // Чтение всех заказов из файла
    while (getline(ordersFile, line)) {
        istringstream ss(line);
        string type, client, phone, address, details, quantityStr;
        int quantity = 0;

        // В зависимости от формата данных парсим нужную информацию
        if (line.find("Индивидуальный заказ:") != string::npos) {
            type = "Индивидуальный заказ";
        } else if (line.find("Заказ на перетяжку:") != string::npos) {
            type = "Перетяжка";
        } else if (line.find("Заказ на ремонт:") != string::npos) {
            type = "Ремонт";
        }

        // Получение данных клиента и прочего
        getline(ss, client, ':');
        getline(ss, phone, ',');
        getline(ss, address, ',');
        getline(ss, details, ',');
        getline(ss, quantityStr);

        // Обработка строки с количеством
        try {
            quantity = stoi(quantityStr);
        } catch (const std::invalid_argument& e) {
            cout << "Ошибка: некорректное количество в заказе: " << quantityStr << endl;
            quantity = 0;  // Присваиваем дефолтное значение
        } catch (const std::out_of_range& e) {
            cout << "Ошибка: количество слишком большое: " << quantityStr << endl;
            quantity = 0;  // Присваиваем дефолтное значение
        }

        orders.push_back({type, client, phone, address, details, quantity});
    }

    // Сортировка заказов по типу
    sort(orders.begin(), orders.end());

    // Вывод заголовка таблицы с корректными разделителями
    cout << "| " << setw(15) << "Номер заказа"
         << " | " << setw(20) << "Тип заказа"
         << " | " << setw(20) << "Клиент"
         << " | " << setw(15) << "Телефон"
         << " | " << setw(25) << "Адрес"
         << " | " << setw(25) << "Детали заказа"
         << " | " << setw(12) << "Количество"
         << " |" << endl;
    cout << "|------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;

    // Вывод заказов
    int i = 1;
    for (const auto& order : orders) {
        cout << "| " << setw(15) << i++
             << " | " << setw(20) << order.type
             << " | " << setw(20) << order.client
             << " | " << setw(15) << order.phone
             << " | " << setw(25) << order.address
             << " | " << setw(25) << order.details
             << " | " << setw(12) << order.quantity
             << " |" << endl;
        cout << "|------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
    }

    ordersFile.close();
}



void WorkWithServices::orderServiceIndividual() const {
    ProgrammChecks checker;

    cout << "--Индивидуальный заказ мебели--" << endl;
    cout << "Введите ваши предпочтения для индивидуального заказа:" << endl;

    string clientName, clientPhone, clientAddress, productType, material, color;
    int quantity;

    cout << "Введите ваше имя для оформления заказа: ";
    cin.ignore();
    getline(cin, clientName);

    cout << "Введите ваш номер телефона: ";
    cin >> clientPhone;

    cout << "Введите ваш адрес: ";
    cin.ignore();
    getline(cin, clientAddress);

    cout << "Введите тип мебели: ";
    cin >> productType;

    cout << "Введите материал: ";
    cin >> material;

    cout << "Введите цвет: ";
    cin >> color;

    cout << "Введите количество: ";
    quantity = checker.inputNumber(1, 100);

    cout << "Вы уверены, что хотите оформить индивидуальный заказ? (1 - Да, 2 - Нет): ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        setlocale(LC_ALL, "ru_RU.UTF-8");
        string filepath = "/Users/ulanatozik/Материалы по учебе (БГУИР)/2 курс/Курсовая 1 семестр/курсовая код/coursework2/coursework2/list_services3.txt";
        ofstream ordersFile(filepath, ios::app);
        if (ordersFile.is_open()) {
            ordersFile << "Индивидуальный заказ:" << endl;
            ordersFile << "Имя клиента: " << clientName << ", Телефон: " << clientPhone
                       << ", Адрес: " << clientAddress << ", Тип: " << productType
                       << ", Материал: " << material << ", Цвет: " << color
                       << ", Количество: " << quantity << endl;
            ordersFile.close();
            cout << "Ваш индивидуальный заказ оформлен." << endl;
        } else {
            cout << "Ошибка при записи в файл." << endl;
        }
    } else {
        cout << "Вы отменили заказ." << endl;
    }
}

void WorkWithServices::orderServiceRedo() const {
    ProgrammChecks checker;

    cout << "--Заказ на перетяжку мебели--" << endl;

    string clientName, clientPhone, clientAddress, furnitureType, material;
    int quantity;

    cout << "Введите ваше имя: ";
    cin.ignore();
    getline(cin, clientName);

    cout << "Введите ваш номер телефона: ";
    cin >> clientPhone;

    cout << "Введите ваш адрес: ";
    cin.ignore();
    getline(cin, clientAddress);

    cout << "Введите тип мебели для перетяжки: ";
    cin >> furnitureType;

    cout << "Введите материал для перетяжки: ";
    cin >> material;

    cout << "Введите количество: ";
    quantity = checker.inputNumber(1, 100);

    cout << "Вы уверены, что хотите оформить заказ на перетяжку мебели? (1 - Да, 2 - Нет): ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        setlocale(LC_ALL, "ru_RU.UTF-8");
        string filepath = "/Users/ulanatozik/Материалы по учебе (БГУИР)/2 курс/Курсовая 1 семестр/курсовая код/coursework2/coursework2/list_services3.txt";
        ofstream ordersFile(filepath, ios::app);
        if (ordersFile.is_open()) {
            ordersFile << "Заказ на перетяжку:" << endl;
            ordersFile << "Имя клиента: " << clientName << ", Телефон: " << clientPhone
                       << ", Адрес: " << clientAddress << ", Тип мебели: " << furnitureType
                       << ", Материал: " << material << ", Количество: " << quantity << endl;
            ordersFile.close();
            cout << "Ваш заказ на перетяжку оформлен." << endl;
        } else {
            cout << "Ошибка при записи в файл." << endl;
        }
    } else {
        cout << "Вы отменили заказ." << endl;
    }
}

void WorkWithServices::orderServiceFix() const {
    ProgrammChecks checker;

    cout << "--Заказ на ремонт мебели--" << endl;

    string clientName, clientPhone, clientAddress, furnitureType, repairDetails;
    int quantity;

    cout << "Введите имя клиента: ";
    cin.ignore();
    getline(cin, clientName);

    cout << "Введите телефон клиента: ";
    cin >> clientPhone;

    cout << "Введите адрес клиента: ";
    cin.ignore();
    getline(cin, clientAddress);

    cout << "Введите тип мебели для ремонта: ";
    cin >> furnitureType;

    cout << "Опишите детали ремонта: ";
    cin.ignore();
    getline(cin, repairDetails);

    cout << "Введите количество: ";
    quantity = checker.inputNumber(1, 100);

    cout << "Вы уверены, что хотите оформить заказ на ремонт мебели? (1 - Да, 2 - Нет): ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        setlocale(LC_ALL, "ru_RU.UTF-8");
        string filepath = "/Users/ulanatozik/Материалы по учебе (БГУИР)/2 курс/Курсовая 1 семестр/курсовая код/coursework2/coursework2/list_services3.txt";
        ofstream ordersFile(filepath, ios::app);
        if (ordersFile.is_open()) {
            ordersFile << "Заказ на ремонт:" << endl;
            ordersFile << "Имя клиента: " << clientName << ", Телефон: " << clientPhone
                       << ", Адрес: " << clientAddress << ", Тип мебели: " << furnitureType
                       << ", Детали ремонта: " << repairDetails << ", Количество: " << quantity << endl;
            ordersFile.close();
            cout << "Ваш заказ на ремонт оформлен." << endl;
        } else {
            cout << "Ошибка при записи в файл." << endl;
        }
    } else {
        cout << "Вы отменили заказ." << endl;
    }
}


void WorkWithServices::editExistingServices() const {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    string filepath="/Users/ulanatozik/Материалы по учебе (БГУИР)/2 курс/Курсовая 1 семестр/курсовая код/coursework2/coursework2/list_services3.txt";
    ifstream ordersFile(filepath);
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
    
    setlocale(LC_ALL, "ru_RU.UTF-8");
 
    // Перезапись файла с изменениями
    ofstream ordersFileOut(filepath);
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
