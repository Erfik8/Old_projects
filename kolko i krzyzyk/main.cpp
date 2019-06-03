#include <iostream>
#include "k_i_k.h"
#include <conio.h>
#include <windows.h>

using namespace std;

int main()
{
    while (1)
    {
        kolko_i_krzyzyk * NOWA_PLANSZA = new kolko_i_krzyzyk;
        char numer_kratki;
        char wygrany;
        while (1)
        {
            NOWA_PLANSZA->DRUKUJ();
            if (NOWA_PLANSZA->CZY_KONIEC_GRY()!=0)
            {
                if (NOWA_PLANSZA->CZY_KONIEC_GRY()==1)
                cout << "koniec gry, wygrywa gracz: "<< wygrany<<endl;
                else if (NOWA_PLANSZA->CZY_KONIEC_GRY()==2)
                cout << "remis, nikt nie wygral" <<endl;
                cout << "chcesz zagrac od nowa ? "<<endl;
                numer_kratki = getch();
                if (numer_kratki == 'Y'|| numer_kratki == 'y')
                {
                    delete NOWA_PLANSZA;
                    system("cls");
                    break;
                }
                else
                {
                    exit(0);
                }
            }
            cout << "ruch gracza: " << NOWA_PLANSZA->RUCH_GRACZA()<<endl;
            wygrany = NOWA_PLANSZA->RUCH_GRACZA();
            cout << "wpisz numer kratki obok, aby zatwierdzic: ";
            numer_kratki = getch();
            while (NOWA_PLANSZA->ZNAJDZ_NUMER(numer_kratki)== true)
            {
                cout <<endl<< "zly numer, podaj ponownie";
                numer_kratki = getch();
            }
            NOWA_PLANSZA->ZAPISZ_RUCH(numer_kratki);
            system("cls");
        }
    }

}
