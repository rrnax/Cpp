// Created by agent on 25.01.2022.
#pragma once
#include <vector>
#include <fstream>
#include "employee.h"
#include "interface_functions.h"

class managment {
private:
    std::vector<product*> supplyes;          //vector wszystkich prodktów
    std::vector<employee> workers;

public:
    void load_products();           //załadowanie produktów z pliku do vektora
    void list_products();           //wypisanie wszystkich produktów
    void load_employees();          //zaladowanie pracownikow
    void list_employees();          //wypisanie id pracownikow
    bool authorize();           //autooryzacja pracownika
    product* find_product(std::string item);            //znajdz produkt
};
