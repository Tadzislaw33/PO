#include "Statystyka.hh"

using namespace std;

/*
 * Wyswietla statystyki testu.
 * Argumenty:
 *    statTest - poprawne i bledne odpowiedzi.
 * Zwraca:
 *    Wartosci statystyk.
 */
void StatystykaTest::Wyswietl(){

    cout << " Statystyka Testu:\n";
    cout << " Liczba poprawnych odpowiedzi: " << l_poprawnych << endl;
    cout << " Liczba niepoprawnych odpowiedzi: " << l_niepoprawnych << endl;
    cout << " Wynik procentowy poprawnych odpowiedzi: " << Oblicz() << "%" << endl;
}

/*!
 * Oblicza wynik testu.
 * Argumenty:
 *    statTestu - liczba poprawnych i niepoprawnych odpowiedzi.
 * Zwraca:
 *    Liczbe uzyskanych punktow.
 */
double StatystykaTest::Oblicz(){

    double wynik=l_poprawnych*1.0/(l_poprawnych+l_niepoprawnych)*1.0*100;
    
    return wynik;
}

void StatystykaTest::inicjalizuj(){

    l_poprawnych=0;
    l_niepoprawnych=0;  
}

void StatystykaTest::dodaj_poprawna(){

    l_poprawnych++;
}

void StatystykaTest::dodaj_niepoprawna(){

    l_niepoprawnych++;
}
