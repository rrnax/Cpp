// Created by agent on 25.01.2022.
#include "employee.h"

void employee::print_id() {
    std::cout << this->nr_id;           //wypisz id pracownika
}

employee::employee() {          //konstruktory
    this->nr_id = -1;
    this->password = "";
}

employee::employee(int nr_id, std::string pass) {
    this->nr_id = nr_id;
    this->password = pass;
}


bool employee::check_password(std::string pass) {           //sprawdz haslo
    if(this->password == pass)
    {
        return true;
    } else {
        return false;
    }
}

employee::~employee() {         //destruktor
}

bool employee::check_nr(int id_t) {         //sprawdz id
    if(this->nr_id == id_t)
    {
        return true;
    } else {
        return false;
    }
}





