//
//
//

#ifndef MAIN_CPP_TRUDNOSC_H
#define MAIN_CPP_TRUDNOSC_H


class Trudnosc {
public:
    int x, y, ilosc_min, ilosc_flag;

    Trudnosc();

    void set_x(int);
    void set_y(int);
    void set_ilosc_min(int);
    void set_ilosc_flag(int);

    int get_x();
    int get_y();
    int get_ilosc_min();
    int get_ilosc_flag();

    void latwy();
    void sredni();
    void trudny();
};


#endif //MAIN_CPP_TRUDNOSC_H
