//
//  MenuTable.cpp
//  coursework2
//
//  Created by Ульяна Тозик on 15.11.24.
//

#include "MenuTable.h"
#include "WorkServices.h"
#include "Furniture.h"
#include "AccountsWork.h"

using namespace std;

void Menu::startMenu() const { // начальное меню
    int choice;
    auto sObj = std::make_unique<EnterSystem>(); // Используем уникальный указатель
    ProgrammChecks checker;
    
    do {
        cout << "-------Введите--------\n 1. Для регистрации \n 2. Для авторизации\n 3. Для выхода \n";
        cout << "Ваш выбор?" << endl;
        choice = checker.inputNumber(1, 3);
        
        switch(choice) {
        case 1:
            sObj->registration(); // Вызов метода через указатель
            sleep(3);
            break;
        case 2:
            sObj->authorization(); // Вызов метода через указатель
            break;
        case 3:
            cout << "Совершен выход из программы.";
            break;
        }
    } while(choice != 3);
}

void Menu::menuWorkWithUser() const { // передаем текущего пользователя
    int choice;
    Tables tableObj;
    WorkWithAccounts accountObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;
    
    do {
        cout << "--------------Введите--------------" << endl;
        
        auto usersPtr = filesObj.readUsersFromFile(); // Получаем вектор указателей
        std::vector<std::shared_ptr<User>> users = usersPtr; // Создаем копию для удобства работы
        
        cout << "1 - для вывода учетных записей" << endl;
        cout << "2 - для добавления учетных записей" << endl;
        cout << "3 - для редактирования учетных записей" << endl;
        cout << "4 - для удаления учетных записей" << endl;
        cout << "5 - для одобрения заявок на регистрацию" << endl;
        cout << "6 - для выхода" << endl;
        cout << "Ваш выбор:  ";
        choice = checker.inputNumber(1, 6);
        
        switch(choice) {
        case 1:
            tableObj.printUsersTable(users); // Передаем вектор указателей
            break;
        case 2:
            accountObj.addAccount();
            break;
        case 3:
            accountObj.editAccount();
            break;
        case 4:
            // Передаем текущего пользователя в метод удаления
            accountObj.deleteAccount();
            break;
        case 5:
            accountObj.approve();
            break;
        case 6:
            break;
        default:
            cout << "Введено некорректное значение. Попробуйте снова." << endl;
        }
    } while(choice != 6);
}


void Menu::menuWorkWithFurnitureStart() const {
    // Создаем объект WorkWithProducts один раз, а не на каждом вызове.
   
    WorkWithProducts prObj;
    ProgrammChecks checker;

    // Путь к файлу, в который будет сохраняться отчет
    std::string pathToFile = "/Users/ulanatozik/Материалы по учебе (БГУИР)/2 курс/Кодик/mycoursework2/mycoursework2/sales_report.txt";

    while (true) {
        std::cout << "--------------Введите--------------" << std::endl;
        int choice;

        std::cout << "1 - для работы с товарами" << std::endl;
        std::cout << "2 - для работы с услугами" << std::endl;
        std::cout << "3 - для вывода данных о продажах (прибыль, выручка, количество проданных товаров)" << std::endl;
        std::cout << "4 - для выхода" << std::endl;
        std::cout << "Ваш выбор:  ";
        choice = checker.inputNumber(1, 4);
        
        switch (choice) {
            case 1: {
                // Работа с товарами: сюда добавим код для работы с товарами
                menuWorkWithFurniture();  // Передаем prObj для работы с товарами
                break;
            }
            case 2: {
                menuWorkWithServices();  // Переход к меню работы с услугами
                break;
            }
            case 3: {
                // Вызов функции генерации отчета
                prObj.printTotalRevenue();
                prObj.generateReport(); // Генерация отчета о продажах
                break;
            }
            case 4: {
                return;  // Выход из меню
            }
        }
    }
}

