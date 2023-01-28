#ifndef MAIN_CPP_POLE_H
#define MAIN_CPP_POLE_H


class Pole {
private:
    int wartosc;
    bool odkryte;
    bool flaga;
    bool mina;
public:
    Pole();

    void set_wartosc(int);
    void set_odkryte(bool);
    void set_flaga(bool);
    void set_mina(bool);

    int get_wartosc();
    bool czy_odkryte();
    bool czy_flaga();
    bool czy_mina();

};


#endif //MAIN_CPP_POLE_H
