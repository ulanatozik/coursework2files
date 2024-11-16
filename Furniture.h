

 
//
//  Header.h
//  mycoursework
//
//  Created by Ульяна Тозик on 15.09.24.
//

#ifndef FURNITURE_H
#define FURNITURE_H
 

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


class WorkWithProducts {
private:
    int totalSoldQuantity; // Общее количество проданных товаров
    int totalRevenue;      // Общая выручка
    std::vector<double> productCosts; // Вектор для хранения стоимости каждого товара

public:
    // Конструктор с инициализацией
    WorkWithProducts()
        : totalSoldQuantity(0), totalRevenue(0), productCosts() {} // Инициализация пустого вектора

    void initializeProductCosts(const std::vector<double>& costs) {
        productCosts = costs; // Инициализация затрат
    }


    void initializeProductCosts() {
        productCosts.clear();  // Очистка вектора
    }

    void addFurniture();
    void deleteFurniture() const;
    void editFurniture() const;

    void printTotalRevenue();
    void generateReport();
    void printProfit();
    void printProfit() const;
    void orderProduct();
    void productNotification() const;
    void salesNotification() const;
    
    void inputCosts();

    

    void calculateSalesStatistics(int& outTotalSoldQuantity, int& outTotalRevenue) const;

    int getTotalSoldQuantity() const;
    int getTotalRevenue() const;
   

private:
    int calculateTotalCost() const; // Объявление метода для расчета общих издержек
};

class Furniture {
private:
    string productType;
    string material;
    string brand;
    string color;
    int orderNumber;
    double price;           // Цена продажи
    double purchasePrice;   // Закупочная цена
    int amount;             // Количество товара в наличии
    int totalSoldQuantity;  // Количество проданных товаров

public:
    Furniture() : purchasePrice(0), price(0), amount(0), totalSoldQuantity(0) {}

    Furniture(const string& type, const string& mat, const string& br, const string& col, int order, double pr, double purPrice, int amt, int soldQty = 0)
        : productType(type), material(mat), brand(br), color(col), orderNumber(order), price(pr), purchasePrice(purPrice), amount(amt), totalSoldQuantity(soldQty) {}
    
    Furniture& operator=(const Furniture& other) {
          if (this != &other) {
              productType = other.productType;
              material = other.material;
              brand = other.brand;
              color = other.color;
              orderNumber = other.orderNumber;
              price = other.price;
              purchasePrice = other.purchasePrice;
              amount = other.amount;
              totalSoldQuantity = other.totalSoldQuantity;
          }
          return *this;
      }

    virtual void display() const {
        cout << "Product Type: " << productType << ", Material: " << material
             << ", Brand: " << brand << ", Color: " << color
             << ", Price: " << price << ", Purchase Price: " << purchasePrice
             << ", Amount: " << amount << ", Total Sold: " << totalSoldQuantity << endl;
    }

    // Виртуальный метод getPrice для переопределения в производных классах
    virtual double getPrice() const {
        return price;
    }

    // Геттеры
    string getProductType() const { return productType; }
    string getMaterial() const { return material; }
    string getBrand() const { return brand; }
    string getColor() const { return color; }
    double getPurchasePrice() const { return purchasePrice; }
    int getAmount() const { return amount; }
    int getTotalSoldQuantity() const { return totalSoldQuantity; }
    int getOrderNumber() const { return orderNumber; }

    // Сеттеры
    void setProductType(const string& newProductType) { productType = newProductType; }
    void setMaterial(const string& newMaterial) { material = newMaterial; }
    void setPrice(double newPrice) { price = newPrice; }
    void setOrderNumber(int newOrderNumber) { orderNumber = newOrderNumber; }
    void setAmount(int newAmount) { amount = newAmount; }
    void setColor(const string& newColor) { color = newColor; }
    void setBrand(const string& newBrand) { brand = newBrand; }
    void setPurchasePrice(double newPurchasePrice) { purchasePrice = newPurchasePrice; }
    void setTotalSoldQuantity(int soldQuantity) { totalSoldQuantity = soldQuantity; }

    // Метод для продажи товара
    void sell(int quantity) {
        if (quantity <= amount) {
            amount -= quantity;  // Уменьшаем количество на складе
            totalSoldQuantity += quantity;  // Увеличиваем количество проданных
        } else {
            cout << "Недостаточно товара на складе для продажи!" << endl;
        }
    }

    // Метод для подсчета выручки от данного товара
    double calculateRevenue() const {
        return price * totalSoldQuantity;
    }

    // Метод для подсчета затрат на данный товар
    double calculateCosts() const {
        return purchasePrice * totalSoldQuantity;
    }

    // Метод для подсчета прибыли
    double calculateProfit() const {
        return calculateRevenue() - calculateCosts();
    }
};

class CustomFurniture : public Furniture {
private:
    string fabricColor;  // Цвет ткани (для кастомизации)

public:
    // Конструктор для инициализации товара с начальным цветом ткани
    CustomFurniture(const string& type, const string& mat, const string& br, const string& col,
                    int order, double pr, double purPrice, int amt, const string& fabricCol)
        : Furniture(type, mat, br, col, order, pr, purPrice, amt), fabricColor(fabricCol) {}

    // Метод для изменения цвета ткани
    void changeFabricColor(const string& newFabricColor) {
        fabricColor = newFabricColor;  // Обновляем цвет ткани
        cout << "Цвет ткани изменен на: " << fabricColor << endl;
    }

    // Переопределение метода display для вывода информации о товаре с учетом кастомизации
    void display() const override {
        Furniture::display();
        cout << "Цвет ткани: " << fabricColor << endl;  // Показываем кастомизированный цвет ткани
    }

    // Геттер для цвета ткани
    string getFabricColor() const {
        return fabricColor;
    }

    // Переопределение метода для получения новой цены с учетом кастомизации
    double getPrice() const override {
        double additionalCost = 50.0;  /// Например, кастомизация стоит 50 единиц
        return Furniture::getPrice() + additionalCost;
    }
};

#endif // Header_h
