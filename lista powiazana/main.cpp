#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstddef>
#include "konwerter.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>

using namespace std;

struct osoba
{
    string imie;
    string nazwisko;
    string telefon;
    string pesel;
    string adres_gmail;
    int numer_porzadkowy;
    osoba *poprzednia;
    osoba *nastepna;
};
osoba *pierwsza = NULL;
osoba *ostatnia = NULL;

string nazwa_pliku = "::NIE_WYBRANO::";

void NAWIGACJA(osoba *prezentacja);
void POKASZ_ELEMENT(osoba *nawigacja);
void POKASZ_LISTE(osoba *kolejne,int limit_na_raz);
void DODAJ_NOWY (osoba *aktualny,bool miejsce_nowej);
void NUMERUJ (osoba *numeracja,int jeden);
void USUN(osoba *usun);
osoba* PRZESUN(char dalej, osoba *przesun);
osoba* ZNAJDZ (int numer, osoba* do_sprawdzenia, bool od_przodu);
void ZMIANA_POLOZENIA(osoba *polozenie);
void NOWY_PARAMETR(osoba *zmiana,char wybor);
int SZUKAJ(osoba *szukaj, char parametr, string fraza, int licznik, int suma);
void ZAPISZ ();
void WCZYTAJ()
{
    fstream wczytaj;
    string linia;
    int licznik = 0;
    wczytaj.open("%%KONTROLA%%PLIKOW%%.txt",ios::in);
    cout << "lista dostepnych kopii listy powiazanej" <<endl;
    while (getline(wczytaj,linia))
    {
        licznik++;
        cout << licznik <<". "<< linia << endl;
    }
    cout << "wpisz numer pliku lub wpisz dowolny numer aby wyjsc: ";
    wczytaj.close();
    wczytaj.open("%%KONTROLA%%PLIKOW%%.txt",ios::in);
    int wybor;
    cin >> wybor;
    if (!((wybor<0)||(wybor>licznik)))
    {
        licznik = 0;
        for (;;)
        {
            getline (wczytaj,linia);
            licznik ++;
            if (wybor == licznik)
                break;
        }
        cout << linia << endl;
        bool USUN_DANE = true;
        if (pierwsza != NULL)
        {
            USUN_DANE = false;
            cout << "w tej sesji sa jeszcze dane, ktore moga byc nie zapisane."<< endl << "chcesz sie ich pozbyc? <Y OR N>" <<endl;
            char wybierz;
            cin >> wybierz;
            if (wybierz == 'y' || wybierz == 'Y')
            {
                USUN_DANE = true;
                osoba *kasowanie = pierwsza;
                for (int i = 1;i <= ostatnia->numer_porzadkowy;i++)
                {
                    pierwsza = kasowanie->nastepna;
                    delete kasowanie;
                    if (pierwsza != NULL)
                    kasowanie = pierwsza;
                }
                ostatnia = NULL;
            }
            else
            {
                cout << endl << "zapisz dane, a nastepnie wczytaj dane z innego pliku" << endl;
                Sleep (1000);
            }
        } // <------------------ DO SKONCZENIA
        if (USUN_DANE == true)
        {
            cout << ":: kontrola numer 1 otworzenie pliku"<<endl;
            wczytaj.close();
            wczytaj.open(linia.c_str(),ios::in);
            nazwa_pliku = linia;
            osoba*nowe_dane = new osoba;
            getline(wczytaj,linia);
            cout << linia<<endl;
            bool dostep = true;
            if (linia == "::HASLO::")
            {
                dostep = false;
                getline(wczytaj,linia);
                cout << "plik zabezpieczony. wpisz haslo: ";
                string haslo;
                for (int j = 0;j<3;j++)
                {
                    cin >> haslo;
                    if (haslo == linia)
                    {
                        dostep = true;
                        break;
                    }
                    cout << "HASLO NIE POPRAWNE, WPISZ PONOWNIE: ";
                }
                getline(wczytaj,linia);
            }

            if ((linia == "::LICZBA::")&&(dostep == true))
            {
                cout << "kontrola numer 2 wczytanie liczby elementow"<<endl;
                getline (wczytaj,linia);
                int ilosc_danych = atoi(linia.c_str());
                cout << "ilosc elementow: "<<ilosc_danych<<endl;
                for (int i = 1;i<=ilosc_danych;i++)
                {
                    getline(wczytaj,nowe_dane->imie);
                    getline(wczytaj,nowe_dane->nazwisko);
                    getline(wczytaj,nowe_dane->telefon);
                    getline(wczytaj,nowe_dane->adres_gmail);
                    getline(wczytaj,nowe_dane->pesel);
                    if ( i == 1)
                    {
                        nowe_dane->poprzednia = NULL;
                        nowe_dane->nastepna = new osoba;
                        nowe_dane->nastepna->poprzednia = nowe_dane;
                        pierwsza = nowe_dane;
                        nowe_dane = nowe_dane->nastepna;
                    }
                    else if (i == ilosc_danych)
                    {
                        nowe_dane->nastepna = NULL;
                        ostatnia = nowe_dane;
                    }
                    else
                    {
                        nowe_dane->nastepna = new osoba;
                        nowe_dane->nastepna->poprzednia = nowe_dane;
                        nowe_dane = nowe_dane->nastepna;
                    }
                }

            }
        }
    }


}

