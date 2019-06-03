#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <time.h>

using namespace std;

char poziom, wybor;
int liczba, strzal, przedzialMaksymalny, podejscie, podejscieWartoscPoczatkowa, numerGry=1;
bool wyburPoziomu=false , wygrana=false, ponownaGra=false;


int main() // GRA W WYBÓR LICZBY
{
    cout <<"SELECT THE NUMER"; // DOGODNE MENU
    cout <<endl<<"----------------"<<endl;

    cout <<endl<<"   -------------------------------------------------------------------------";//OMOWIENIE ZASAD GRY
    cout <<endl<<"  |  W tej grze masz za proste zadanie wybranie liczby z danego przedzialu  |";
    cout <<endl<<"  |  liczb w zaleznosci od poziomu trudnosci. aby ci to ulatwic, bedziesz   |";
    cout <<endl<<"  |  miec po kazdym wyborze liczby wskazowke, ktora bedzie mowila, czy      |";
    cout <<endl<<"  |  twoja liczba jest mniejsza lub wieksza od wylosowanej. Po tym bedziesz |";
    cout <<endl<<"  |  mogl ponownie wpisac swoj numer. po kazdej probie pokaze ci sie takze  |";
    cout <<endl<<"  |  komunikat mowiacy o tym, ile zostalo ci podejsc. Jesli zdolasz wygrac, |";
    cout <<endl<<"  |  program powiadomi cie o tym, ze wygrales, poda ilosc wszystkich rozgry-|";
    cout <<endl<<"  |  wek oraz spyta, czy chcesz zagrac ponownie.                            |";
    cout <<endl<<"  |                             POWODZENIA                                  |";
    cout <<endl<<"   -------------------------------------------------------------------------";
    cout <<endl<<
    endl<<"NAJCZESTSZE BLEDY GRY:"<<
    endl<<"----------------------";
    cout <<endl<<"1. Po wpisaniu 'tak' program po powrocie do menu wyswietla dwa razy komunikat"<<
    endl <<      "o blednym znaku, mimo ze nic nie wpisalem. dlaczego?";
    cout <<endl<<endl<<"Bez zbednego tlumaczenia wyjasnie tylko, ze przy tym wyborze wystarczy,a raczej"<<
    endl <<            "MUSI, znalezc sie tylko jedna literka(poprawna oczywiscie). w przeciwnym razie"<<
    endl <<            "program bedzie wyswietlal ten komunikat z iloscia zalezna od dlugosci slowa";
    cout <<endl<<endl<<"wcisnij dowolny klawisz!";
    getchar();
    system("cls");

    for(;;) //NIESKONCZONA PETLA DO CZASU KOMENDY EXIT(0)
    {
        wyburPoziomu=false; //1
        wygrana=false;      //2
        ponownaGra=false;   //3
        numerGry=1;         //4 WARTOSC DO ZRESETOWANIA

        cout <<      " WYBIERZ POZIOM TRUDNOSCI:";//WYBÓR POZIOMU TRUDNOSCI GRY
        cout <<endl<<" -------------------------";
        cout <<endl<<"1. LATWY";
        cout <<endl<<"2. SREDNI";
        cout <<endl<<"3. TRUDNY";
        cout <<endl<<endl<<"Aby wybrac, wpisz numer: ";
        cin >>poziom;

        while(wyburPoziomu==false)//PO PRAWIDLOWYM WYBORZE KATEGORII PROGRAM PRZEJDZIE DO GRY. INACZEJ BEDZIE CZEKAL NA POPRAWNE WYBRANIE KATEGORII
        {
            switch(poziom)
            {
            case '1'://POZIOM LATWY
                {
                system("cls");
                cout<<endl<<"wybrana kategoria: LATWY.";
                cout<<endl<<endl<<"przedzial liczbowy od 1 do 25";
                cout<<endl<<endl<<"liczba podejsc do jednej rogrywki: 4";
                przedzialMaksymalny = 25;
                podejscie = 4;
                Sleep(4500);
                wyburPoziomu=true;
                }
            break;
            case '2': //POZIOM SREDNI
                {
                system("cls");
                cout<<endl<<"wybrana kategoria: SREDNI.";
                cout<<endl<<endl<<"przedzial liczbowy od 1 do 100";
                cout<<endl<<endl<<"liczba podejsc do jednej rogrywki: 3";
                przedzialMaksymalny = 100;
                podejscie = 3;
                Sleep(4500);
                wyburPoziomu=true;
                }
            break;
            case '3'://POZIOM TRUDNZ
                {
                system("cls");
                cout<<endl<<"wybrana kategoria: TRUDNY.";
                cout<<endl<<endl<<"przedzial liczbowy od 1 do 250";
                cout<<endl<<endl<<"liczba podejsc do jednej rogrywki: 3";
                przedzialMaksymalny = 250;
                podejscie = 3;
                Sleep(4500);
                wyburPoziomu=true;
                }
            break;
            default://ZADNA WARTOSC Z POWYŻSZYCH (ZLEWPISANIE ZNAKU)
                {
                cout<<endl<<"NIE MA TAKIEJ KATEGORII LUB PODANY ZNAK JEST NIEPRAWIDLOWY. SPROBUJ PONOWNIE: ";
                cin >> poziom;
                }
            break;
            }
        }
        podejscieWartoscPoczatkowa = podejscie;//RESETOWANIE ILOSCI PODEJSC (JEDNA CZESC)
        //ROZPOCZECIE LOSOWANIA
        while(wygrana==false)//SKONCZONE
        {
            podejscie = podejscieWartoscPoczatkowa;//RESETOWANIE ILOSCI PODEJSC(DRUGA CZESC)
            system("cls");
            srand(time(NULL));
            for (int i=1;i<6;i++) liczba = rand()%przedzialMaksymalny + 1;
            cout <<endl<<"ZOSTALA WYLOSOWAN NOWA LICZBA";
            cout <<endl<<"GRA NUMER "<<numerGry;
            cout <<endl<<"wpisz swoja propozycje(UWAZAJ, ABY NIE WPISAC LITER): ";
            cin >> strzal;

            while((podejscie>0)&&(wygrana==false)) //DRUGI WARUNEK DODANY PO TO, ABY ZAPOBIEC BLEDU W POSTACI WYBRANIU POPRAWNEJ LICZBY W OSTATNIEJ PRUBIE(NR 1).
            {
                if (strzal > liczba)
                {
                    cout<<"niestety, twoja liczba jest wieksza od wylosowanej"<<endl;
                    podejscie--;
                    cout<<endl<<"pozostalo prob: "<<podejscie<<endl;
                    Sleep(2000);
                    if(podejscie!=0) cin >>strzal;
                }
                else if (strzal < liczba)
                {
                    cout<<"niestety, twoja liczba jest mniejsza od wylosowanej"<<endl;
                    podejscie--;
                    cout<<endl<<"pozostalo prob: "<<podejscie<<endl;
                    Sleep(2000);
                    if(podejscie!=0) cin >>strzal;
                }
                else wygrana = true;
            }
            if(wygrana==false)
            {
            system("cls");
            cout<<"jesli to widzisz, to oznacza to, ze nie udalo ci sie wygrac w tej grze."<<endl<< "Za chwile rozpocznie sie nastepna ";
            numerGry++;
            Sleep(4000);
            }
        }
        system("cls");
        cout<<"GRATULACJE. UDALO CI SIE WYGRAC!!!";
        cout<<endl<<"ilosc twoich gier: "<<numerGry;
        cout<<endl<<"ilosc twoich prob: "<<numerGry*podejscieWartoscPoczatkowa-(podejscie-1)<<endl;
        getchar(); getchar();
        system("cls");
        cout<<"Chcesz zagrac jeszcze raz?"<<endl;
        cin >>wybor;

        do //PONOWNIE ZAGRANIE LUB WYLACZENIE APLIKACJI
        {
            switch(wybor)
            {
                case'y':case'Y':case't':case'T':
                {
                    system("cls");
                    cout<<"Za chwile wrocisz do menu wyboru...";
                    ponownaGra=true;
                    Sleep(3000);
                    system("cls");
                }
                break;
                case'n':
                case'N':
                {
                    exit(0);
                }
                break;
                default:
                {
                    system("cls");
                    cout<<"NIEPRAWIDLOWA KOMENDA. WPISZ Y<tak> LUB N<nie>";
                    cin>>wybor;
                }
                break;
            }
        }while (ponownaGra==false);

    }
}
