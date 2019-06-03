#include <iostream>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include <conio.h>

using namespace std;

bool ODKRYJ_WSZYSTKIE_PUSTE_POLA(char  ** tablica_min, char **tablica_znakow ,short int aktualne_x,short int aktualne_y) // funkcja zwruci falsz, jesli zostanie odkryta mina
{
    bool tymczas;
    if (tablica_min[aktualne_y][aktualne_x]=='X')
        return false;

    tablica_znakow[aktualne_y][aktualne_x] = '?'; // <--- ten znak oznacza, ze czesc planszy jest odkryta. pytajnik nie bedzie pokazywany w grze
    if (tablica_min[aktualne_y][aktualne_x]==' ') // <--- puste pole: rozpoczecie czyszczenie pustych pol aby moc je od razu wyswietlic
    {
        if (aktualne_x-1>=0)
        {
            if (aktualne_y-1>=0&&tablica_znakow[aktualne_y-1][aktualne_x-1]!='?')
                tymczas = ODKRYJ_WSZYSTKIE_PUSTE_POLA(tablica_min,tablica_znakow,aktualne_x-1,aktualne_y-1);
            if (tablica_znakow[aktualne_y][aktualne_x-1]!='?')
                tymczas = ODKRYJ_WSZYSTKIE_PUSTE_POLA(tablica_min,tablica_znakow,aktualne_x-1,aktualne_y);
            if (aktualne_y+1<10&&tablica_znakow[aktualne_y+1][aktualne_x-1]!='?')
                tymczas = ODKRYJ_WSZYSTKIE_PUSTE_POLA(tablica_min,tablica_znakow,aktualne_x-1,aktualne_y+1);
        }
        if (aktualne_y-1>=0&&tablica_znakow[aktualne_y-1][aktualne_x]!='?')
            tymczas = ODKRYJ_WSZYSTKIE_PUSTE_POLA(tablica_min,tablica_znakow,aktualne_x,aktualne_y-1);
        if (aktualne_y+1<10&&tablica_znakow[aktualne_y+1][aktualne_x]!='?')
            tymczas = ODKRYJ_WSZYSTKIE_PUSTE_POLA(tablica_min,tablica_znakow,aktualne_x,aktualne_y+1);
        if (aktualne_x+1<10)
        {
            if (aktualne_y-1>=0&&tablica_znakow[aktualne_y-1][aktualne_x+1]!='?')
                tymczas = ODKRYJ_WSZYSTKIE_PUSTE_POLA(tablica_min,tablica_znakow,aktualne_x+1,aktualne_y-1);
            if (tablica_znakow[aktualne_y][aktualne_x+1]!='?')
                tymczas = ODKRYJ_WSZYSTKIE_PUSTE_POLA(tablica_min,tablica_znakow,aktualne_x+1,aktualne_y);
            if (aktualne_y+1<10&&tablica_znakow[aktualne_y+1][aktualne_x+1]!='?')
                tymczas = ODKRYJ_WSZYSTKIE_PUSTE_POLA(tablica_min,tablica_znakow,aktualne_x+1,aktualne_y+1);
        }
    }
    return true;
}

