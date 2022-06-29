// Created by agent on 26.01.2022.
#pragma once
#include "luz.h"

void line_i();          //wypisuje linie
void line_long();           //wypisuje dluzsza linie
void table_products();          //wypisuje poczatek tabeli dla produktow
void table_bin();           //wypisuje poczatek tabeli dla koszyka
void menu();            //wypsije meny


//Funkcje porownujace
bool cmp_alph(std::pair<product*, double> x, std::pair<product*, double> y);
bool cmp_price_up(std::pair<product*, double> x, std::pair<product*, double> y);
bool cmp_price_down(std::pair<product*, double> x, std::pair<product*, double> y);
bool cmp_alph_cat(std::pair<product*, double> x, std::pair<product*, double> y);

