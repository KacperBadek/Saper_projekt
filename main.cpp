#include <iostream>
#include "Pole.h"
#include "Trudnosc.h"
#include <random>
#include <windows.h>

using namespace std;

void wybor_trudnosci(Trudnosc &tryb){
    int opcja;

    cout << "Wybierz tryb trudnosci: " << endl;
    cout << "1.Latwy(10 bomb, plansza 10x10)" << endl;
    cout << "2.Sredni(40 bomb, plansza 18x18)" << endl;
    cout << "3.Trudny(99 bomb, plansza 24x24)" << endl;
    cout << "4.Niestandardowy(Podawane wartosci musza byc wieksze niz 0)" << endl;
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
        case 4: tryb.niestandardowy();
            break;
        default: system("cls");
            cout << "Brak wybranej opcji!" << endl;
            wybor_trudnosci(tryb);
    }

}

void zasady_gry(){
    system("cls");
    cout << "Gra polega na odkrywaniu na planszy poszczegolnych pol w taki sposob, aby nie natrafic na mine." << "\n";
    cout << "Na kazdym z odkrytych pol napisana jest liczba min, ktore bezposrednio stykaja sie z danym polem." << "\n";
    cout << "Jesli min jest zero to na polu nie ma wpisanej liczby." << "\n";
    cout << "Nalezy uzywac tych liczb by wydedukowac gdzie schowane sa miny." << "\n";
    cout << "Jesli oznaczymy dane pole flaga, jest ono zabezpieczone przed odslonieciem, dzieki czemu nie odslonimy miny." << "\n";
    cout << "Aby wygrac nalezy odslonic wszystkie pola ktore nie chowaja miny pod spodem." << "\n";
    cout << "\n";
    system("pause");
}

void menu(Trudnosc &tryb){
    int opcja;
    cout << "MENU" << endl;

    cout << "1.Graj" << endl;
    cout << "2.Zasady gry" << endl;
    cout << "3.Wyjdz" << endl;
    cout << endl;

    cout << "Twoj wybor: ";
    cin >> opcja;
    system("cls");

    switch (opcja) {
        case 1: wybor_trudnosci(tryb);
            break;
        case 2: zasady_gry();
        system("cls");
            menu(tryb);
            break;
        case 3: cout << "Shutting down" << endl;
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
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

//! Os X
    for(int i = 0; i < x; i++){
        if(i == 0) cout << "   ";
        if(i < 9) cout << " " << i+1 << "  ";
        else cout << " " << i+1 << " ";
    }
    cout << endl;

    for(int i = 0; i < x; i++){
        if(i == 0) cout << "   ";
        cout << "---" << " ";
    }
    cout << endl;

    //! Os Y
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){

            if(j == 0){
                cout << i+1;
                if(i < 9) cout << " | ";
                else cout << "| ";
            }

            if(plansza[j][i].czy_odkryte()){
                if(plansza[j][i].get_wartosc() == 0){
                    if(plansza[j][i].czy_mina()){
                        SetConsoleTextAttribute(h, 4);
                        cout << "*";
                        SetConsoleTextAttribute(h, 7);
                    }
                    else cout << " ";
                }
                else{
                    if(plansza[j][i].czy_mina()){
                        SetConsoleTextAttribute(h, 4);
                        cout << "*";
                        SetConsoleTextAttribute(h, 7);
                    }
                    else cout << plansza[j][i].get_wartosc();
                }
            }
            if(!plansza[j][i].czy_odkryte()){
                if(plansza[j][i].czy_flaga()){
                    SetConsoleTextAttribute(h, 2);
                    cout << "F";
                    SetConsoleTextAttribute(h, 7);
                }
                //else if(plansza[j][i].czy_mina()) cout << "*"; //!testowanie
                else cout << (char)254u;
            }

            cout << " | ";

        }
        cout << endl;
        for(int i = 0; i < x; i++){
            if(i == 0) cout << "   ";
            cout << "---" << " ";
        }
        cout << endl;
    }

    cout << "Flagi: " << flagi << endl;
    cout << endl;
}