void Menu::menuWorkWithFurniture() const { // меню для работы с товарами
    Tables tableObj;
    WorkWithProducts prObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;


    while (true) {
        std::cout << "--------------Введите--------------" << std::endl;
        int choice;
        auto furnitureProducts = filesObj.readFurnitureFromFile(); // std::shared_ptr<Furniture>

        std::cout << "1 - для отображения перечня мебельных товаров" << std::endl;
        std::cout << "2 - для добавления товара" << std::endl;
        std::cout << "3 - для редактирования товара" << std::endl;
        std::cout << "4 - для удаления товара" << std::endl;
        std::cout << "5 - для поиска товара" << std::endl;
        std::cout << "6 - для сортировки товаров" << std::endl;
        std::cout << "7 - для выхода" << std::endl;
        std::cout << "Ваш выбор:  ";
        choice = checker.inputNumber(1, 7);

        switch (choice) {
            case 1: {
                tableObj.printFurnitureTable(furnitureProducts);
                break;
            }
            case 2: {
                prObj.addFurniture();
                break;
            }
            case 3: {
                prObj.editFurniture();
                break;
            }
            case 4: {
                prObj.deleteFurniture();
                break;
            }
            case 5: {
                menuSearch();
                break;
            }
            case 6: {
                menuSort();
                break;
            }
            case 7: {
                return;
            }
        }
    }
}

void Menu::menuWorkWithServices() const
{
    WorkWithServices serObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;
    
    while (true) {
        std::cout << "--------------Введите--------------" << std::endl;
        int choice;
        auto furnitureProducts = filesObj.readFurnitureFromFile(); // std::shared_ptr<Furniture>
        
        std::cout << "1 - для отображения перечня заказанных услуг" << std::endl;
        std::cout << "2 - для редактирования данных о заказанных услугах" << std::endl;
        std::cout << "3 - для выхода" << std::endl;
        std::cout << "Ваш выбор:  ";
        choice = checker.inputNumber(1, 3);
        
        switch (choice) {
            case 1: {
                serObj.displayServices();
                break;
            }
            case 2: {
                serObj.editExistingServices();
                break;
            }
            case 3: {
                return;
            }
        }
    }
}




void Menu::menuUser() const { // меню пользователя
    Tables tableObj;
    WorkWithProducts prObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;
    
    int choice;
    std::cout << "\n----УВЕДОМЛЕНИЯ ДЛЯ ПОЛЬЗОВАТЕЛЯ----" << std::endl;
    prObj.salesNotification();
    
    do {
        auto furnitureProducts = filesObj.readFurnitureFromFile();
        
        std::cout << "\n--------------МЕНЮ ПОЛЬЗОВАТЕЛЯ--------------" << std::endl;
        std::cout << "Введите:" << std::endl;
        std::cout << "1 - для просмотра данных" << std::endl;
        std::cout << "2 - для поиска данных" << std::endl;
        std::cout << "3 - для сортировки данных" << std::endl;
        std::cout << "4 - для оформления заказа или предзаказа товара" << std::endl;
        std::cout << "5 - для оформления заказа услуги" << std::endl;
        std::cout << "6 - для выхода" << std::endl;
        std::cout << "Ваш выбор:  ";
        choice = checker.inputNumber(1, 6);
        
        switch (choice) {
            case 1: {
                tableObj.printFurnitureTable(furnitureProducts);
                break;
            }
            case 2: {
                menuSearch();
                break;
            }
            case 3: {
                menuSort();
                break;
            }
            case 4: {
                // Вызов метода orderProduct и получение цены проданного товара
                prObj.orderProduct();
              
                break;
            }
            case 5: {
                menuService();
                break;
            }
            case 6: {
                break; // Завершение меню
            }
        }
    } while (choice != 6);
}

void Menu::menuService() const {
    WorkWithFiles filesObj;
    ProgrammChecks checker;
    WorkWithServices serObj;
    cout << "--------------Введите--------------" << endl;
    int choice;
    auto furnitureProducts = filesObj.readFurnitureFromFile();
    cout << "1 - для заказа индивидуальной мебели" << endl;
    cout << "2 - для заказа услуги по перетяжке мебели" << endl;
    cout << "3 - для заказа услуги починки мебели" << endl;
    cout << "4 - для выхода" << endl;
    cout << "Ваш выбор:  ";
    choice = checker.inputNumber(1, 6);
    switch (choice) {
        case 1:
            serObj.orderServiceIndividual(); // Поиск по цене
            break;
        case 2:
            serObj.orderServiceRedo(); // Поиск по количеству
            break;
        case 3:
            serObj.orderServiceFix(); // Поиск по виду изделия
            break;
        case 4:
            break;
    }
}

