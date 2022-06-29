// Created by agent on 25.01.2022.
#pragma once
#include <iostream>
#include <iomanip>
#include <limits>

class product {          //klasa przechowująca produkt
protected:
    std::string name, type, category;
    double price, vat;

    void print_values();            //wypisanie danych;

public:
    product();          //konstruktory
    product(std::string name, std::string type, std::string category, double price, double vat);

    virtual void write_product();           //wypisanie produktu
    virtual double get_weight();            //waga
    std::string get_name();         //pobranie nazwy
    bool check_type();          //sprawdz typ produktu
    double get_price();         //cena
    double get_tax();           //podatek
    std::string get_category();         //kategoria

    ~product();         //destruktor
};