int main ()
{
    // zmienne globalne, w celu oszczêdzenia pamieci //
    short int i,j;
    short int nawi_x=4,nawi_y=4;
    bool game = true;
    short int znalezione_miny = 0;
    bool bledne_zaznaczenie = false;

    // tworzenie tablicy do sapera oraz do ukrycia planszy //
    char ** saper = new  char * [10];
    char ** gra = new char * [10];
    for (i = 0;i<10;i++)
    {
        saper [i] = new char [10];
        gra[i] = new char [10];
    }

    // inicjacja tablicy znakami spacji oraz planszy do gry krzyzykami//
    for (i = 0; i<10;i++)
    {
        for (j = 0;j<10;j++)
        {
            saper[i][j] = ' ';
            gra[i][j] = '*';
        }
    }

    // dodawanie min //
    srand(time(NULL));
    unsigned short int x,y;
    for (i = 0;i<10;i++)
    {
        x = rand()%10;
        y = rand()%10;
        if (saper[x][y]!=' ')
        {
            i--;
            continue;
        }
        else
        {
            saper[x][y] = 'X'; //<--- X oznacza bombe //
        }
    }

    // ustawienie cyferek w okolo min //
    for (i = 0;i<10;i++)
    {
        for (j = 0;j<10;j++)
        {
            short int tymczasowa = 0;
            if (saper[i][j]=='X')
                continue;
            else
            {
                if ((i-1>=0&&j-1>=0)&&saper[i-1][j-1]=='X') tymczasowa++;
                if ((i-1>=0)&&saper[i-1][j]=='X') tymczasowa++;
                if ((i-1>=0&&j+1<10)&&saper[i-1][j+1]=='X') tymczasowa++;
                if ((j-1>=0)&&saper[i][j-1]=='X') tymczasowa++;
                if ((j+1<10)&&saper[i][j+1]=='X') tymczasowa++;
                if ((i+1<10&&j-1>=0)&&saper[i+1][j-1]=='X') tymczasowa++;
                if ((i+1<10)&&saper[i+1][j]=='X') tymczasowa++;
                if ((i+1<10&&j+1<10)&&saper[i+1][j+1]=='X') tymczasowa++;
            }
            if (tymczasowa!=0)
            saper [i][j] = tymczasowa + 48;
        }
    }

    // wlasciwa gra, naiwgacja WASD, zatwierdzenie klawisz E, ustawienie miny M //
    while (game==true)
    {
        // zero oznacza nawigacje po mapie za pomoca strzalek WASD //
        for (i = 0;i<10;i++)
        {
            for (j = 0;j<10;j++)
            {
                if (i==nawi_y&&j==nawi_x)
                {
                    cout << '0';
                    continue;
                }
                if (gra[i][j]=='?')
                    cout << saper[i][j];
                else
                cout << gra[i][j];
            }
            cout << endl;
        }
        switch (getch())
        {
        case 'a':
        case 'A':
            {
                nawi_x--;
                if (nawi_x<0)
                    nawi_x=9;
            }break;
        case 'd':
        case 'D':
            {
                nawi_x++;
                if (nawi_x>=10)
                    nawi_x=0;
            }break;
        case 'w':
        case 'W':
            {
                nawi_y--;
                if (nawi_y<0)
                    nawi_y=9;
            }break;
        case 's':
        case 'S':
            {
                nawi_y++;
                if (nawi_y>=10)
                    nawi_y=0;
            }break;
        case 'e':
        case 'E':
            {
                if (gra[nawi_y][nawi_x]!='+')
                game = ODKRYJ_WSZYSTKIE_PUSTE_POLA(saper,gra,nawi_x,nawi_y);
            }break;
        case 'm':
        case 'M':
            {
                if (gra[nawi_y][nawi_x]=='*')
                gra[nawi_y][nawi_x] = '+';  // <--- + oznacza zaznaczona mine. nie mozna w tym momencie odslonic pola
                else if (gra[nawi_y][nawi_x]=='+')
                gra[nawi_y][nawi_x] = '*';
            }
        }
    system("cls");

    // sprawdzenie mapy, czy zostala wyczyszczona //
    for (i = 0;i<10;i++)
        {
            for (j = 0;j<10;j++)
            {
                if (gra[i][j]=='+')
                {
                    if (saper[i][j]=='X')
                        znalezione_miny++;
                    else
                    {
                        bledne_zaznaczenie = true;
                    }
                }
            }
            if (bledne_zaznaczenie == true)
            {
                bledne_zaznaczenie = false;
                znalezione_miny = 0;
                break;
            }

        }
        if (znalezione_miny == 10)
        {
            cout << "WYGRALES" <<endl;
            game = false;
        }
        else
            znalezione_miny = 0;
    }



}
