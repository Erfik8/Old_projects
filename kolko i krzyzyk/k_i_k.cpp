#include <iostream>
#include <ctime>
#include <cstdlib>
#include "k_i_k.h"

using namespace std;

kolko_i_krzyzyk::kolko_i_krzyzyk()
{
    tablica = new char *[11];
    for (int i = 0;i<11;i++)
    {
        tablica[i] = new char [11];
    }
    for (int j = 0;j<9;j++)
        kolko_lub_krzyzyk[j] = 2;
    srand(time(NULL));
    zaczynajacy = rand()% 2;
    aktualne_ruchy = 0;
    WYPISZ_TABLICE();
}
kolko_i_krzyzyk::~kolko_i_krzyzyk()
    {
        for (int i = 0;i<11;i++)
        {
            delete [] tablica[i];
        }
        delete [] tablica;
    }
void kolko_i_krzyzyk::WYPISZ_TABLICE()
{
    for (int i = 0; i <11 ; i++)
    {
        for (int j = 0; j <11 ; j++)
        {
            if ((i==3)||(i==7))
                tablica [i][j] = '-';
            else if ((j==3)||(j==7))
                tablica [i][j] = '|';
            else
            tablica [i][j] = ' ';
        }
    }
    PRZYPISZ_NUMERKI();
}
void kolko_i_krzyzyk::PRZYPISZ_NUMERKI()
{
    tablica[1][1] = '1';
    tablica[1][5] = '2';
    tablica[1][9] = '3';
    tablica[5][1] = '4';
    tablica[5][5] = '5';
    tablica[5][9] = '6';
    tablica[9][1] = '7';
    tablica[9][5] = '8';
    tablica[9][9] = '9';
}
void kolko_i_krzyzyk::DRUKUJ()
{
    for (int i = 0; i <11 ; i++)
    {
        for (int j = 0; j <11 ; j++)
        cout << tablica [i][j];
        cout << endl;
    }
}
char kolko_i_krzyzyk::RUCH_GRACZA()
{
    if (zaczynajacy == 0) // ruch gracza kolko
        return 'O';
    else // ruch gracza krzyzyk
        return 'X';
}
bool kolko_i_krzyzyk::ZNAJDZ_NUMER(char wybor)
{
    for (int i = 0; i <aktualne_ruchy; i++)
    {
        if (zapisane_ruchy[i]==wybor)
            return true;
    }
    switch (wybor)
    {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        return false;
    }
    break;
    default:
    {
        return true;
    }
    break;
    }
}
int KONWERTER(char w)
{
    switch (w)
    {
        case '1': return 1; break;
        case '2': return 2; break;
        case '3': return 3; break;
        case '4': return 4; break;
        case '5': return 5; break;
        case '6': return 6; break;
        case '7': return 7; break;
        case '8': return 8; break;
        default: return 9; break;
    }
}
void kolko_i_krzyzyk::RYSUJ_ZNAK(int znak, int polozenie)
{
    int polozenie_x,polozenie_y;
    switch (polozenie)
    {
    case 1:
    {
        polozenie_x = 0;
        polozenie_y = 0;
    }
    break;
    case 2:
    {
        polozenie_x = 0;
        polozenie_y = 4;
    }
    break;
    case 3:
    {
        polozenie_x = 0;
        polozenie_y = 8;
    }
    break;
    case 4:
    {
        polozenie_x = 4;
        polozenie_y = 0;
    }
    break;
    case 5:
    {
        polozenie_x = 4;
        polozenie_y = 4;
    }
    break;
    case 6:
    {
        polozenie_x = 4;
        polozenie_y = 8;
    }
    break;
    case 7:
    {
        polozenie_x = 8;
        polozenie_y = 0;
    }
    break;
    case 8:
    {
        polozenie_x = 8;
        polozenie_y = 4;
    }
    break;
    case 9:
    {
        polozenie_x = 8;
        polozenie_y = 8;
    }
    break;
    }
    if (znak == 0)
    {
        tablica[polozenie_x][polozenie_y+1] = 'O';
        tablica[polozenie_x+1][polozenie_y] = 'O';
        tablica[polozenie_x+1][polozenie_y+1] = ' ';
        tablica[polozenie_x+1][polozenie_y+2] = 'O';
        tablica[polozenie_x+2][polozenie_y+1] = 'O';
    }
    else
    {
        tablica[polozenie_x][polozenie_y] = 'X';
        tablica[polozenie_x][polozenie_y+2] = 'X';
        tablica[polozenie_x+1][polozenie_y+1] = 'X';
        tablica[polozenie_x+2][polozenie_y] = 'X';
        tablica[polozenie_x+2][polozenie_y+2] = 'X';
    }
}
void kolko_i_krzyzyk::ZAPISZ_RUCH(char wybor)
{
    zapisane_ruchy[aktualne_ruchy] = wybor;
    for (int i = 0; i <aktualne_ruchy; i++)
    cout << zapisane_ruchy[i] << endl;
    aktualne_ruchy++;
    cout << aktualne_ruchy;
    kolko_lub_krzyzyk[KONWERTER(wybor)-1] = zaczynajacy;
    RYSUJ_ZNAK(zaczynajacy,KONWERTER(wybor));
    if (zaczynajacy == 1)
        zaczynajacy = 0;
    else
        zaczynajacy = 1;
}
int kolko_i_krzyzyk::CZY_KONIEC_GRY()
    {
        if ((kolko_lub_krzyzyk[0]!= 2&&kolko_lub_krzyzyk[0]==kolko_lub_krzyzyk[1]&&kolko_lub_krzyzyk[0]==kolko_lub_krzyzyk[2])|| // 1. sprawdzenie
            (kolko_lub_krzyzyk[3]!= 2&&kolko_lub_krzyzyk[3]==kolko_lub_krzyzyk[4]&&kolko_lub_krzyzyk[3]==kolko_lub_krzyzyk[5])|| // linii
            (kolko_lub_krzyzyk[6]!= 2&&kolko_lub_krzyzyk[6]==kolko_lub_krzyzyk[7]&&kolko_lub_krzyzyk[6]==kolko_lub_krzyzyk[8])|| // poziomo
            (kolko_lub_krzyzyk[0]!= 2&&kolko_lub_krzyzyk[0]==kolko_lub_krzyzyk[3]&&kolko_lub_krzyzyk[0]==kolko_lub_krzyzyk[6])|| // 2. sprawdzenie
            (kolko_lub_krzyzyk[1]!= 2&&kolko_lub_krzyzyk[1]==kolko_lub_krzyzyk[4]&&kolko_lub_krzyzyk[1]==kolko_lub_krzyzyk[7])|| // linii
            (kolko_lub_krzyzyk[2]!= 2&&kolko_lub_krzyzyk[2]==kolko_lub_krzyzyk[5]&&kolko_lub_krzyzyk[2]==kolko_lub_krzyzyk[8])|| // pionowo
            (kolko_lub_krzyzyk[0]!= 2&&kolko_lub_krzyzyk[0]==kolko_lub_krzyzyk[4]&&kolko_lub_krzyzyk[0]==kolko_lub_krzyzyk[8])|| // 3. sprawdzenie
            (kolko_lub_krzyzyk[2]!= 2&&kolko_lub_krzyzyk[2]==kolko_lub_krzyzyk[4]&&kolko_lub_krzyzyk[2]==kolko_lub_krzyzyk[6]))  // na krzyz
        {
            return 1;
        }
        else if (kolko_lub_krzyzyk[0]!=2&&kolko_lub_krzyzyk[1]!=2&&
                 kolko_lub_krzyzyk[2]!=2&&kolko_lub_krzyzyk[3]!=2&&
                 kolko_lub_krzyzyk[4]!=2&&kolko_lub_krzyzyk[5]!=2&&
                 kolko_lub_krzyzyk[6]!=2&&kolko_lub_krzyzyk[7]!=2&&
                 kolko_lub_krzyzyk[8]!=2)
        {
            return 2;
        }
        else
            return 0;
    }

