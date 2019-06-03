#include <iostream>
#include "konwerter.h"

using namespace std;

bool WYKRYJ_NIELICZBE(string liczba)
{
    int dlugosc = liczba.size();
    for (int i=0;i<dlugosc;i++)
    {
        switch (liczba[i])
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
        case '0':
            {
                continue;
            }break;
        default:
            {
                return false;
            }
        }
    }
    return true;

}