void Menu::menuSearch() const { // Поиск товаров
    SearchProducts searchObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;
    cout << "--------------Введите--------------" << endl;
    int choice;
    auto furnitureProducts = filesObj.readFurnitureFromFile();
    cout << "1 - для поиска по цене" << endl;
    cout << "2 - для поиска по количеству" << endl;
    cout << "3 - для поиска по виду изделия" << endl;
    cout << "4 - для поиска по цвету" << endl;
    cout << "5 - для поиска по виду материала" << endl;
    cout << "6 - для поиска по названию бренда" << endl;
    cout << "Ваш выбор:  ";
    choice = checker.inputNumber(1, 6);
    switch (choice) {
        case 1:
            searchObj.searchPrice(); // Поиск по цене
            break;
        case 2:
            searchObj.searchAmount(); // Поиск по количеству
            break;
        case 3:
            searchObj.searchProductType(); // Поиск по виду изделия
            break;
        case 4:
            searchObj.searchColor(); // Поиск по цвету
            break;
        case 5:
            searchObj.searchMaterial(); // Поиск по виду материала
            break;
        case 6:
            searchObj.searchBrand(); // Поиск по бренду
            break;
    }
}

void Menu::menuSort() const { // Меню сортировки
    Tables tableObj;
    SortProducts sortObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;
    
    auto furnitureProducts = filesObj.readFurnitureFromFile(); // Получаем vector<Furniture>
    vector<Furniture> furniture_temp = furnitureProducts; // Копируем вектор
    int choice;
    
    cout << "---—Введите---" << endl;
    cout << "1 - для сортировки по цене " << endl;
    cout << "2 - для сортировки по количеству товара в наличии " << endl;
    cout << "3 - для сортировки по виду материала" << endl;
    cout << "4 - для сортировки по цвету" << endl;
    cout << "Ваш выбор:" << endl;
    
    choice = checker.inputNumber(1, 4);
    
    switch (choice) {
        case 1:
            sort(furniture_temp.begin(), furniture_temp.end(),
                 bind(&SortProducts::isSortByPrice, &sortObj, placeholders::_1, placeholders::_2));
            break;
        case 2:
            sort(furniture_temp.begin(), furniture_temp.end(),
                 bind(&SortProducts::isSortByAmount, &sortObj, placeholders::_1, placeholders::_2));
            break;
        case 3:
            sort(furniture_temp.begin(), furniture_temp.end(),
                 bind(&SortProducts::isSortByMaterial, &sortObj, placeholders::_1, placeholders::_2));
            break;
        case 4:
            sort(furniture_temp.begin(), furniture_temp.end(),
                 bind(&SortProducts::isSortByColor, &sortObj, placeholders::_1, placeholders::_2));
            break;
    }
    
    cout << "--Успешно отсортировано--" << endl;
    tableObj.printFurnitureTable(furniture_temp); // Передаем vector<Furniture>
}

void Menu::menuAdministrator() const { // передаем текущего пользователя
    ProgrammChecks checker;
    int choice;

    WorkWithProducts obj1;
    WorkWithFiles fileObj;
    auto furnitureProducts = fileObj.readFurnitureFromFile(); // Используем auto
    cout << "\n";
    cout << "----УВЕДОМЛЕНИЯ ДЛЯ АДМИНИСТРАТОРА----" << endl;
    obj1.productNotification();
    cout << "\n";

    do {
        cout << "\n";
        cout << "--------------МЕНЮ АДМИНИСТРАТОРА--------------" << endl;
        cout << "Введите:" << endl;
        cout << "1 - для работы с учетными записями" << endl;
        cout << "2 - для работы с данными" << endl;
        cout << "3 - для выхода" << endl;
        cout << "Ваш выбор:  ";
        choice = checker.inputNumber(1, 3);
        
        switch(choice) {
        case 1:
            // Передаем текущего пользователя в menuWorkWithUser
            menuWorkWithUser();
            break;
        case 2:
            menuWorkWithFurnitureStart(); // Аналогично
            break;
        case 3:
            break;
        }
    } while(choice != 3);
}


