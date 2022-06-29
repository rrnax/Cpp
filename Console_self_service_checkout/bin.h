// Created by agent on 25.01.2022.
#pragma once
#include "managment.h"
#include <utility>
#include <algorithm>

class bin {
private:
    std::vector<std::pair<product*, double>> bin_list;

public:
    void add_product(managment tab);            //dodaj produkt
    void edit_bin(managment tab);           //edytuj koszyk
    void print_bin();           //wypisz koszyk
    bool check_product_in_bin(std::string it);             //sprawdz produkt w koszyku
    void change_amount(double add_a, std::string it);           //zmien ilosc/wage przez dodanie do obecnej wartosci
    void change_amount_2(double add_a, std::string it);         //zmien ilosc/wage poprzez podanie nowej
    void print_bin_sort(int t);         //posortuj koszyk
    void print_bin_menu();          //wyswietl menu kopszyka
    void sump_up();         //pdosumuj
};
