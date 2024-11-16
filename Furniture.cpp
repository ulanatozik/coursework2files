//
//  Furniture.cpp
//  coursework2
//
//  Created by Ульяна Тозик on 15.11.24.
//


#include "WorkServices.h"
#include "AccountsWork.h"
#include "MenuTable.h"
#include "Furniture.h"
#include <sstream>


void WorkWithProducts::addFurniture() {
    auto checker = std::make_unique<ProgrammChecks>();
    auto filesObj = std::make_unique<WorkWithFiles>();
    auto tableObj = std::make_unique<Tables>();

    std::cout << "Добавить товар:" << std::endl;

    std::string productType;
    int typeIndex = 0;

    std::cout << "Введите вид товара (1. Стол, 2. Стул, 3. Кровать, 4. Шкаф, 5. Полка):" << std::endl;
    typeIndex = checker->inputNumber(1, 5);

    while (typeIndex < 1 || typeIndex > 5) {
        std::cout << "Выбранный вид товара недопустим. Пожалуйста, выберите снова:" << std::endl;
        typeIndex = checker->inputNumber(1, 5);
    }

    // Определяем тип товара
    switch (typeIndex) {
        case 1: productType = "Стол"; break;
        case 2: productType = "Стул"; break;
        case 3: productType = "Кровать"; break;
        case 4: productType = "Шкаф"; break;
        case 5: productType = "Полка"; break;
    }

    // Запрос на материал, бренд, цвет товара
    std::cout << "Введите материал товара (например, Дерево, Металл, Пластик): ";
    std::string material = checker->checkString();

    std::cout << "Введите бренд товара: ";
    std::string brand = checker->checkString();

    std::cout << "Введите цвет товара: ";
    std::string color = checker->checkString();
    
    // Запрос на цену товара и закупочную цену
    std::cout << "Введите цену товара: ";
    double price = checker->inputNumber(1, 10000);
    
    std::cout << "Введите закупочную цену товара: ";
    double purchasePrice = checker->inputNumber(1, 10000);
    
    // Запрос на количество товара
    std::cout << "Введите количество товара в наличии: ";
    int amount = checker->inputNumber(0, 100);

    // Создаем новый объект Furniture
    Furniture furniture(productType, material, brand, color, 0, price, amount, purchasePrice);

    // Чтение списка товаров из файла
    auto furnitureProducts = filesObj->readFurnitureFromFile();
    
    // Добавление нового товара в вектор
    furnitureProducts.push_back(furniture);

    // Обновляем вектор с затратами (закупочные цены для каждого товара)
    this->productCosts.push_back(purchasePrice);

    // Запись обновленных данных о товарах в файл
    filesObj->writeFurnitureToFile(furnitureProducts);

    // Вывод обновленной таблицы товаров
    tableObj->printFurnitureTable(furnitureProducts);
}


void WorkWithProducts::deleteFurniture() const { // Удалить товар
    WorkWithFiles filesObj;
    Tables tableObj;
    ProgrammChecks checker;

    // Считываем товары из файла
    auto furnitureProducts = filesObj.readFurnitureFromFile();
    
    // Печатаем таблицу с товарами
    tableObj.printFurnitureTable(furnitureProducts);

    int number_for_delete;
    cout << "----Удаление товара---" << endl;
    cout << "Введите номер товара, который хотите удалить: ";
    number_for_delete = checker.inputNumber(1, furnitureProducts.size());

    // Запрашиваем подтверждение
    cout << "1. Да" << endl
         << "2. Нет" << endl
         << "Ваш выбор? ";
    int yes_or_no = checker.inputNumber(1, 2);
    
    if(yes_or_no == 1) {
        // Удаляем товар из списка
        furnitureProducts.erase(furnitureProducts.begin() + number_for_delete - 1);
        cout << "----Товар успешно удален----" << endl;

        // Перезаписываем обновленный список товаров в файл
        filesObj.writeFurnitureToFile(furnitureProducts);
    } else {
        cout << "Вы отменили удаление" << endl;
    }
}