void Tables::printAccountsTable(const vector<shared_ptr<User>>& accounts) const { // Вывод таблицы аккаунтов
    EnterSystem sObj;
    cout << "\n|=============================================================================================|"
         << "\n|                                 ЗАЯВКИ НА РЕГИСТРАЦИЮ                                       |"
         << "\n|=============================================================================================|"
         << "\n|    №    |            Логин             |            Пароль            |         Админ       |"
         << "\n|=============================================================================================|\n";
    int i = 0;
    // Вывод строк таблицы
    for (const auto& account : accounts) {
        cout << "|" << setw(9) << ++i << "|" << setw(16) << account->getLogin() << setw(16) << " | "
             << setw(16) << sObj.encrypt(account->getPassword()) << setw(15) << " | "
             << setw(13) << (account->getIsAdmin() ? "Да" : "Нет") << setw(10) << "|" << endl;
        cout << "|=============================================================================================|" << endl;
    }
}

void Tables::printUsersTable(const vector<shared_ptr<User>>& users) const { // Вывод таблицы пользователей
    EnterSystem sObj;
    cout << "\n|=============================================================================================|"
         << "\n|                                 АККАУНТЫ ПОЛЬЗОВАТЕЛЕЙ                                      |"
         << "\n|=============================================================================================|"
         << "\n|    №    |            Логин             |            Пароль            |        Админ        |"
         << "\n|=============================================================================================|\n";
    int i = 0;
    // Вывод строк таблицы
    for (const auto& user : users) {
        cout << "|" << setw(9) << ++i << "|" << setw(18) << user->getLogin() << setw(14) << " | "
             << setw(16) << sObj.encrypt(user->getPassword()) << setw(15) << " | "
             << setw(13) << (user->getIsAdmin() ? "Да" : "Нет") << setw(10) << "|" << endl;
        cout << "|=============================================================================================|" << endl;
    }
}


void Tables::printFurnitureTable(const vector<Furniture>& furnitureProducts) const { // Вывод таблицы товаров
    headTable();
    int i = 0;

    for (const auto& furniture : furnitureProducts) {
        cout << "| "
             << setw(3) << ++i << " | "
             << setw(20) << furniture.getProductType() << setw(8) << " | "
             << setw(13) << furniture.getMaterial() << setw(15) << " | "
             << setw(10) << furniture.getColor() << setw(5) << " | "
             << setw(6) << furniture.getPrice() << setw(8) << " | "
             << setw(8) << furniture.getAmount() << setw(10) << " | "
             << setw(10) << furniture.getBrand() << setw(3) << " |"
             << endl
             << "|=======================================================================================================================|" << endl;
    }
}

void Tables::headTable() const { // Шапка таблицы товаров
    cout << "\n|=======================================================================================================================|"
         << "\n|                                        МЕБЕЛЬНЫЕ ТОВАРЫ                                                              |"
         << "\n|=======================================================================================================================|"
         << "\n|  №  |      Вид изделия     |     Материал     |   Цвет    |    Цена     |   Количество    |    Бренд    |"
         << "\n|=======================================================================================================================|\n";
}

void SearchProducts::searchProductType() const { // Поиск по виду изделия
    Tables tableObj;
    ProgrammChecks checker;
    WorkWithFiles filesObj;
    auto furnitureProducts = filesObj.readFurnitureFromFile();
    string productType;
    
    cout << "--Поиск по виду товара--" << endl;
    cout << "Введите вид товара: ";
    productType = checker.checkString();

    tableObj.headTable();

    // Используем std::copy_if для поиска
    auto foundItems = std::count_if(furnitureProducts.begin(), furnitureProducts.end(),
        [&productType](const Furniture& furniture) {
            return furniture.getProductType().find(productType) != string::npos;
        });

    if (foundItems > 0) {
        int a = 0;
        for (const auto& furniture : furnitureProducts) {
            if (furniture.getProductType().find(productType) != string::npos) { // Ищем по виду товара
                cout << "| "
                     << setw(3) << ++a << " | "
                     << setw(20) << furniture.getProductType() << setw(8) << " | "
                     << setw(17) << furniture.getMaterial() << setw(7) << " | "
                     << setw(17) << furniture.getColor() << setw(7) << " | "
                     << setw(6) << furniture.getPrice() << setw(8) << " | "
                     << setw(8) << furniture.getAmount() << setw(10) << " | "
                     << setw(10) << furniture.getBrand() << setw(3) << " |"
                     << endl
                     << "|=======================================================================================================================|" << endl;
            }
        }
    } else {
        cout << "Ничего не найдено" << endl;
    }
}


