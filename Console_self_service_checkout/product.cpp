// Created by agent on 25.01.2022.
#include "product.h"

void product::print_values() {          //wypisanie danych
    std::cout << std::setw(15) << std::left <<this->name <<  std::setw(15) << std::left << this->category
    <<  std::setw(15) << std::left << this->type <<  std::setw(15) << std::left << this->vat
    <<  std::setw(15) << std::left << this->price;
}

product::product() {            //konstruktory
    this->name = "";
    this->type = "";
    this->category = "";
    this->price = 0;
    this->vat = 0;
}

product::product(std::string name, std::string type, std::string category, double price, double vat) {
    this->name = name;
    this->type = type;
    this->category = category;
    this->price = price;
    this->vat = vat;
}

void product::write_product() {         //wpisz produkt
    this->print_values();
}

std::string product::get_name() {       //pobieranie nazwy
    return this->name;
}

bool product::check_type() {            //sprawdzenie typu
    if(this->type == "szt"){
        return true;
    }
    return false;
}

product::~product() {           //destruktor
}

double product::get_price() {           //pobierz cene
    return this->price;
}

std::string product::get_category() {           //pobierz kategorie
    return this->category;
}

double product::get_tax() {             //pobierz podatek
    return this->vat;
}

double product::get_weight() {          //pobierz wage
    return 0;
}





