//
//  AccountsWork.cpp
//  coursework2
//
//  Created by Ульяна Тозик on 15.11.24.
//

 
#include "Furniture.h"
#include "MenuTable.h"
#include "WorkServices.h"
#include "AccountsWork.h"
 


bool EnterSystem::checkLoginAndPassword(const std::vector<std::shared_ptr<User>>& users, const std::string& login, const std::string& password) const { // Проверка логина и пароля
    Menu menuObj;
    WorkWithFiles fileObj;

    // Проверяем существующих пользователей
    for (const auto& user : users) {
        if (user->getLogin() == login && user->getPassword() == password) {
            std::cout << "Добро пожаловать, " << user->getLogin() << "!" << std::endl;

            // Переход в соответствующее меню в зависимости от роли
            if (user->getIsAdmin() == 0) {
                menuObj.menuUser(); // Для пользователей
            } else if (user->getIsAdmin() == 1) {
                menuObj.menuAdministrator(); // Для администраторов
            }
            return true;
        }
    }

    // Проверяем заявки на регистрацию
    auto accounts = fileObj.readAccountsFromFile();
    for (const auto& account : accounts) {
        if (account->getLogin() == login && account->getPassword() == password) {
            std::cout << "Добро пожаловать, " << account->getLogin() << "! К сожалению, ваша заявка на регистрацию еще не подтверждена, поэтому вы не можете зайти в систему." << std::endl;

            // Предоставляем доступ к меню независимо от статуса заявки
            // Здесь вы можете добавить логику для пользователя с неподтвержденной заявкой
          /*  menuObj.menuAdministrator(); // Для неподтвержденных заявок также переходим в меню пользователя*/
            return true;
        }
    }

    std::cout << "Неверный логин или пароль. Попробуйте снова" << std::endl;
    return false;
}





bool EnterSystem::checkLoginAndPasswordRegist(const std::vector<std::shared_ptr<User>>& users, const std::string& login, const std::string& password, bool isAdmin) const { // Проверка на существование пользователя
    for (const auto& user : users) {
        if (user->getLogin() == login && user->getPassword() == password && user->getIsAdmin() == isAdmin) {
            std::cout << "Такой пользователь уже существует" << std::endl;
            return false;
        }
        if (user->getLogin() == login) {
            std::cout << "Пользователь с таким логином уже существует" << std::endl;
            return false;
        }
    }
    return true;
}




void EnterSystem::authorization() const { // Авторизация
    WorkWithFiles filesObj;
    std::cout << "Авторизация:" << std::endl;
    std::string login, password;
    
    bool isLoggedIn = false;

    while (!isLoggedIn) {
        std::cout << "Введите логин:  ";
        std::cin >> login;

        std::cout << "Введите пароль: ";
        std::cin >> password;

        auto users = filesObj.readUsersFromFile();
        if (checkLoginAndPassword(users, login, password)) {
            isLoggedIn = true;
        }
    }
}

void EnterSystem::registration() const { // Регистрация
    ProgrammChecks checker;
    WorkWithFiles filesObj;
    std::cout << "Регистрация:" << std::endl;
    std::string login, password;
    bool isAdmin;
    auto accounts = filesObj.readAccountsFromFile();
    auto users = filesObj.readUsersFromFile();
    
    while (true) {
        std::cout << "Введите логин: " << std::endl;
        login = checker.checkSize(login);
        std::cout << "Введите пароль: " << std::endl;
        password = checker.checkSize(password);
        std::cout << "Является ли админом (1/0): " << std::endl;
        isAdmin = checker.inputNumber(0, 1);
        
        if (checkLoginAndPasswordRegist(accounts, login, password, isAdmin) &&
            checkLoginAndPasswordRegist(users, login, password, isAdmin)) {
            break;
        }
    }

    // Создаем shared_ptr для нового аккаунта
    auto account = std::make_shared<User>();
    account->setLogin(login);
    account->setPassword(password);
    account->setIsAdmin(isAdmin);

    accounts.push_back(account); // Добавляем вектору shared_ptr
    filesObj.writeAccountsToFile(accounts);
    std::cout << "Ваша заявка на регистрацию отправлена, ожидайте ответ администратора." << std::endl;
}


std::string EnterSystem::encrypt(const std::string& input) const { // Шифровка
    std::string output(input.size(), ' ');
    for (size_t i = 0; i < input.size(); i++) {
        output[i] = (char)((int)input[i] + 3) % 256;
    }
    return output;
}

std::string EnterSystem::decrypt(const std::string& input) const { // Дешифровка
    std::string output(input.size(), ' ');
    for (size_t i = 0; i < input.size(); i++) {
        output[i] = (char)((int)input[i] - 3) % 256;
    }
    return output;
}