void WorkWithProducts::editFurniture() const {
    int choice;
    Tables tableObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;

    do {
        vector<Furniture> furnitureProducts = filesObj.readFurnitureFromFile();
        tableObj.printFurnitureTable(furnitureProducts);
        
        int number_for_edit;
        cout << "Введите номер товара, который хотите изменить: " << endl;
        number_for_edit = checker.inputNumber(1, furnitureProducts.size());

        cout << "--------------Введите--------------" << endl;
        cout << "1 - Чтобы изменить вид товара" << endl;
        cout << "2 - Чтобы изменить количество товара в наличии" << endl;
        cout << "3 - Чтобы изменить бренд товара" << endl;
        cout << "4 - Чтобы изменить цену товара" << endl;
        cout << "5 - Чтобы изменить цену закупки товара" << endl;
        cout << "6 - Чтобы выйти из режима редактирования" << endl;
        cout << "Ваш выбор: ";

        choice = checker.inputNumber(1, 6);
        switch(choice) {
        case 1: {
            cout << "--Изменение вида товара--" << endl;
            cout << setw(5) << "Новый вид товара (1. Стол, 2. Стул, 3. Кровать, 4. Шкаф, 5. Полка):" << endl;
            int typeIndex = checker.inputNumber(1, 5);
            string newProductType;
            switch(typeIndex) {
            case 1: newProductType = "Стол"; break;
            case 2: newProductType = "Стул"; break;
            case 3: newProductType = "Кровать"; break;
            case 4: newProductType = "Шкаф"; break;
            case 5: newProductType = "Полка"; break;
            }

            // Создаем новый объект с измененным видом товара
            Furniture updatedFurniture = furnitureProducts.at(number_for_edit - 1);
            updatedFurniture.setProductType(newProductType); // Устанавливаем новый вид товара
            
            // Перегрузка оператора присваивания для обновления текущего товара
            furnitureProducts.at(number_for_edit - 1) = updatedFurniture;

            filesObj.writeFurnitureToFile(furnitureProducts);
            cout << "--Вид товара изменен--" << endl;
            break;
        }
        case 2: {
            cout << "--Изменение количества товара в наличии--" << endl;
            cout << setw(5) << "Новое количество: " << endl;
            int newAmount = checker.inputNumber(0, 100);
            
            // Создаем новый объект с измененным количеством товара
            Furniture updatedFurniture = furnitureProducts.at(number_for_edit - 1);
            updatedFurniture.setAmount(newAmount); // Устанавливаем новое количество

            // Перегрузка оператора присваивания для обновления текущего товара
            furnitureProducts.at(number_for_edit - 1) = updatedFurniture;

            filesObj.writeFurnitureToFile(furnitureProducts);
            cout << "--Количество товара изменено--" << endl;
            break;
        }
        case 3: {
            cout << "--Изменение бренда--" << endl;
            cout << setw(5) << "Новый бренд:" << endl;
            string newBrand = checker.checkString();

            // Создаем новый объект с измененным брендом
            Furniture updatedFurniture = furnitureProducts.at(number_for_edit - 1);
            updatedFurniture.setBrand(newBrand); // Устанавливаем новый бренд

            // Перегрузка оператора присваивания для обновления текущего товара
            furnitureProducts.at(number_for_edit - 1) = updatedFurniture;

            filesObj.writeFurnitureToFile(furnitureProducts);
            cout << "--Бренд изменен--" << endl;
            break;
        }
        case 4: {
            cout << "--Изменение цены товара--" << endl;
            int newPrice = checker.inputNumber(1, 10000);

            // Создаем новый объект с измененной ценой
            Furniture updatedFurniture = furnitureProducts.at(number_for_edit - 1);
            updatedFurniture.setPrice(newPrice); // Устанавливаем новую цену

            // Перегрузка оператора присваивания для обновления текущего товара
            furnitureProducts.at(number_for_edit - 1) = updatedFurniture;

            filesObj.writeFurnitureToFile(furnitureProducts);
            cout << "--Цена товара изменена--" << endl;
            break;
        }
        case 5: {
            cout << "--Изменение цены закупки товара--" << endl;
            double newPurchasePrice = checker.inputNumber(1, 10000);

            // Создаем новый объект с измененной ценой закупки
            Furniture updatedFurniture = furnitureProducts.at(number_for_edit - 1);
            updatedFurniture.setPurchasePrice(newPurchasePrice); // Устанавливаем новую цену закупки

            // Перегрузка оператора присваивания для обновления текущего товара
            furnitureProducts.at(number_for_edit - 1) = updatedFurniture;

            filesObj.writeFurnitureToFile(furnitureProducts);
            cout << "--Цена закупки товара изменена--" << endl;
            break;
        }
        case 6: {
            cout << "Выход из режима редактирования." << endl;
            break;
        }
        }

    } while(choice != 6);
}

