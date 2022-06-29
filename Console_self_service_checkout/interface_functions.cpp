// Created by agent on 26.01.2022.
#include "interface_functions.h"


//Tutaj mamy funkcje oprawy wizualnej a takrze cmp do sorta
void line_i() {
    std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
}

void line_long(){
    std::cout << "--------------------------------------------------------------------------------------------------------------------" << std::endl;
}

void table_products(){
    std::cout << std::setw(15) << std::left << "[nazwa]" <<  std::setw(15) << std::left << "[kategoria]"
    <<  std::setw(15) << std::left << "[typ]" <<  std::setw(15) << std::left << "[vat]" <<  std::setw(15) << std::left << "[cena]"
    << std::setw(18) << std::left << "[za jaka wage]" <<std::endl;
}

void table_bin(){
    std::cout << std::setw(15) << std::left << "[nazwa]" <<  std::setw(15) << std::left << "[kategoria]"
              <<  std::setw(15) << std::left << "[typ]" <<  std::setw(15) << std::left << "[vat]" <<  std::setw(15) << std::left << "[cena]"
              << std::setw(18) << std::left << "[za jaka wage]" <<std::setw(23) << std::left << "[ilosc/waga w koszyku]" << std::endl;
}

bool cmp_alph(std::pair<product*, double> x, std::pair<product*, double> y){
    return x.first->get_name() < y.first->get_name();
}

bool cmp_price_up(std::pair<product*, double> x, std::pair<product*, double> y){
    return x.first->get_price() < y.first->get_price();
}

bool cmp_price_down(std::pair<product*, double> x, std::pair<product*, double> y){
    return x.first->get_price() > y.first->get_price();
}

bool cmp_alph_cat(std::pair<product*, double> x, std::pair<product*, double> y){
    if(x.first->get_category() == y.first->get_category())
    {
        return x.first->get_name() < y.first->get_name();
    } else {
        return x.first->get_category() < y.first->get_category();
    }
}

void menu(){
    std::cout << std::setw(25) << std::right << "MENU KASY" << std::endl;
    std::cout << "[1. Wypisz dostepne produkty w sklepie]" << std::endl;
    std::cout << "[2. Dodaj produkt do koszyka]" << std::endl;
    std::cout << "[3. Edytuj koszyk]" << std::endl;
    std::cout << "[4. Wypisz produkty w koszyku]" << std::endl;
    std::cout << "[5. Podsumowanie zakupow]" << std::endl;
    std::cout << "[6. Zakoncz zakupy]" << std::endl;
    std::cout << std::endl;
    std::cout << "Wybierz opcje: " << std::endl;
}