void WorkWithAccounts::approve() const { // Одобрение заявки
    Tables tablesObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;

    auto accounts = filesObj.readAccountsFromFile();
    auto users = filesObj.readUsersFromFile();

    tablesObj.printAccountsTable(accounts);

    int number_for_add, choice;
    cout << "---Выберите---" << endl;
    cout << "1 - Для одобрения заявки" << endl;
    cout << "2 - Для выхода" << endl;

    choice = checker.inputNumber(1, 2);

    switch(choice) {
        case 1: {
            cout << "Выберите номер заявки, которую хотите одобрить" << endl;
            number_for_add = checker.inputNumber(1, accounts.size());

         
            auto user = accounts.at(number_for_add - 1);
     
            users.push_back(user);
            filesObj.writeUsersToFile(users);

            cout << "Вы одобрили заявку" << endl;
            accounts.erase(accounts.begin() + number_for_add - 1);
            filesObj.writeAccountsToFile(accounts);
            break;
        }
        case 2:
            return;
    }
}



void WorkWithAccounts::addAccount() const { // Добавить аккаунт
    WorkWithFiles filesObj;
    EnterSystem sObj;
    ProgrammChecks checker;

    cout << "Добавить аккаунт" << endl;
    string login, password;
    bool isAdmin;
    
    auto users = filesObj.readUsersFromFile(); // Предполагается, что это std::vector<std::shared_ptr<User>>

    while(true) {
        cout << "Введите логин: ";
        cin >> login;
        cout << "Введите пароль: ";
        cin >> password;
        cout << "Является ли админом (1/0): ";
        isAdmin = checker.inputNumber(0, 1);
        
        if(sObj.checkLoginAndPasswordRegist(users, login, password, isAdmin)) {
            break;
        }
    }

    auto user = std::make_shared<User>(); // Создаем указатель на нового пользователя
    user->setLogin(login);
    user->setPassword(password);
    user->setIsAdmin(isAdmin);

    users.push_back(user); // Добавляем указатель на пользователя
    filesObj.writeUsersToFile(users);
}



void WorkWithAccounts::deleteAccount() const { // удалить аккаунт
    Tables tableObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;
    
    auto usersPtr = filesObj.readUsersFromFile(); // Получаем вектор указателей
    std::vector<std::shared_ptr<User>> users = usersPtr; // Создаем копию для удобства работы
    tableObj.printUsersTable(users);
    
    int number_for_delete;
    cout << "----Удаление учетной записи----" << endl << endl;
    cout << "Введите номер аккаунта, который хотите удалить" << endl;
    number_for_delete = checker.inputNumber(1, users.size());
    
    cout << "Вы уверены, что хотите удалить аккаунт?" << endl;
    int yes_or_no;
    cout << "1. Да" << endl
         << "2. Нет" << endl
         << "Ваш выбор:" << endl;
    yes_or_no = checker.inputNumber(1, 2);
    
     if(yes_or_no == 1) {
        /*if(users.at(number_for_delete - 1)->getIsAdmin() == 1) { // Используем -> для доступа к методу
            cout << "Удалить свой аккаунт невозможно" << endl;
        } else {*/
            users.erase(users.begin() + number_for_delete - 1);
            cout << "----Аккаунт успешно удален----" << endl;
            filesObj.writeUsersToFile(users); // Предполагается, что writeUsersToFile принимает std::vector<std::shared_ptr<User>>
        
    } else {
        cout << "Вы отменили удаление" << endl;
    }
}



