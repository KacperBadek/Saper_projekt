//
//
//

#include "Trudnosc.h"

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