// Created by agent on 25.01.2022.
#pragma once
#include <iostream>
#include <string>

class employee {
private:
    std::string password;
    int nr_id;

public:
    employee();             //konstruktory
    employee(int nr_id, std::string pass);

    bool check_password(std::string pass);          //sprawdz hsaslo
    void print_id();            //wypisz id pracownika
    bool check_nr(int id_t);            //sprawdz id

    ~employee();            //destructor
};