void WorkWithAccounts::editAccount() const {
    int choice;
    Tables tableObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;

    do {
        // Чтение пользователей из файла
        vector<shared_ptr<User>> users = filesObj.readUsersFromFile();
        // Преобразуем для вывода
        tableObj.printUsersTable(users);
        
        int number_for_edit;
        cout << "Введите номер аккаунта, который хотите изменить: " << endl;
        number_for_edit = checker.inputNumber(1, users.size());

        cout << "--------------Введите--------------" << endl;
        cout << "1 - Чтобы изменить логин" << endl;
        cout << "2 - Чтобы изменить роль пользователя" << endl;
        cout << "3 - Чтобы редактировать все данные аккаунта" << endl;
        cout << "4 - Чтобы выйти из режима редактирования" << endl;
        cout << "Ваш выбор: ";
        choice = checker.inputNumber(1, 4);
        
        switch(choice) {
        case 1: {
            cout << "--Новый логин--" << endl;
            string newLogin;
            cin >> newLogin;

            bool isLoginTaken = false;
            for(const auto& user : users) {
                if(user->getLogin() == newLogin) {
                    isLoginTaken = true;
                    break;
                }
            }

            if(!isLoginTaken) {
                users.at(number_for_edit - 1)->setLogin(newLogin);
                filesObj.writeUsersToFile(users);
                cout << "--Логин успешно заменен--" << endl;
            } else {
                cout << "Данный логин занят, повторите попытку" << endl;
            }
            break;
        }
        case 2: {
            cout << "--Новая роль пользователя--" << endl;
            cout << "1 - роль администратора" << endl;
            cout << "0 - роль пользователя" << endl;
            users.at(number_for_edit - 1)->setIsAdmin(checker.inputNumber(0, 1));
            filesObj.writeUsersToFile(users);
            cout << "---Успешно отредактировано---" << endl;
            break;
        }
        case 3: {
            cout << "--Новый логин--" << endl;
            string newLogin;
            cin >> newLogin;

            while(true) {
                bool isLoginTaken = false;
                for(const auto& user : users) {
                    if(user->getLogin() == newLogin) {
                        isLoginTaken = true;
                        break;
                    }
                }
                if(!isLoginTaken) {
                    break;
                }
                cout << "Данный логин занят, повторите попытку" << endl;
                cin >> newLogin;
            }

            // Создаем новый объект User с обновленным логином
            User updatedUser = *users.at(number_for_edit - 1);  // Копируем данные старого пользователя
            updatedUser.setLogin(newLogin);  // Устанавливаем новый логин

            cout << "--Новая роль пользователя--" << endl;
            cout << "1 - роль администратора" << endl;
            cout << "0 - роль пользователя" << endl;
            updatedUser.setIsAdmin(checker.inputNumber(0, 1));  // Устанавливаем новую роль

            // Используем перегрузку оператора = для замены старого объекта
            *users.at(number_for_edit - 1) = updatedUser;

            filesObj.writeUsersToFile(users);
            cout << "---Успешно отредактировано---" << endl;
            break;
        }
        case 4: {
            break;
        }
        }

    } while(choice != 4);
}
 


string global_login;


 

string ProgrammChecks::checkSize(const string& input) { // Принятый параметр как const reference
    const int SIZE = 8;
    string s;

    do {
        cout << "Введите строку (максимум " << SIZE << " символов): ";
        getline(cin, s);
        if (s.size() > SIZE) {
            cout << "Введенная строка превышает заданный размер. Пожалуйста, повторите ввод." << endl;
        }
    } while (s.size() > SIZE);

    return s;
}

string ProgrammChecks::checkString() {
    string s;
    while (true) {
        getline(cin, s);

        bool hasDigit = false;
        for (char ch : s) {
            if (isdigit(ch)) {
                hasDigit = true;
                break;
            }
        }
        if (!hasDigit) {
            return s;
        }
        cout << "Некорректный ввод. Повторите попытку." << endl;
    }
}

bool ProgrammChecks::isNumberNumeric() {
    return cin.good();
}

bool ProgrammChecks::isNumberRangeCorrect(int number, int left_range, int right_range) {
    return (number >= left_range && number <= right_range);
}

int ProgrammChecks::inputNumber(int left_range, int right_range) {
    int number;
    while (true) {
       /* cout << "Введите число (" << left_range << " - " << right_range << "): ";*/
        cin >> number;
        if (isNumberNumeric() && isNumberRangeCorrect(number, left_range, right_range)) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера ввода
            return number;
        } else {
            cout << "Некорректный ввод. Повторите попытку." << endl;
            cin.clear(); // Сброс флагов ошибок
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера ввода
        }
    }
}

void WorkWithFiles::writeUsersToFile(const vector<shared_ptr<User>>& users) const {
    string filename = "/Users/ulanatozik/Материалы по учебе (БГУИР)/2 курс/Кодик/mycoursework2/mycoursework2/users.txt";
    ofstream outputFile(filename);
    EnterSystem sObj;

    if (!outputFile.is_open()) {
        cerr << "Ошибка открытия файла " << filename << " для записи" << endl;
        return;
    }

    for (const auto& user : users) {
        outputFile << user->getLogin() << " "
                   << sObj.encrypt(user->getPassword()) << " "
                   << user->getIsAdmin() << endl;
    }

    outputFile.close();
}

