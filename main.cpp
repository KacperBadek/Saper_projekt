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
    system("cls");

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
    if(!plansza[poz_x][poz_y].czy_mina()) {
        plansza[poz_x][poz_y].set_mina(true);

        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {

                if (poz_x + j < 0 || poz_y + i < 0) continue;
                if (poz_x + j > x-1 || poz_y + i > y-1) continue;
                if (plansza[poz_x + j][poz_y + i].czy_mina()) continue;

                plansza[poz_x + j][poz_y + i].set_wartosc(plansza[poz_x + j][poz_y + i].get_wartosc() + 1);
            }
        }
    }
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

        if(!plansza[poz_x][poz_y].czy_mina()){
            ustaw_miny(x, y, poz_x, poz_y, plansza);
            licznik++;
        }
    }
}

void rysuj_plansze(int x, int y, int flagi, Pole **plansza){
    system("cls");

//! Os X
    for(int i = 0; i < x; i++){
        if(i == 0) cout << "   ";
         cout << i+1;
    }
    cout << endl;

    //! Os Y
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){

            if(j == 0){
                cout << i+1;
                if(i < 9) cout << "  ";
                else cout << " ";
            }

            if(plansza[j][i].czy_odkryte()){
                if(plansza[j][i].get_wartosc() == 0){
                    if(plansza[j][i].czy_mina()) cout << "*";
                    else cout << " ";
                }
                else{
                    if(plansza[j][i].czy_mina()) cout << "*";
                    else cout << plansza[j][i].get_wartosc();
                }
            }
            if(!plansza[j][i].czy_odkryte()){
                if(plansza[j][i].czy_flaga()) cout << "F";
                    // else if(p[j][i].mina) cout << "*"; //!testowanie
                else cout << "#"; //(char)254u
            }
        }
        cout << endl;
    }

    cout << "Flagi: " << flagi << endl;
    cout << endl;
}

void odkryj_pole(){

}

void odkryj_miny(int x, int y, int flagi, Pole **plansza){
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            if(plansza[j][i].czy_mina()){
                plansza[j][i].set_odkryte(true);
                rysuj_plansze(x, y, flagi, plansza);
            }
        }
    }
}

void sterowanie_akcja(int wybor, int x, int y, int poz_x, int poz_y, int flagi, Pole **plansza){
    switch(wybor){
        case 1: {
            if(plansza[poz_x][poz_y].czy_mina()){
                odkryj_miny(x, y, flagi, plansza);
                cout << "Trafiles na mine, przegrales!!!" << endl;
                system("pause");
                free(*plansza);
                free(plansza);
                exit(0);
            }
            else odkryj_pole();
        }
            break;
        case 2:{
            if(flagi > 0){
                if(!plansza[poz_x][poz_y].czy_odkryte()){
                    if(!plansza[poz_x][poz_y].czy_flaga()){
                        plansza[poz_x][poz_y].set_flaga(true);
                        flagi--;
                    }
                }
            }
        }
            break;
        case 3:{
            if(plansza[poz_x-1][poz_y-1].czy_flaga()){
                plansza[poz_x-1][poz_y-1].set_flaga(false);
                flagi++;
            }
        }
            break;
        default: cout << "Brak wybranej opcji!" << endl;

    }
}

void sterowanie(int x, int y, int flagi, Pole **plansza){
    int wybor, poz_x, poz_y;
    cout << "Co chcesz zrobic?" << endl;
    cout << "1. Odkryj pole" << endl;
    cout << "2. Ustaw flage" << endl;
    cout << "3. Usun flage" << endl;
    cout << "Twoj wybor: ";
    cin >> wybor;

    if(wybor < 1 || wybor > 3){
        cout << endl;
        cout << "Brak podanej opcji!" << endl;
        sterowanie(x, y, flagi, plansza);
    }
    cout << endl;

    cout << "Podaj x: ";
    cin >> poz_x;
    poz_x -= 1;
    cout << "Podaj y: ";
    cin >> poz_y;
    poz_y -= 1;

    sterowanie_akcja(wybor, x, y, poz_x, poz_y, flagi, plansza);
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
rysuj_plansze(tryb.get_x(), tryb.get_y(), tryb.get_ilosc_flag(), plansza);
sterowanie(tryb.get_x(), tryb.get_y(), tryb.get_ilosc_flag(), plansza);
    system("pause");

    return 0;
}
