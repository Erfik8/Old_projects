#include <iostream>

using namespace std;

int KONWERTER(char w);

class kolko_i_krzyzyk
{
private:
    char ** tablica;
    char zapisane_ruchy[9];
    int kolko_lub_krzyzyk[9];
    int aktualne_ruchy;
    int zaczynajacy;
    void WYPISZ_TABLICE();
    void PRZYPISZ_NUMERKI();
public:
    kolko_i_krzyzyk();
    ~kolko_i_krzyzyk();
    void DRUKUJ();
    char RUCH_GRACZA();
    bool ZNAJDZ_NUMER(char wybor);
    void ZAPISZ_RUCH(char wybor);
    void RYSUJ_ZNAK(int znak, int polozenie);
    int CZY_KONIEC_GRY();
};