void WorkWithProducts::orderProduct() {
    Tables tableObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;
    vector<Furniture> furnitureProducts = filesObj.readFurnitureFromFile();

    cout << "--Заказ товара--" << endl;
    cout << "Введите номер товара, который хотите заказать: " << endl;
    tableObj.printFurnitureTable(furnitureProducts);

    int choice = checker.inputNumber(1, furnitureProducts.size()) - 1;

    if(furnitureProducts[choice].getAmount() > 0) {
        int originalPrice = furnitureProducts[choice].getPrice();
        
        // Применяем скидку
        if(furnitureProducts[choice].getAmount() < 5 && furnitureProducts[choice].getAmount() > 3) {
            int discountedPrice = originalPrice * 0.9;
            cout << "На товар действует скидка 10%. Цена товара изменена с " << originalPrice << " на " << discountedPrice << endl;
            furnitureProducts[choice].setPrice(discountedPrice);
        } else if(furnitureProducts[choice].getAmount() <= 3) {
            int discountedPrice = originalPrice * 0.8;
            cout << "На товар действует скидка 20%. Цена товара изменена с " << originalPrice << " на " << discountedPrice << endl;
            furnitureProducts[choice].setPrice(discountedPrice);
        }

        // Преобразуем выбранный товар в объект CustomFurniture
        CustomFurniture customProduct(
            furnitureProducts[choice].getProductType(),
            furnitureProducts[choice].getMaterial(),
            furnitureProducts[choice].getBrand(),
            furnitureProducts[choice].getColor(),
            furnitureProducts[choice].getOrderNumber(),
            furnitureProducts[choice].getPrice(),
            furnitureProducts[choice].getPurchasePrice(),
            furnitureProducts[choice].getAmount(),
            furnitureProducts[choice].getColor()  // Начальный цвет ткани
        );

        // Запросить кастомизацию ткани
        cout << "Хотите изменить цвет ткани этого товара? (Текущий цвет: " << customProduct.getFabricColor() << ")" << endl;
        cout << "1. Да" << endl;
        cout << "2. Нет" << endl;
        int choice3;
        cin >> choice3;

        if(choice3 == 1) {
            string newColor;
            cout << "Введите новый цвет ткани: ";
            cin.ignore();  // Очищаем буфер перед вводом строки
            getline(cin, newColor);

            // Изменяем цвет ткани через метод кастомизации
            customProduct.changeFabricColor(newColor);
            
            // Пересчитываем цену с учетом кастомизации
            int customizedPrice = customProduct.getPrice();  // Получаем цену с кастомизацией
            cout << "Цена товара после кастомизации: " << customizedPrice << endl;
        }

        cout << "Вы уверены, что хотите заказать этот товар?" << endl;
        cout << "1. Да" << endl;
        cout << "2. Нет" << endl;
        cout << "Ваш выбор: ";
        int choice4;
        cin >> choice4;

        switch(choice4) {
        case 1:
            // Обновляем количество в наличии и количество проданных товаров
            cout << "Ожидайте ответа администратора для подтверждения вашего заказа." << endl;
            sleep(3); // Имитация ожидания
            cout << "Заказ товара подтвержден." << endl;
            
            furnitureProducts[choice].setAmount(furnitureProducts[choice].getAmount() - 1);  // Уменьшаем количество
            furnitureProducts[choice].setTotalSoldQuantity(furnitureProducts[choice].getTotalSoldQuantity() + 1); // Увеличиваем количество проданных товаров

            // Сохраняем изменения в файл
            filesObj.writeFurnitureToFile(furnitureProducts);
            break;
        case 2:
            cout << "Вы отменили заказ товара." << endl;
            return;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    } else if(furnitureProducts[choice].getAmount() == 0) {
        cout << "Выбранного товара нет в наличии. Оформить предзаказ?" << endl;
        cout << "1. Да" << endl;
        cout << "2. Нет" << endl;
        cout << "Ваш выбор?" << endl;
        int choice3;
        cin >> choice3;
        switch(choice3) {
        case 1:
            cout << "Предзаказ оформлен." << endl;
            filesObj.writeFurnitureToFile(furnitureProducts);
            break;
        case 2:
            cout << "Вы отменили предзаказ." << endl;
            return;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    }
}

void WorkWithProducts::printTotalRevenue()
{
    int totalSoldQuantity = 0;
    double totalRevenue = 0.0;  // Используем double для корректной работы с ценой, которая может быть дробной
    
    WorkWithFiles filesObj;
    vector<Furniture> furnitureProducts = filesObj.readFurnitureFromFile();
    
    for(const auto& furniture : furnitureProducts) {
        totalSoldQuantity += furniture.getTotalSoldQuantity();  // Добавляем количество проданных товаров
        totalRevenue += furniture.getPrice() * furniture.getTotalSoldQuantity();  // Умножаем цену на количество проданных
        
        cout << "цена товара: " << furniture.getPrice() << ", продано: "
             << furniture.getTotalSoldQuantity() << " шт." << endl;
    }
  
    cout << "Общая выручка: " << totalRevenue << endl;
    cout << "Общее количество проданных товаров: " << totalSoldQuantity << endl;
}

       
           
void WorkWithProducts::printProfit() {
    int totalSoldQuantity = 0;
    int totalRevenue = 0;
    double totalCost = 0;
    double totalProfit = 0;
    
    // Чтение данных о товарах из файла
    WorkWithFiles filesObj;
    vector<Furniture> furnitureProducts = filesObj.readFurnitureFromFile();
    
    // Запрашиваем дополнительные расходы у пользователя
    double expenses;
    cout << "Введите общие затраты (например, аренда, зарплата и т.п.): ";
    cin >> expenses;

    // Проход по всем товарам и подсчет выручки и стоимости
    for (const auto& furniture : furnitureProducts) {
        if (furniture.getTotalSoldQuantity() > 0) {
            totalSoldQuantity += furniture.getTotalSoldQuantity();
            totalRevenue += furniture.getPrice() * furniture.getTotalSoldQuantity();
            totalCost += furniture.getPrice() * furniture.getTotalSoldQuantity(); // Закупочная цена товара
        }
    }
    
    // Прибыль = Выручка - (Закупочная стоимость + Затраты)
    totalProfit = totalRevenue - totalCost - expenses;

    // Выводим информацию
    cout << "Общее количество проданных товаров: " << totalSoldQuantity << endl;
    cout << "Общая выручка от всех проданных товаров: " << totalRevenue << endl;
    cout << "Общие затраты: " << expenses << endl;
    cout << "Прибыль от продаж: " << totalProfit << endl;
}

void WorkWithProducts::generateReport() {
    int totalSoldQuantity = 0;
    double totalRevenue = 0;  // Обновим тип на double для точности
    double totalCost = 0;
    double totalProfit = 0;
    
    WorkWithFiles filesObj;
    vector<Furniture> furnitureProducts = filesObj.readFurnitureFromFile();
    
    // Запрашиваем дополнительные расходы
    double expenses;
    cout << "Введите общие затраты (например, аренда, зарплата и т.п.): ";
    cin >> expenses;
    
    // Проход по всем товарам для подсчета выручки и прибыли
    for (const auto& furniture : furnitureProducts) {
        // Суммируем количество проданных товаров
        totalSoldQuantity += furniture.getTotalSoldQuantity();
        
        // Рассчитываем выручку от продажи товаров
        totalRevenue += furniture.getPrice() * furniture.getTotalSoldQuantity();
        
        // Рассчитываем затраты на закупку товаров
        totalCost += furniture.getPurchasePrice() * furniture.getTotalSoldQuantity(); // Закупочная цена
        
        // Рассчитываем прибыль
        totalProfit += (furniture.getPrice() - furniture.getPurchasePrice()) * furniture.getTotalSoldQuantity();
    }
    
    // Подсчет общей прибыли с учетом дополнительных расходов
    totalProfit -= expenses;

    // Формирование отчета
    stringstream report;
    report << "--------------------- Отчет о продажах ---------------------\n";
    report << "Общее количество проданных товаров: " << totalSoldQuantity << "\n";
    report << "Общая выручка от всех проданных товаров: " << totalRevenue << " руб.\n";
    report << "Общие затраты на закупку товаров: " << totalCost << " руб.\n";
    report << "Прибыль от продаж (с учетом расходов): " << totalProfit << " руб.\n";

    /// Сохранение отчета в файл
    string filename = "/Users/ulanatozik/Материалы по учебе (БГУИР)/2 курс/Кодик/mycoursework2/mycoursework2/sales_report.txt";
    ofstream reportFile(filename, ios::out);
    if (reportFile.is_open()) {
        reportFile << report.str();
        reportFile.close();
        cout << "Отчет успешно сохранен в файл sales_report.txt" << endl;
    } else {
        cout << "Ошибка при сохранении отчета в файл!" << endl;
    }
}

void WorkWithProducts::productNotification() const {
    WorkWithFiles fileObj;
    vector<Furniture> furnitureProducts = fileObj.readFurnitureFromFile();
    int flag = 0;
    int i = 0;

    for (const auto& furniture : furnitureProducts) {
        if (furniture.getAmount() < 2) {
            cout << "На складе заканчиваются единицы товара " << ++i
                 << " (Вид изделия: " << furniture.getProductType()
                 << ", вид материала: " << furniture.getMaterial()
                 << ", бренд изделия: " << furniture.getBrand()
                 << ", цвет: " << furniture.getColor()
                 << ", количество товара в наличии: " << furniture.getAmount() << ")" << endl;
            flag = 1;
        }
    }
    if (flag == 0) {
        cout << "Нет новых уведомлений." << endl;
    }
}

void WorkWithProducts::salesNotification() const {
    WorkWithFiles fileObj;
    vector<Furniture> furnitureProducts = fileObj.readFurnitureFromFile();
    int flag = 0;
    int i = 0;

    for (const auto& furniture : furnitureProducts) {
        if (furniture.getAmount() < 5 && furniture.getAmount() > 2 && furniture.getAmount() > 0) {
            cout << "Действует скидка 10% на товар " << ++i
                 << " (Вид изделия: " << furniture.getProductType()
                 << ", Материал: " << furniture.getMaterial()
                 << ", Цвет: " << furniture.getColor()
                 << ", Бренд: " << furniture.getBrand()
                 << ", Количество товара в наличии: " << furniture.getAmount() << ")" << endl;
            flag = 1;
        } else if (furniture.getAmount() < 3 && furniture.getAmount() > 0) {
            cout << "Действует скидка 20% на товар " << ++i
                 << " (Вид изделия: " << furniture.getProductType()
                 << ", Материал: " << furniture.getMaterial()
                 << ", Цвет: " << furniture.getColor()
                 << ", Бренд: " << furniture.getBrand()
                 << ", Количество товара в наличии: " << furniture.getAmount() << ")" << endl;
            flag = 1;
        }
    }

    if (flag == 0) {
        cout << "Нет новых уведомлений." << endl;
    }
}


