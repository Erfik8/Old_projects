#include <iostream>

using namespace std;

void SLOWNIE(string kontrola_dziesiatek,int KONTROLA_DLUGOSC_SLOWA,int potega_dziesiatki, char cyfra, bool &byla_dziesiatka)
{
    switch (potega_dziesiatki)
    {
    case 1:
    case 4:
    case 7:
    case 10:
    case 13:
    case 16:
    case 19:
        {
            if (byla_dziesiatka == false)
            {
                switch (cyfra)
                {
                case '1':   cout << "jeden "; break;
                case '2':   cout << "dwa "; break;
                case '3':   cout << "trzy "; break;
                case '4':   cout << "cztery "; break;
                case '5':   cout << "piec "; break;
                case '6':   cout << "szesc "; break;
                case '7':   cout << "siedem "; break;
                case '8':   cout << "osiem "; break;
                case '9':   cout << "dziewiec "; break;
                default: break;
                }
            }
            byla_dziesiatka = false;
            if (kontrola_dziesiatek[(KONTROLA_DLUGOSC_SLOWA-potega_dziesiatki)]!='0'||
                kontrola_dziesiatek[(KONTROLA_DLUGOSC_SLOWA-potega_dziesiatki-1)]!='0'||
                kontrola_dziesiatek[(KONTROLA_DLUGOSC_SLOWA-potega_dziesiatki-2)]!='0')
            {
                switch (potega_dziesiatki)
                {
                    case 4:    cout << "tys. "; break;
                    case 7:    cout << "mln. "; break;
                    case 10:   cout << "mld. "; break;
                    case 13:   cout << "bln. "; break;
                    case 16:   cout << "bld. "; break;
                    case 19:   cout << "trln. ";break;
                    default: break;
                }
            }
        }break;
    case 2:
    case 5:
    case 8:
    case 11:
    case 14:
    case 17:
    case 20:
        {
            switch (cyfra)
                {
                case '1':
                    {
                        byla_dziesiatka = true;
                        switch (kontrola_dziesiatek[(KONTROLA_DLUGOSC_SLOWA-potega_dziesiatki)+1])
                        {
                            case '0':   cout << "dziesiec "; break;
                            case '1':   cout << "jedenascie "; break;
                            case '2':   cout << "dwanascie "; break;
                            case '3':   cout << "trzynascie "; break;
                            case '4':   cout << "czternascie "; break;
                            case '5':   cout << "pietnascie "; break;
                            case '6':   cout << "szesnascie "; break;
                            case '7':   cout << "siedemnascie "; break;
                            case '8':   cout << "osiemnascie "; break;
                            case '9':   cout << "dziewietnascie "; break;
                            default: break;
                        }
                    }break;
                case '2':   cout << "dwadziescia "; break;
                case '3':   cout << "trzydziesci "; break;
                case '4':   cout << "czterdziesci "; break;
                case '5':   cout << "piecdziesiat "; break;
                case '6':   cout << "szescdziesiat "; break;
                case '7':   cout << "siedemdziesiat "; break;
                case '8':   cout << "osiemdziesiat "; break;
                case '9':   cout << "dziewiecdziesiat "; break;
                default: break;
                }
        }break;
    case 3:
    case 6:
    case 9:
    case 12:
    case 15:
    case 18:
    case 21:
        {
            switch (cyfra)
                {
                case '1':   cout << "sto "; break;
                case '2':   cout << "dwiescie "; break;
                case '3':   cout << "trzysta "; break;
                case '4':   cout << "czterysta "; break;
                case '5':   cout << "piecset "; break;
                case '6':   cout << "szescset "; break;
                case '7':   cout << "siedemset "; break;
                case '8':   cout << "osiemset "; break;
                case '9':   cout << "dziewiecset "; break;
                default: break;
                }
        }break;



    }
}

int main ()
{
    int test;
    cin>>test;
    for (int j = 0;j<test;j++)
    {
        string liczba;
        bool wykorzystano = false;
        cin >> liczba;
        int dlugosc = liczba.size();
        for (int i = 0;i <dlugosc;i++)
        {
            SLOWNIE(liczba,dlugosc,dlugosc - i,liczba[i],wykorzystano);
        }
        cout << endl;
    }
}
