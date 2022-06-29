#include "bin.h"

int main() {
    int act;            //zmienna doo wyboru menu
    bin my_bin;         //koszyk zakupowy
    managment rule;         //zarzadzanie produktami i pracownikami sklepu
    rule.load_products();           //zaladowanie produktow z pliku
    rule.load_employees();          //zaladowanie pracownikow z pliku
    while (act != 6)            //petla menu
    {
        menu();
        std::cin >> act;
        while(true){            //aby nie mozna bylo czegos zamiast liczby wpsiac
            if(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Podaj liczbe nie litere:" << std::endl;
                std::cin >> act;
                continue;
            }
            break;
        }
        std::cout << std::endl;
        switch (act) {
            case 1:         //wylistowanie produktow sklepu
                rule.list_products();
                break;
            case 2:         //dodanie produktu do koszyka
                my_bin.add_product(rule);
                break;
            case 3:         //edycja koszyka
                my_bin.edit_bin(rule);
                break;
            case 4:         //wypisanie koszyka
                my_bin.print_bin_menu();
                break;
            case 5:         //podsumowanie
                my_bin.sump_up();
                break;
            case 6:         //zakonczenie
                line_i();
                std::cout << "DO ZOBACZENIA!" << std::endl;
                break;
            default:
                std::cout << "Nie ma takiej opcji, wybierz jeszcze raz!" << std::endl;
                line_i();
                break;
        }

    }


    return 0;
}