int main()
{
    for (;;)
    {
        system("cls");
        cout << "prezentacja listy powiazanej"<<endl
             << "----------------------------"<<endl;
        cout << "dostepne opcje: "<<endl
             << "1. zarzadzanie lista"<<endl
             << "2. wyswietlenie listy"<<endl
             << "3. zapis listy do pliku tekstowego"<<endl
             << "4. wczytanie listy z pliku"<<endl
             << "5. zamkniecie programu oraz usuniecie niezapisanego postepu"<<endl
             << "6. instrukcja obslugi i nawigacja po programie"<<endl;
        NUMERUJ (pierwsza,1);
        switch (getch())
        {
        case '1':
            {
                NAWIGACJA(pierwsza);

            }break;
        case '2':
            {
                POKASZ_LISTE(pierwsza,1);
                getch();
            }break;

        case '3':
            {
                ZAPISZ();
            }break;
        case '4':
            {
                WCZYTAJ();
                Sleep(1000);
            }break;
        case '5':
            {
                cout << "UWAGA. PO ZAMKNIECIU PROGRAMU CALA LISTA ZOSTANIE ZNISZCZONA"<<endl
                     << "PRZED ZAMKNIECIEM PROGRAMU ZAPISZ LISTE, JESLI JESZCZE TEGO"<<endl
                     << "NIE ZROBILES. CZY MIMO TO CHCESZ ZAMKNAC PROGRAM? <Y OR N>"<<endl;
                if (getch()=='y'||getch()=='Y')
                    exit(0);
            }break;
        case '6':
            {

            }break;
        default:
            {
                cout << "nie ma takiej opcji na liscie"<<endl;
                Sleep(500);
            }break;
        }
    }
}
void NAWIGACJA  (osoba *prezentacja)
{
    system("cls");
    if (pierwsza == NULL)
    {
        cout << "BRAK ELEMENTOW"<<endl;
        cout << "chcesz dodac pierwszy element?"<<endl
             << "wpisz Y lub N"<<endl;
        switch (getch())
        {
        case 'y':
        case 'Y': // kod tworzenia nowego pierwszego elementu. mozna ukryc
            {
                osoba *nowy = new osoba;
                cout << "wpisz imie: ";
                cin >> nowy->imie;
                cout << "wpisz nazwisko: ";
                cin >> nowy->nazwisko;
                cout << "wpisz numer telefonu: ";
                string proba;
                cin >> proba;
                if (WYKRYJ_NIELICZBE(proba)==false)
                {
                    proba = "do uzupelnienia";
                    cout << "wprowadzono bledne dane. uzupelnij rubryke pozniej"<<endl;
                }
                nowy->telefon = proba;
                cout << "wpisz pesel: ";
                cin >> proba;
                if (WYKRYJ_NIELICZBE(proba)==false)
                {
                    proba = "do uzupelnienia";
                    cout << "wprowadzono bledne dane. uzupelnij rubryke pozniej"<<endl;
                }
                nowy->pesel = proba;
                cout << "wpisz adres gamil: ";
                cin >> nowy->adres_gmail;
                nowy->nastepna = NULL;
                nowy->poprzednia = NULL;
                pierwsza = nowy;
                ostatnia = nowy;
            }break;
        case 'n':
        case 'N':
        default :
            {
            }break;
        }
    }
    else // do uzupelnienia kody do zarzadzania lista
    {
        bool wyjscie=false;
        do
        {
            system("cls");
            POKASZ_ELEMENT(prezentacja);
            cout << "wybierz jedna z opcji, wciskajac numer na klawiaturze"<<endl
                 << "-----------------------------------------------------"<<endl
                 << "1. dodaj element przed aktualny"<<endl
                 << "2. dodaj element po aktualnym"<<endl
                 << "3. usun aktualny element"<<endl
                 << "4. przesun dany element"<<endl
                 << "5. zmien parametr danego elementu"<<endl
                 << "6. szukaj elementu, wybierajac parametr oraz wpisujac fraze"<<endl;
            cout << "wcisnij dana litere, aby przeniesc sie do innego elementu"<<endl
                 << "---------------------------------------------------------"<<endl
                 << "A. element wczesniej"<<endl
                 << "D. element dalej"<<endl
                 << "J. skocz do innego elemntu, wpisujac jego numer"<<endl
                 << "S. idz na poczatek"<<endl
                 << "F. idz na koniec"<<endl
                 << "wcisnij dowolny klawisz, aby wyjsc"<<endl;
            switch (getch())
            {
            case '1':
            {
                DODAJ_NOWY(prezentacja,true);
                wyjscie = true;
            }
            break;
            case '2':
            {
                DODAJ_NOWY(prezentacja,false);
                wyjscie = true;
            }
            break;
            case '3':
            {
                USUN(prezentacja);
                wyjscie = true;
            }
            break;
            case '4':
            {
                ZMIANA_POLOZENIA(prezentacja);
                wyjscie = true;

            } break;
            case '5':
            {
                cout << "ktory element chcesz zmienic?"<<endl
                     << "1. imie"<<endl
                     << "2. nazwisko"<<endl
                     << "3. adres e-mail"<<endl
                     << "4. numer telefonu"<<endl
                     << "5. PESEL"<<endl;
                NOWY_PARAMETR(prezentacja,getch());
            } break;
            case '6':
            {
                system("cls");
                cout << "szukaj elementu po parametrze "<<endl;
                cout << "1. imie" <<endl
                     << "2. nazwisko"<<endl
                     << "3. adres e-mail"<<endl
                     << "4. numerze telefonu"<<endl
                     << "5. PESEL"<<endl;
                char wybor;
                cin >> wybor;
                string fraza;
                cout << "wpisz fraze, aby wyszukac: ";
                cin >> fraza;
                if (SZUKAJ(pierwsza,wybor,fraza,1,0)== 0)
                cout << "nie znaleziono elementow" << endl;
                system("pause");
            } break;
            case 'A':
            case 'a':
            {
                if (prezentacja != PRZESUN ('a',prezentacja))
                    prezentacja = PRZESUN ('a',prezentacja);
            }
            break;
            case 'D':
            case 'd':
            {
                if (prezentacja != PRZESUN ('d',prezentacja))
                    prezentacja = PRZESUN ('d',prezentacja);
            }
            break;
            case 'J':
            case 'j':
            {
                cout << "wpisz o ile elementow przeskoczyc"<<endl;
                int skok;
                cin >> skok;
                cout << "wybierz, w ktora strone przeskoczyc <wpisz A(do tylu) lub D(do przodu)>"<<endl;
                char znak;
                cin>> znak;
                for (int a=0; a<skok; a++)
                {
                    if (prezentacja == PRZESUN (znak,prezentacja))
                        break;
                    else
                        prezentacja = PRZESUN (znak,prezentacja);
                }
            }
            break;
            case 'S':
            case 's':
                prezentacja = pierwsza;   break;
            case 'F':
            case 'f':
                prezentacja = ostatnia;   break;
            default:
                wyjscie = true;           break;
            }
        }while (wyjscie == false);
    }
}