void odkryj_pole(int x, int y, int poz_x, int poz_y, Pole **plansza){
    if(poz_x < 0 || poz_x > x-1) return;
    if(poz_y < 0 || poz_y > y-1) return;
    if(plansza[poz_x][poz_y].czy_odkryte()) return;

    if(!plansza[poz_x][poz_y].czy_odkryte() && !plansza[poz_x][poz_y].czy_mina()){
        plansza[poz_x][poz_y].set_odkryte(true);
    }

    if(plansza[poz_x][poz_y].get_wartosc() != 0) return;

    odkryj_pole(x, y, poz_x-1, poz_y-1, plansza);
    odkryj_pole(x, y, poz_x-1, poz_y, plansza);
    odkryj_pole(x, y, poz_x-1, poz_y+1, plansza);
    odkryj_pole(x, y, poz_x+1, poz_y-1, plansza);
    odkryj_pole(x, y, poz_x+1, poz_y, plansza);
    odkryj_pole(x, y, poz_x+1, poz_y+1, plansza);
    odkryj_pole(x, y, poz_x, poz_y-1, plansza);
    odkryj_pole(x, y, poz_x, poz_y+1, plansza);

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

void sterowanie_akcja(int wybor, int x, int y, int poz_x, int poz_y, int flagi, Trudnosc &tryb, Pole **plansza){
    switch(wybor){
        case 1: {
            if(plansza[poz_x][poz_y].czy_flaga());
            else if(plansza[poz_x][poz_y].czy_mina() && !plansza[poz_x][poz_y].czy_flaga()){
                odkryj_miny(x, y, flagi, plansza);
                cout << "Trafiles na mine, przegrales!!!" << endl;
                system("pause");
                free(*plansza);
                free(plansza);
                exit(0);
            }
            else odkryj_pole(x, y ,poz_x, poz_y, plansza);
        }
            break;
        case 2:{
            if(flagi > 0){
                if(!plansza[poz_x][poz_y].czy_odkryte()){
                    if(!plansza[poz_x][poz_y].czy_flaga()){
                        plansza[poz_x][poz_y].set_flaga(true);
                        tryb.set_ilosc_flag(flagi - 1);
                    }
                }
            }
        }
            break;
        case 3:{
            if(plansza[poz_x][poz_y].czy_flaga()){
                plansza[poz_x][poz_y].set_flaga(false);
                tryb.set_ilosc_flag(flagi + 1);
            }
        }
            break;
        default: cout << "Brak wybranej opcji!" << endl;

    }
}

void sterowanie(int x, int y, int flagi, Trudnosc &tryb, Pole **plansza){
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
        sterowanie(x, y, flagi,tryb, plansza);
    }
    cout << endl;

    cout << "Podaj x: ";
    cin >> poz_x;
    poz_x -= 1;
    cout << "Podaj y: ";
    cin >> poz_y;
    poz_y -= 1;

    sterowanie_akcja(wybor, x, y, poz_x, poz_y, flagi, tryb, plansza);
}

bool czy_wygrana(int x, int y, int ilosc_min, Pole **plansza){
    int wszystkie_pola = x * y;
    int pola_odkryte=0;

    for(int i = 0; i < y; i++){
        for(int j = 0 ; j < x; j++){
            if(plansza[j][i].czy_odkryte()){
                pola_odkryte++;
            }
        }
    }

    if(pola_odkryte == (wszystkie_pola - ilosc_min)){
        cout << "Gratulacje wygrales!!!" << endl;
        return true;
    }
    return false;
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

while(!czy_wygrana(tryb.get_x(), tryb.get_y(), tryb.get_ilosc_min(), plansza)){
    sterowanie(tryb.get_x(), tryb.get_y(), tryb.get_ilosc_flag(), tryb, plansza);
    rysuj_plansze(tryb.get_x(), tryb.get_y(), tryb.get_ilosc_flag(), plansza);
}

    system("pause");
    free(*plansza);
    free(plansza);
    exit(0);

}
