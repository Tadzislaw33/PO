#include "WyrazenieZesp.hh"

using namespace std;

/*
 *  Przeciazenie operatora << do wyswietlania operatora dzialania.
 */
ostream& operator << ( ostream &sout, Operator &Op){

    switch (Op)
    {
        case Op_Dodaj:      sout << '+';     break;
        case Op_Odejmij:    sout << '-';     break;
        case Op_Mnoz:       sout << '*';     break;
        case Op_Dziel:      sout << '/';     break;
    }
    return sout;
}

/*
 *  Przeciazenie operatora >> do wczytywania operatora dzialania.
 */
istream& operator >> ( istream& sin, Operator& Op){

    Operator Tabznak[] = { Op_Dodaj, Op_Odejmij, Op_Mnoz, Op_Dziel };
    const char Tabsymbol[] = "+-*/", *wSymOp;
    char CzytSymOp = 'x';

    sin >> CzytSymOp;
    if ( (wSymOp = strchr(Tabsymbol,CzytSymOp)) == nullptr) { 
      sin.setstate(ios::failbit); 
    }
    else Op = Tabznak[wSymOp-Tabsymbol];
    
    return sin;
}

/*!
 * Przeciazenie operatora << do wyswietlania wyrazenia zespolonego.
 * Argumenty:
 *    sout - referencja do obiektu ostream,
 *    WyrZ - wyrazenie zespolone.
 * Zwraca:
 *    referencja do strumienia wyjsciowego(wyswietla WyrZ w zadanym formacie).
 */
ostream& operator << ( ostream &sout, WyrazenieZesp &WyrZ){

    sout << WyrZ.Arg1 << " " << WyrZ.Op << " " << WyrZ.Arg2;
    
    return sout;
} 

/*!
 * Przeciazenie operatora >> do wczytywania wyrazenia zespolonego.
 * Argumenty:
 *    sin - referencja do obiektu istream,
 *    WyrZ - referencja do wyrazenia zespolonego.
 * Zwraca:
 *    referencja do strumienia wejsciowego(wczytuje WyrZ w zadanym formacie).
 */
istream& operator >> ( istream &sin, WyrazenieZesp &WyrZ){

    sin >> WyrZ.Arg1;
    if(sin.fail()) return sin;

    sin >> WyrZ.Op;
    if(sin.fail()) return sin;

    sin >> WyrZ.Arg2;
    if(sin.fail()) return sin;

    return sin;
}

/*!
 * Oblicza wartosc wyrazenia zespolonego.
 * Argumenty:
 *    WyrZ - Wyrazenie zespolone.
 * Zwraca:
 *    Wynik dzialania w postaci liczby zespolonej.
 */
LZespolona WyrazenieZesp::Oblicz(){

    LZespolona Wynik;

    switch (Op)
    {
        case Op_Dodaj:      Wynik = Arg1 + Arg2;        break;
        case Op_Odejmij:    Wynik = Arg1 - Arg2;        break;
        case Op_Mnoz:       Wynik = Arg1 * Arg2;        break;
        case Op_Dziel:   
            try{
                            Wynik = Arg1 / Arg2; 
            }
            catch(exception &e){
                cout << "Nie dziel przez zero\nWyjatek:" << e.what();
            }      
                                                        break;
    } 
    return Wynik;
}