void SearchProducts::searchMaterial() const { // Поиск по материалу
    WorkWithFiles filesObj;
    auto furnitureProducts = filesObj.readFurnitureFromFile();
    Tables tableObj;
    ProgrammChecks checker;
    string material;

    cout << "--Поиск по материалу--" << endl;
    cout << "Введите материал: ";
    material = checker.checkString();

    tableObj.headTable();

    // Используем std::count_if для поиска
    auto foundItems = std::count_if(furnitureProducts.begin(), furnitureProducts.end(),
        [&material](const Furniture& furniture) {
            return furniture.getMaterial().find(material) != string::npos;
        });

    if (foundItems > 0) {
        int a = 0;
        for (const auto& furniture : furnitureProducts) {
            if (furniture.getMaterial().find(material) != string::npos) { // Ищем по материалу
                cout << "| "
                     << setw(3) << ++a << " | "
                     << setw(20) << furniture.getProductType() << setw(8) << " | "
                     << setw(17) << furniture.getMaterial() << setw(7) << " | "
                     << setw(17) << furniture.getColor() << setw(7) << " | "
                     << setw(6) << furniture.getPrice() << setw(8) << " | "
                     << setw(8) << furniture.getAmount() << setw(10) << " | "
                     << setw(10) << furniture.getBrand() << setw(3) << " |"
                     << endl
                     << "|=======================================================================================================================|" << endl;
            }
        }
    } else {
        cout << "Ничего не найдено" << endl;
    }
}


void SearchProducts::searchPrice() const { // Поиск по цене
    WorkWithFiles filesObj;
    auto furnitureProducts = filesObj.readFurnitureFromFile();
    Tables tableObj;
    ProgrammChecks checker;
    int price;

    cout << "--Поиск по цене--" << endl;
    cout << "Введите цену: ";
    price = checker.inputNumber(0, 10000);

    tableObj.headTable();

    // Используем std::count_if для поиска
    auto foundItems = std::count_if(furnitureProducts.begin(), furnitureProducts.end(),
        [price](const Furniture& furniture) {
            return furniture.getPrice() == price;
        });

    if (foundItems > 0) {
        int a = 0;
        for (const auto& furniture : furnitureProducts) {
            if (furniture.getPrice() == price) {
                cout << "| "
                     << setw(3) << ++a << " | "
                     << setw(20) << furniture.getProductType() << setw(8) << " | "
                     << setw(17) << furniture.getMaterial() << setw(7) << " | "
                     << setw(13) << furniture.getColor() << setw(15) << " | "
                     << setw(6) << furniture.getPrice() << setw(8) << " | "
                     << setw(8) << furniture.getAmount() << setw(10) << " | "
                     << setw(10) << furniture.getBrand() << setw(3) << " |"
                     << endl
                     << "|=======================================================================================================================|" << endl;
            }
        }
    } else {
        cout << "Ничего не найдено" << endl;
    }
}


