//
//
//

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
    bool get_odkryte();
    bool get_flaga();
    bool get_mina();

};


#endif //MAIN_CPP_POLE_H
