// Created by agent on 25.01.2022.
#include "luz.h"

luz::luz() : product() {            //konstruktory
    this->weight = 0;
}

luz::luz(std::string name, std::string type, std::string category, double price, double vat, double weight): product(name, type, category, price, vat) {
    this->weight = weight;
}

void luz::write_product()  {         //wypisz produkt
    this->print_values();
    std::cout << std::setw(4) << std::right << "za" << std::setw(7) << std::right << this->weight << std::setw(7) << std::left << " kg";
}

luz::~luz() {           //destruktor
}

double luz::get_weight() {          //zwroc wage
    return this->weight;
}


