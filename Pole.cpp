#include "Pole.h"

Pole::Pole() {
    this->wartosc = 0;
    this->odkryte = false;
    this->flaga = false;
    this->mina = false;
}

void Pole::set_wartosc(int w) {
    this->wartosc=w;
}

void Pole::set_odkryte(bool o) {
    this->odkryte=o;
}

void Pole::set_flaga(bool f) {
    this->flaga=f;
}

void Pole::set_mina(bool m) {
    this->mina=m;
}

int Pole::get_wartosc() {
    return this->wartosc;
}

bool Pole::czy_odkryte() {
    return this->odkryte;
}

bool Pole::czy_flaga() {
    return this->flaga;
}

bool Pole::czy_mina() {
    return this->mina;
}