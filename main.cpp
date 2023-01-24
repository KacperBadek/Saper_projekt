#include <iostream>
#include "Pole.h"
#include "Trudnosc.h"
#include <random>

using namespace std;

void wybor_trudnosci(Trudnosc &tryb){
    int opcja;

    cout << "Wybierz tryb trudnosci: " << endl;
    cout << "1.Latwy(10 bomb, plansza 10x10)" << endl;
    cout << "2.Sredni(40 bomb, plansza 18x18)" << endl;
    cout << "3.Trudny(99 bomb, plansza 24x24)" << endl;
    cout << endl;
    cout << "Twoj wybor: ";
    cin >> opcja;

    switch (opcja) {
        case 1: tryb.latwy();
            break;
        case 2: tryb.sredni();
            break;
        case 3: tryb.trudny();
            break;
        default: system("cls");
            cout << "Brak wybranej opcji!" << endl;
            wybor_trudnosci(tryb);
    }

}

void menu(Trudnosc &tryb){
    int opcja;
    cout << "MENU" << endl;

    cout << "1.Graj" << endl;
    cout << "2.Wyjdz" << endl;
    cout << endl;

    cout << "Twoj wybor: ";
    cin >> opcja;

    switch (opcja) {
        case 1: wybor_trudnosci(tryb);
            break;
        case 2: cout << "Shutting down" << endl;
            system("pause");
            exit(0);

        default: system("cls");
            cout << "Brak wybranej opcji!" << endl;
            menu(tryb);
    }
}

void generacja_planszy(int x, int y, Pole **plansza){
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            plansza[j][i].set_wartosc(0);
            plansza[j][i].set_odkryte(false);
        }
    }
}

void ustaw_miny(int x, int y, int poz_x, int poz_y, Pole **plansza){

}

void generacja_min(int x, int y, int ilosc_min, Pole **plansza){
    int licznik=0, poz_x, poz_y;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distx(0,x-1);
    uniform_int_distribution<> disty(0,y-1);


    while(licznik < ilosc_min){
        poz_x = distx(gen);
        poz_y = disty(gen);

        if(!plansza[poz_x][poz_y].get_mina()){
            ustaw_miny(x, y, poz_x, poz_y, plansza);
            licznik++;
        }
    }
}

int main() {
Trudnosc tryb;
menu(tryb);

Pole **plansza;
plansza = new Pole *[tryb.get_x()];
for(int i=0; i<tryb.get_x(); i++){
    plansza[i] = new Pole[tryb.get_y()];
}

generacja_planszy(tryb.get_x(), tryb.get_y(), plansza);
generacja_min(tryb.get_x(), tryb.get_y(), tryb.get_ilosc_min(), plansza);

    return 0;
}
