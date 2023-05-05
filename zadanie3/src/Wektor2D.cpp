#include "Wektor2D.hh"

/*
 *  Konstruktor klasy Wektor2D.
 *  Argumenty:
 *      Brak argumentów.
 *  Zwraca:
 *      Tablica wypelniona wartosciami 0.
 */
Wektor2D::Wektor2D(){

    for(int i=0; i < ROZMIAR_WEKTORA; ++i){
        Wsp[i] = 0;
    }
}

/*
 *  Konstruktor klasy Wektor2D.
 *  Argumenty:
 *      tmp - Jednowymiarowa tablica typu double.
 *  Zwraca:
 *      Tablica wypelniona wartosciami podanymi w argumencie.
 */
Wektor2D::Wektor2D(double tmp[ROZMIAR_WEKTORA]){

    for(int i=0; i < ROZMIAR_WEKTORA; ++i){
        Wsp[i] = tmp[i];
    }
}

/*
 *  Realizuje dodawanie dwóch wektorów.
 *  Argumenty:
 *      arg2 - Drugi składnik dodawania.
 *  Zwraca:
 *      Sume dwoch skladnikow przekazanych jako wskaznik na parametr.
 */
Wektor2D Wektor2D::operator + (const Wektor2D &arg2){

    Wektor2D Wynik;

    for(int i=0; i < ROZMIAR_WEKTORA; ++i){
        Wynik[i] = Wsp[i] + arg2[i];
    }
    return Wynik;
}

/*
 *  Realizuje odejmowanie dwóch wektorów.
 *  Argumenty:
 *      arg2 - Drugi składnik odejmowania.
 *  Zwraca:
 *      Roznice dwoch skladnikow przekazanych jako wskaznik na parametr.
 */
Wektor2D Wektor2D::operator - (const Wektor2D &arg2){

    Wektor2D Wynik;

    for(int i=0; i < ROZMIAR_WEKTORA; ++i){
        Wynik[i] = Wsp[i] - arg2[i];
    }
    return Wynik;
}

/*
 *  Realizuje mnozenie dwóch wektorów.
 *  Argumenty:
 *      arg2 - Drugi składnik mnozenia.
 *  Zwraca:
 *      Iloczyn dwoch skladnikow przekazanych jako wskaznik na parametr.
 */
Wektor2D Wektor2D::operator * (const double &tmp){

    Wektor2D Wynik;

    for(int i=0; i < ROZMIAR_WEKTORA; ++i){
        Wynik[i] = Wsp[i] * tmp;
    }
    return Wynik;
}

/*
 *  Funktor wektora.
 *  Argumenty:
 *      Ind - indeks wektora.
 *  Zwraca:
 *      Wartosc wektora w danym miejscu tablicy jako stala.
 */
const double &Wektor2D::operator [] (int Ind) const{

    if(Ind<0 || Ind>=ROZMIAR_WEKTORA){
        cerr << "Blad: Wektor jest poza zasiegiem.\n"; 
    }
    return Wsp[Ind];
}

/*
 *  Funktor wektora.
 *  Argumenty:
 *      Ind - indeks wektora.
 *  Zwraca:
 *      Wartosc wektora w danym miejscu tablicy.
 */
double &Wektor2D::operator [] (int Ind){

    if(Ind<0 || Ind>=ROZMIAR_WEKTORA){
        cerr << "Blad: Wektor jest poza zasiegiem.\n"; 
    }
    return Wsp[Ind];
}

/*
 *  Funkcja liczaca dlugosc boku prostokata.
 *  Argumenty:
 *      arg1 - pierwszy wektor.
 *      arg2 - drugi wektor.
 *  Zwraca:
 *      odleglosc dwoch wierzcholkow prostokata.
 */
double DlugoscBoku(const Wektor2D &arg1, const Wektor2D &arg2){

    double dlugosc, RoznicaX, RoznicaY;
    RoznicaX = arg1[0] - arg2[0];
    RoznicaY = arg1[1] - arg2[1];
    return dlugosc = sqrt(pow(RoznicaX,2) + pow(RoznicaY,2));
}

/*
 *  Przeciazenie operatora przesuniecia bitowego w lewo.
 *  Argumenty:
 *      Sout - strumien wejsciowy.
 *      Wek - wektor. 
 */
ostream& operator << (ostream &Sout, const Wektor2D &Wek){

    for (int i=0; i < ROZMIAR_WEKTORA; ++i)
    {
        Sout << setw(16) << fixed << setprecision(10) << Wek[i] << "   "; 
    }
    return Sout;
}

/*
 *  Przeciazenie operatora przesuniecia bitowego w prawo.
 *  Argumenty:
 *      Sin - strumien wyjsciowy.
 *      Wek - wektor. 
 */
istream& operator >> (istream &Sin, Wektor2D &Wek){

    for (int i=0; i < ROZMIAR_WEKTORA; ++i)
    {
        Sin >> Wek[i]; 
    }
    cout << endl;
    return Sin;
}