vector<shared_ptr<User>> WorkWithFiles::readUsersFromFile() const {
    string fileName = "/Users/ulanatozik/Материалы по учебе (БГУИР)/2 курс/Кодик/mycoursework2/mycoursework2/users.txt";
    vector<shared_ptr<User>> users;
    EnterSystem sObj;
    ifstream inFile(fileName);
    
    if (inFile.is_open()) {
        string login, password, isAdminStr;
        while (inFile >> login >> password >> isAdminStr) {
            bool isAdmin = (isAdminStr == "1");
            shared_ptr<User> newUser;

            // Создаем пользователя в зависимости от его роли
            if (isAdmin) {
                newUser = make_shared<AdminUser>(login, sObj.decrypt(password));
            } else {
                newUser = make_shared<RegularUser>(login, sObj.decrypt(password));
            }

            users.push_back(newUser);
        }
        inFile.close();
    } else {
        cerr << "Невозможно открыть файл " << fileName << endl;
    }
    return users;
}


void WorkWithFiles::writeAccountsToFile(const vector<shared_ptr<User>>& accounts) const {
    string filename = "/Users/ulanatozik/Материалы по учебе (БГУИР)/2 курс/Кодик/mycoursework2/mycoursework2/accounts.txt";
    ofstream outputFile(filename);
    EnterSystem sObj;

    if (!outputFile.is_open()) {
        cerr << "Ошибка открытия файла " << filename << " для записи" << endl;
        return;
    }

    for (const auto& account : accounts) {
        outputFile << account->getLogin() << " "
                   << sObj.encrypt(account->getPassword()) << " "
                   << account->getIsAdmin() << endl;
    }

    outputFile.close();
}

vector<shared_ptr<User>> WorkWithFiles::readAccountsFromFile() const {
    string fileName = "/Users/ulanatozik/Материалы по учебе (БГУИР)/2 курс/Кодик/mycoursework2/mycoursework2/accounts.txt";
    vector<shared_ptr<User>> accounts;
    EnterSystem sObj;
    ifstream inFile(fileName);
    
    if (inFile.is_open()) {
        string login, password, isAdminStr;
        while (inFile >> login >> password >> isAdminStr) {
            bool isAdmin = (isAdminStr == "1");
            shared_ptr<User> newUser;

            // Создаем пользователя в зависимости от его роли
            if (isAdmin) {
                newUser = make_shared<AdminUser>(login, sObj.decrypt(password));
            } else {
                newUser = make_shared<RegularUser>(login, sObj.decrypt(password));
            }

            accounts.push_back(newUser);
        }
        inFile.close();
    } else {
        cerr << "Невозможно открыть файл " << fileName << endl;
    }
    return accounts;
}


void WorkWithFiles::writeFurnitureToFile(const vector<Furniture>& furnitureProducts) const {
    string filename = "/Users/ulanatozik/Материалы по учебе (БГУИР)/2 курс/Кодик/mycoursework2/mycoursework2/furnitProducts.txt";  // Используем абсолютный путь

    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cerr << "Ошибка открытия файла " << filename << " для записи." << std::endl;
        return;
    }

    // Записываем товары в файл, включая totalSoldQuantity
    for (const Furniture& furniture : furnitureProducts) {
        outputFile << furniture.getProductType() << " "
                   << furniture.getMaterial() << " "
                   << furniture.getBrand() << " "
                   << furniture.getColor() << " "
                   << furniture.getPrice() << " "
                   << furniture.getAmount() << " "
                   << furniture.getPurchasePrice() << " "
                   << furniture.getTotalSoldQuantity() << std::endl;  // Добавляем поле totalSoldQuantity
    }

    if (outputFile.fail()) {
        cerr << "Ошибка записи в файл " << filename << std::endl;
    }

    outputFile.close();
}



vector<Furniture> WorkWithFiles::readFurnitureFromFile() const {
    string fileName = "/Users/ulanatozik/Материалы по учебе (БГУИР)/2 курс/Кодик/mycoursework2/mycoursework2/furnitProducts.txt";  // Используйте абсолютный путь или относительный
    vector<Furniture> furnitureProducts;
    
    ifstream inputFile(fileName);
    if (inputFile.is_open()) {
        double price, purchasePrice;  // Обновляем типы данных для цены и закупочной цены
        int amount, totalSoldQuantity;  // Добавляем переменную для totalSoldQuantity
        string productType, material, brand, color;
        
        // Чтение из файла
        while (inputFile >> productType >> material >> brand >> color >> price >> amount >> purchasePrice >> totalSoldQuantity) {
            Furniture f;
            f.setProductType(productType);
            f.setMaterial(material);
            f.setBrand(brand);
            f.setColor(color);
            f.setPrice(price);
            f.setAmount(amount);
            f.setPurchasePrice(purchasePrice);  // Устанавливаем закупочную цену
            f.setTotalSoldQuantity(totalSoldQuantity);  // Устанавливаем количество проданных товаров

            furnitureProducts.push_back(f);
        }
        
        inputFile.close();
    } else {
        cerr << "Ошибка открытия файла " << fileName << std::endl;
    }

    return furnitureProducts;
}



