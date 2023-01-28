#include "Trudnosc.h"
#include <iostream>
using std::cout;
using std::cin;

Trudnosc::Trudnosc() {

    this->x=0;
    this->y=0;
    this->ilosc_min = 0;
    this->ilosc_flag = 0;
}

void Trudnosc::set_x(int xx) {
    this->x=xx;
}

void Trudnosc::set_y(int yy) {
    this->y=yy;
}

void Trudnosc::set_ilosc_min(int mm) {
    this->ilosc_min=mm;
}

void Trudnosc::set_ilosc_flag(int ff) {
    this->ilosc_flag=ff;
}

int Trudnosc::get_x() {
    return this->x;
}

int Trudnosc::get_y() {
    return this->y;
}

int Trudnosc::get_ilosc_min() {
    return this->ilosc_min;
}

int Trudnosc::get_ilosc_flag() {
    return this->ilosc_flag;
}

void Trudnosc::latwy() {
    set_x(10);
    set_y(10);
    set_ilosc_min(10);
    set_ilosc_flag(10);
}

void Trudnosc::sredni() {
    set_x(18);
    set_y(18);
    set_ilosc_min(40);
    set_ilosc_flag(40);
}

void Trudnosc::trudny() {
    set_x(24);
    set_y(24);
    set_ilosc_min(99);
    set_ilosc_flag(99);
}

void Trudnosc::niestandardowy() {
    int niestandardowy_x=0, niestandardowy_y=0, niestandardowe_miny=0, niestandardowe_flagi=0;
    cout << "Podaj rozmiar planszy: " << "\n";

    while(niestandardowy_x <= 0 || niestandardowy_x > 58){
        cout << "Dlugosc osi X(max 58)= ";
        cin >> niestandardowy_x;
    }
    set_x(niestandardowy_x);

    while(niestandardowy_y <= 0 || niestandardowy_y > 99){
        cout << "Dlugosc osi Y(max 99)= ";
        cin >> niestandardowy_y;
    }
    set_y(niestandardowy_y);

    while(niestandardowe_miny <= 0 || niestandardowe_miny > niestandardowy_x * niestandardowy_y){
        cout << "Podaj ilosc min(max os x * os y): ";
        cin >> niestandardowe_miny;
    }
    set_ilosc_min(niestandardowe_miny);

    while(niestandardowe_flagi <= 0){
        cout << "Podaj ilosc flag: ";
        cin >> niestandardowe_flagi;
    }
    set_ilosc_flag(niestandardowe_flagi);
}