void POKASZ_ELEMENT(osoba *nawigacja)
{
        cout<< "numer elementu: "<<nawigacja->numer_porzadkowy<<endl;
        cout<< "imie: "<<nawigacja->imie<<endl
            << "nazwisko: "<<nawigacja->nazwisko<<endl
            << "gmail: "<<nawigacja->adres_gmail<<endl
            << "numer telefonu: "<<nawigacja->telefon<<endl
            << "pesel: "<<nawigacja->pesel<<endl<<endl;
}
void POKASZ_LISTE(osoba *kolejne,int limit_na_raz)
{
    if (kolejne == NULL)
    {
        cout << "BRAK ELEMENTOW" <<endl; Sleep(500);
    }
    else
    {
        POKASZ_ELEMENT(kolejne);
        if ((limit_na_raz == 5)&&(kolejne->nastepna!=NULL))
        {
            cout << "wcisnij dowolny klawisz, aby wyswietlic dalsza liste"<<endl;
            getch();
            system("cls");
            limit_na_raz = 1;
        }
        if (kolejne->nastepna != NULL)
            POKASZ_LISTE(kolejne->nastepna,++limit_na_raz);
    }
}
void DODAJ_NOWY(osoba *aktualny,bool miejsce_nowej)
{
    osoba *nowy = new osoba;
    cout << "wpisz imie: ";
    cin >> nowy->imie;
    cout << "wpisz nazwisko: ";
    cin >> nowy->nazwisko;
    cout << "wpisz numer telefonu: ";
    string proba;
    cin >> proba;
    if (WYKRYJ_NIELICZBE(proba)==false)
    {
        proba = "do uzupelnienia";
        cout << "wprowadzono bledne dane. uzupelnij rubryke pozniej"<<endl;
    }
    nowy->telefon = proba;
    cout << "wpisz pesel: ";
    cin >> proba;
    if (WYKRYJ_NIELICZBE(proba)==false)
    {
        proba = "do uzupelnienia";
        cout << "wprowadzono bledne dane. uzupelnij rubryke pozniej"<<endl;
    }
    nowy->pesel = proba;
    cout << "wpisz adres gamil: ";
    cin >> nowy->adres_gmail;
    if (miejsce_nowej==true) // jesli prawda, nowa bedzie utworzona przed danym elementem
    {
        if (aktualny == pierwsza)
        {
            aktualny->poprzednia = nowy;
            nowy->nastepna = aktualny;
            nowy->poprzednia = NULL;
            pierwsza = nowy;
        }
        else
        {
            nowy->nastepna = aktualny;
            aktualny->poprzednia->nastepna = nowy;
            nowy->poprzednia = aktualny->poprzednia;
            aktualny->poprzednia = nowy;
        }
    }
    else
    {
        if (aktualny == ostatnia)
        {
            aktualny->nastepna = nowy;
            nowy->poprzednia = aktualny;
            nowy->nastepna = NULL;
            ostatnia = nowy;
        }
        else
        {
            nowy->poprzednia = aktualny;
            aktualny->nastepna->poprzednia = nowy;
            nowy->nastepna = aktualny->nastepna;
            aktualny->nastepna= nowy;
        }
    }
}
void USUN(osoba *usun)
{
    cout << "na pewno usunac dany element?"<<endl;
    cout << "<wcisnij Y lub N>"<<endl;
    switch (getch())
    {
    case 'y':
    case 'Y':
        {
            if (pierwsza==ostatnia)
            {
                pierwsza = NULL;
                ostatnia = NULL;
            }
            else if (usun==pierwsza)
            {
                usun->nastepna->poprzednia=NULL;
                pierwsza=usun->nastepna;
            }
            else if (usun==ostatnia)
            {
                usun->poprzednia->nastepna=NULL;
                ostatnia=usun->poprzednia;
            }
            else
            {
                usun->poprzednia->nastepna=usun->nastepna;
                usun->nastepna->poprzednia=usun->poprzednia;
            }
            delete usun;
        }break;
    default: break;
    }
}
void ZMIANA_POLOZENIA(osoba *polozenie)
{
    int nowe_polozeniee = pierwsza->numer_porzadkowy;
    bool wybrano = false;
    do
    {
        system("cls");
        cout << "   WYBRANY ELEMENT ZNAJDZIE SIE ";
        if (nowe_polozeniee==ostatnia->numer_porzadkowy+1)
            cout << "PO ELEMENCIE NUMER: "<< nowe_polozeniee-1<<endl;
        else
            cout << "PRZED ELEMENTEM NUMER: "<< nowe_polozeniee<<endl;
        cout << "1. zatwierdz nowe polozenie (element znajdzie siê PRZED AKTUALNYM elementem)"<<endl
             << "A. przesun sie o jeden element wczesniej"<<endl
             << "D. przesun sie o jeden element do przodu"<<endl
             << "J. przeskocz do elementu o podanym numerze"<<endl;
        switch (getch())
        {
        case '1':
            {
                wybrano = true;
            }break;
        case 'A':
        case 'a':
            {
                if (nowe_polozeniee-1<pierwsza->numer_porzadkowy)
                {
                    cout << "OPERACJA NIEDOZWOLONA. ELEMENT NIE ISTNIEJE"<<endl;
                    Sleep(500);
                }
                else nowe_polozeniee--;
            }break;
        case 'D':
        case 'd':
            {
                if (nowe_polozeniee+1==ostatnia->numer_porzadkowy+1)
                nowe_polozeniee++;
                else if (nowe_polozeniee>ostatnia->numer_porzadkowy)
                {
                    cout << "OPERACJA NIEDOZWOLONA. ELEMENT NIE ISTNIEJE"<<endl;
                    Sleep(500);
                }
                else nowe_polozeniee++;
            }break;
        case 'J':
        case 'j':
            {
                cout << "wpisz numer elementu obok: "<<endl;
                int liczba;
                cin >> liczba;
                if ((liczba<1)||(liczba>ostatnia->numer_porzadkowy))
                {
                    cout << "OPERACJA NIEDOZWOLONA. ELEMENT NIE ISTNIEJE"<<endl;
                    Sleep(500);
                }
                else nowe_polozeniee = liczba;
            }break;
        }
    }while (wybrano == false);
    osoba * przed_niego;
    bool SZCZEGOLNY_PRZYPADEK;
    if (nowe_polozeniee>ostatnia->numer_porzadkowy)
    {
        SZCZEGOLNY_PRZYPADEK = true;
        nowe_polozeniee--;
    }
    else
        SZCZEGOLNY_PRZYPADEK = false;
    if (pierwsza->numer_porzadkowy+nowe_polozeniee<ostatnia->numer_porzadkowy-nowe_polozeniee)
    {
       przed_niego = ZNAJDZ (nowe_polozeniee,pierwsza,true);
    }
    else
    {
       przed_niego = ZNAJDZ (nowe_polozeniee,ostatnia,false);
    }
    // // // kod zmiany polozenia // // // //
    if (polozenie == ostatnia)
    {
        ostatnia = polozenie->poprzednia;
        ostatnia->nastepna = NULL;
    }
    else if (polozenie == pierwsza)
    {
        pierwsza = polozenie->nastepna;
        pierwsza->poprzednia = NULL;
    }
    else
    {
        polozenie->poprzednia->nastepna = polozenie->nastepna;
        polozenie->nastepna->poprzednia = polozenie->poprzednia;
    }



    if (przed_niego==pierwsza)
    {
        polozenie->poprzednia=przed_niego->poprzednia;
        przed_niego->poprzednia=polozenie;
        polozenie->nastepna=przed_niego;
        pierwsza=polozenie;
    }
    else if (SZCZEGOLNY_PRZYPADEK == true)
    {
        polozenie->nastepna=przed_niego->nastepna;
        przed_niego->nastepna=polozenie;
        polozenie->poprzednia=przed_niego;
        ostatnia=polozenie;
    }
    else
    {
        polozenie->nastepna = przed_niego;
        polozenie->poprzednia = przed_niego->poprzednia;
        przed_niego->poprzednia->nastepna = polozenie;
        przed_niego->poprzednia = polozenie;
    }
}
osoba* ZNAJDZ (int numer, osoba* do_sprawdzenia, bool od_przodu)
{
    if (numer == do_sprawdzenia->numer_porzadkowy)
    {
        return do_sprawdzenia;
    }
    else if (od_przodu == true) // kod bedzie szukac od przodu
    {
        do_sprawdzenia = do_sprawdzenia->nastepna;
        ZNAJDZ (numer,do_sprawdzenia,true);
    }
    else if (od_przodu == false) // kod bedzie szukac od tylu
    {
        do_sprawdzenia = do_sprawdzenia->poprzednia;
        ZNAJDZ (numer,do_sprawdzenia,false);
    }
}
osoba* PRZESUN (char dalej, osoba *przesun)
{
	if ((dalej=='A')||(dalej=='a'))
	{
		if (przesun->poprzednia!=NULL)
            przesun = przesun->poprzednia;
		else
			cout << "nie mozna wykonac przeskoku. element nie istnieje"<<endl;
	}
	else if ((dalej=='D')||(dalej=='d'))
	{
		if (przesun->nastepna!=NULL)
            przesun = przesun->nastepna;
		else
			cout << "nie mozna wykonac przeskoku. element nie istnieje"<<endl;
	}
	 return przesun;
}
void NOWY_PARAMETR(osoba *zmiana,char wybor)
{
    system("cls");
    string nowy_parameter;
    switch(wybor)
    {
    case '1':
        {
            cout << "aktualne imie : "<<zmiana->imie<<endl;
            cout << "wpisz nowe obok :";
            cin >> nowy_parameter;
            zmiana->imie = nowy_parameter;
        }break;
    case '2':
        {
            cout << "aktualne nazwisko : "<<zmiana->nazwisko<<endl;
            cout << "wpisz nowe obok :";
            cin >> nowy_parameter;
            zmiana->nazwisko = nowy_parameter;
        }break;
    case '3':
        {
            cout << "aktualny adres e-mail : "<<zmiana->adres_gmail<<endl;
            cout << "wpisz nowe obok :";
            cin >> nowy_parameter;
            zmiana->adres_gmail = nowy_parameter;
        }break;
    case '4':
        {
            cout << "aktualny numer telefonu : "<<zmiana->telefon<<endl;
            cout << "wpisz nowe obok :";
            cin >> nowy_parameter;
            if (WYKRYJ_NIELICZBE(nowy_parameter)==false)
                {
                    nowy_parameter = "do uzupelnienia";
                    cout << "wprowadzono bledne dane. uzupelnij rubryke pozniej"<<endl;
                }
            zmiana->telefon = nowy_parameter;
        }break;
    case '5':
        {
            cout << "aktualny PESEL : "<<zmiana->pesel<<endl;
            cout << "wpisz nowe obok :";
            cin >> nowy_parameter;
            if (WYKRYJ_NIELICZBE(nowy_parameter)==false)
                {
                    nowy_parameter = "do uzupelnienia";
                    cout << "wprowadzono bledne dane. uzupelnij rubryke pozniej"<<endl;
                }
            zmiana->pesel = nowy_parameter;
        }break;
    default:
        {
            cout << "wybrano zly parametr, powrot do glownego menu"<<endl;
        }break;
    }
    Sleep (500);
}
int SZUKAJ(osoba *szukaj, char parametr, string fraza, int licznik, int suma)
{
    string do_porownania;
    if (szukaj!=NULL)
    {
        switch (parametr)
        {
        case '1':   do_porownania = szukaj->imie;   break;
        case '2':   do_porownania = szukaj->nazwisko;   break;
        case '3':   do_porownania = szukaj->adres_gmail;    break;
        case '4':   do_porownania = szukaj->telefon;    break;
        case '5':   do_porownania = szukaj->pesel;  break;
        default :   do_porownania = ":::BLAD:::";   break;
        }
        if (do_porownania != ":::BLAD:::")
        {
            if (do_porownania == fraza)
            {
                POKASZ_ELEMENT(szukaj);
                licznik++;
                suma++;
                if (licznik>5)
                {
                    system("pause");
                    system("cls");
                    licznik = 1;
                }
            }
            SZUKAJ(szukaj->nastepna,parametr,fraza,licznik,suma);
        }
    }
    return suma;
}
void ZAPISZ ()
{
    cout << "--------------------------------------------------" <<endl;
    cout << "chcesz zapisac do nowego pliku, czy nadpisac dane?" <<endl
        << "1. zapisz do nowego"<<endl;
    if (nazwa_pliku == "::NIE_WYBRANO::")
    cout << "NIE WYBRANO WCZESNIEJ PLIKU, DANE NIE MOGA BYC NADPISANE"<<endl;
    else
    cout << "2. nadpisz dane do pliku " << nazwa_pliku << endl;
    fstream plik;
    switch (getch())
    {
    case '1':
        {
            cin.ignore();
            cout << "podaj nazwe pliku: ";
            string nazwa;
            getline(cin,nazwa);
            plik.open((nazwa + ".txt").c_str(),ios::out);
            cout << "chcesz ustawic haslo do tego pliku? <Y LUB N>"<<endl;
            char wybor;
            wybor = getch();
            if (wybor=='y'||wybor=='Y')
            {
                cout << "wpisz swoje haslo ponizej"<<endl;
                string haslo;
                cin >> haslo;
                plik<<"::HASLO::"<<endl;
                plik<<haslo<<endl;
            }
            osoba *zapisz = pierwsza;
            plik<<"::LICZBA::"<<endl;
            plik<<ostatnia->numer_porzadkowy<<endl;
            for (int i = 1;i<=ostatnia->numer_porzadkowy;i++)
            {
                plik<<zapisz->imie<<endl;
                plik<<zapisz->nazwisko<<endl;
                plik<<zapisz->telefon<<endl;
                plik<<zapisz->adres_gmail<<endl;
                plik<<zapisz->pesel<<endl;
                zapisz = zapisz->nastepna;
            }
            plik.close();
            plik.open("%%KONTROLA%%PLIKOW%%.txt",ios::out|ios::app);
            plik<<endl<<nazwa<<".txt"<<endl;
            plik.close();
        }break;
    case '2':
        {
            if (nazwa_pliku == "::NIE_WYBRANO::")
            cout << "OPCJA NIEDOZWOLONA"<<endl;
            else
            {
                plik.open(nazwa_pliku.c_str(),ios::in);
                string linia;
                string haslo;
                bool odblokowano = true;
                getline(plik,linia);
                if (linia=="::HASLO::")
                {
                    odblokowano = false;
                    getline(plik,linia);
                    cout << "plik zabezpieczony. podaj haslo"<<endl;
                    for (int i = 0;i<3;i++)
                    {
                        cin >> haslo;
                        if (haslo == linia)
                        {
                            odblokowano = true;
                            break;
                        }
                        else
                            cout << "zle haslo. sproboj ponownie"<<endl;
                    }
                }
                if (odblokowano == true) // <--------------------- DO SKONCZENIA
                {
                    plik.close();
                    plik.open(nazwa_pliku.c_str(),ios::out);
                    if (linia != "::LICZBA::")
                    {
                        plik<<"::HASLO::"<<endl;
                        plik<<linia<<endl;
                    }
                    osoba *zapisz = pierwsza;
                    plik<<"::LICZBA::"<<endl;
                    plik<<ostatnia->numer_porzadkowy<<endl;
                    for (int i = 1;i<=ostatnia->numer_porzadkowy;i++)
                    {
                        plik<<zapisz->imie<<endl;
                        plik<<zapisz->nazwisko<<endl;
                        plik<<zapisz->telefon<<endl;
                        plik<<zapisz->adres_gmail<<endl;
                        plik<<zapisz->pesel<<endl;
                        zapisz = zapisz->nastepna;
                    }
                    plik.close();
                }
            }
        }
    }
}
void NUMERUJ (osoba *numeracja,int jeden)
{
    if (numeracja !=NULL)
    {
        numeracja->numer_porzadkowy = jeden;
        Sleep(500);
        NUMERUJ (numeracja->nastepna,++jeden);
    }
}
