// Created by agent on 25.01.2022.
#pragma once
#include "product.h"

class luz: public product{          //klasa przechowuje produkty na wage
private:
    double weight;

public:
    luz();          //konstruktory
    luz(std::string name, std::string type, std::string category, double price, double vat, double weight);

    double get_weight();            //zwroc wage
    void write_product();           //wypisz produkt typu luz

    ~luz();         //destruktor
};
