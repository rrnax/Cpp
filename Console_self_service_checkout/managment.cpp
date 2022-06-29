// Created by agent on 25.01.2022
#include "managment.h"

void managment::load_products() {           //załaduj produkty z pliku
    product *temp1;
    luz *temp2;
    std::string name_t, type_t, category_t;
    double price_t, vat_t, weight_t;
    std::ifstream  articles("art.txt");
    if(articles.is_open()){
        while (!articles.eof()){
            articles >> name_t >> price_t >> type_t;
            if(type_t == "luz"){
                articles >> category_t >> vat_t >> weight_t;
                temp2 =  new luz(name_t, type_t, category_t, price_t, vat_t, weight_t);
                this->supplyes.push_back(temp2);
            } else {
                articles >> category_t >> vat_t;
                temp1 =  new product(name_t, type_t, category_t, price_t, vat_t);
                this->supplyes.push_back(temp1);
            }
        }
    } else {
        std::cout << "File art.txt did not open..." << std::endl;
    }
}

void managment::list_products() {           //wypisz wszystkie produkty
    std::cout << std::endl;
    std::cout <<  "LISTA PRODUKTOW W SKLEPIE: " << std::endl;
    std::cout << std::endl;
    table_products();
    line_i();
    for(auto & supplye : this->supplyes)
    {
        supplye->write_product();
        std::cout << std::endl;
        line_i();
    }
    std::cout << std::endl;
}

void managment::load_employees() {          //zaladuj pracownikow
    employee temp;
    int id_t;
    std::string pass_t;
    std::ifstream emp("emp.txt");
    if(emp.is_open()){
        while(!emp.eof()){
            emp >> id_t >> pass_t;
            temp = employee(id_t, pass_t);
            this->workers.push_back(temp);
        }
    } else {
        std::cout << "File emp.txt did not open..." << std::endl;
    }

}

void managment::list_employees() {          //wypisz id pracownikow
    for(auto & worker : this->workers)
    {
        worker.print_id();
        std::cout << std::endl;
    }
}

bool managment::authorize() {           //autoryzuj pracownika
    int id_t;
    std::string pass;
    std::cout << "Prosze podac swoj numer pracownika: " << std::endl;
    std::cin >> id_t;
    while(true){            //aby nie mozna bylo czegos zamiast liczby wpsiac
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Podaj liczbe nie litere:" << std::endl;
            std::cin >> id_t;
            continue;
        }
        break;
    }
    std::cout << "Prosze podac haslo: " << std::endl;
    std::cin >> pass;
    for(auto & worker : this->workers){
        if(worker.check_nr(id_t)){
            if (worker.check_password(pass)) {
                std::cout << "Zalogowano uzytkownika o id: " << id_t << std::endl;
                line_i();
                return true;
            }
        }
    }
    std::cout << "Niewlasciwy login lub haslo!" << std::endl;
    return false;
}

product *managment::find_product(std::string item) {            //znajdz produkt zwraca produkt
    product* temp = nullptr;
    for(int i = 0 ; i < this->supplyes.size(); i++)
    {
        if(this->supplyes[i]->get_name() == item){
            temp = this->supplyes[i];
        }
    }
    return temp;
}