void SearchProducts::searchAmount() const { // Поиск по количеству
    WorkWithFiles filesObj;
    auto furnitureProducts = filesObj.readFurnitureFromFile();
    ProgrammChecks checker;
    int amount;
    Tables tableObj;

    cout << "--Поиск по количеству товара в наличии--" << endl;
    cout << "Введите количество товара в наличии: ";
    amount = checker.inputNumber(0, 100);

    tableObj.headTable();

    // Используем std::count_if для поиска
    auto foundItems = std::count_if(furnitureProducts.begin(), furnitureProducts.end(),
        [amount](const Furniture& furniture) {
            return furniture.getAmount() == amount;
        });

    if (foundItems > 0) {
        int a = 0;
        for (const auto& furniture : furnitureProducts) {
            if (furniture.getAmount() == amount) {
                cout << "| "
                     << setw(3) << ++a << " | "
                     << setw(20) << furniture.getProductType() << setw(8) << " | "
                     << setw(17) << furniture.getMaterial() << setw(7) << " | "
                     << setw(13) << furniture.getColor() << setw(15) << " | "
                     << setw(6) << furniture.getPrice() << setw(8) << " | "
                     << setw(8) << furniture.getAmount() << setw(10) << " | "
                     << setw(10) << furniture.getBrand() << setw(3) << " |"
                     << endl
                     << "|=======================================================================================================================|" << endl;
            }
        }
    } else {
        cout << "Ничего не найдено" << endl;
    }
}



void SearchProducts::searchColor() const { // Поиск по цвету
    WorkWithFiles filesObj;
    auto furnitureProducts = filesObj.readFurnitureFromFile();
    string color;
    Tables tableObj;
    ProgrammChecks checker;
    int count = 0;
    int a = 0;

    cout << "--Поиск по цвету--" << endl;
    cout << "Введите цвет: ";
    color = checker.checkString(); // Убрали аргумент

    tableObj.headTable();
    for (const auto& furniture : furnitureProducts) {
        if (furniture.getColor().find(color) != string::npos) { // Ищем по цвету
            count++;
            cout << "| "
                 << setw(3) << ++a << " | "
            << setw(20) << furniture.getProductType() << setw(8) << " | "
            << setw(17) << furniture.getMaterial() << setw(7) << " | "
            << setw(17) << furniture.getColor() << setw(7) << " | "
            << setw(6) << furniture.getPrice() << setw(8) << " | "
            << setw(8) << furniture.getAmount() << setw(10) << " | "
            << setw(10) << furniture.getBrand() << setw(3) << " |"
                 << endl
                 << "|=======================================================================================================================|" << endl;
        }
    }

    if (count == 0) {
        cout << "Ничего не найдено" << endl;
    }
}

void SearchProducts::searchBrand() const { // Поиск по бренду
    WorkWithFiles filesObj;
    auto furnitureProducts = filesObj.readFurnitureFromFile();
    string brand;
    Tables tableObj;
    ProgrammChecks checker;
    int count = 0;
    int a = 0;

    cout << "--Поиск по названию бренда--" << endl;
    cout << "Введите название бренда: ";
    brand = checker.checkString(); // Убрали аргумент

    tableObj.headTable();
    for (const auto& furniture : furnitureProducts) {
        if (furniture.getBrand().find(brand) == 0) { // Поиск по началу названия бренда
            count++;
            cout << "| "
                 << setw(3) << ++a << " | "
            << setw(20) << furniture.getProductType() << setw(8) << " | "
            << setw(17) << furniture.getMaterial() << setw(7) << " | "
            << setw(13) << furniture.getColor() << setw(15) << " | "
            << setw(6) << furniture.getPrice() << setw(8) << " | "
            << setw(8) << furniture.getAmount() << setw(10) << " | "
            << setw(10) << furniture.getBrand() << setw(3) << " |"
                 << endl
                 << "|=======================================================================================================================|" << endl;
        }
    }

    if (count == 0) {
        cout << "Ничего не найдено" << endl;
    }
}

bool SortProducts::isSortByPrice(const Furniture& price_a, const Furniture& price_b) const { // Сортировка по цене
    return price_a.getPrice() < price_b.getPrice();
}

bool SortProducts::isSortByAmount(const Furniture& amount_a, const Furniture& amount_b) const { // Сортировка по количеству в наличии
    return amount_a.getAmount() < amount_b.getAmount();
}

bool SortProducts::isSortByMaterial(const Furniture& material_a, const Furniture& material_b) const { // Сортировка по пробе металла
    return material_a.getMaterial() < material_b.getMaterial();
}

bool SortProducts::isSortByColor(const Furniture& color_a, const Furniture& color_b) const { // Сортировка по виду металла
    return color_a.getColor() < color_b.getColor();
}
