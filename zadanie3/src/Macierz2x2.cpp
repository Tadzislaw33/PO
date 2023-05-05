#include "Macierz2x2.hh"
#include "Wektor2D.hh"

/*
 *  Konstruktor klasy Macierz2x2.
 *  Argumenty:
 *      Brak argumentów.
 *  Zwraca:
 *      Macierz wypelniona wartosciami 0.
 */
Macierz2x2::Macierz2x2(){

    for(int i=0; i < ROZMIAR_MAC; ++i){
        for(int j=0; j < ROZMIAR_MAC; ++j){
            Tab[i][j] = 0;
        }
    }
}

/*
 *  Konstruktor parametryczny klasy Macierz2x2.
 *  Argumenty:
 *      Tab - dwuwymiarowa tablica z elemetami typu double.
 *  Zwraca:
 *      Macierz wypelniona wartosciami podanymi w argumencie.
 */
Macierz2x2::Macierz2x2(double tmp[ROZMIAR_MAC][ROZMIAR_MAC]){

    for(int i=0; i < ROZMIAR_MAC; ++i){
        for(int j=0; j < ROZMIAR_MAC; ++j){
            Tab[i][j] = tmp[i][j];
        }
    }
}

/*
 *  Realizuje mnozenie macierzy przez wektor.
 *  Argumenty:
 *      arg2 - Drugi składnik mnozenia.
 *  Zwraca:
 *      Iloczyn dwoch skladnikow przekazanych jako wektor.
 */
Wektor2D Macierz2x2::operator * (Wektor2D arg2){

    Wektor2D Wynik;

    for(int i=0; i < ROZMIAR_MAC; ++i){
        for(int j=0; j < ROZMIAR_MAC; ++j){
            Wynik[i] += Tab[i][j] * arg2[j];
        }
    }
    return Wynik;
}

/*
 *  Realizuje dodawanie dwoch macierzy.
 *  Argumenty:
 *      arg2 - Drugi składnik dodawania.
 *  Zwraca:
 *      Suma dwoch skladnikow przekazanych jako macierz.
 */
Macierz2x2 Macierz2x2::operator + (Macierz2x2 arg2){

    Macierz2x2 Wynik;

    for(int i=0; i < ROZMIAR_MAC; ++i){
        for(int j=0; j < ROZMIAR_MAC; ++j){
            Wynik(i,j) = Tab[i][j] + arg2(i,j);
        }
    }
    return Wynik;
}

/*
 *  Funktor macierzy.
 *  Argumenty:
 *      x - numer wiersza.
 *      y - numer kolumny.
 *  Zwraca:
 *      Wartosc macierzy w danym miejscu tablicy jako stala.
 */
const double &Macierz2x2::operator () (int x, int y) const{

    if(x >= ROZMIAR_MAC){
        cerr << "Blad: Macierz jest poza zasiegiem.\n"; 
    }
    if(y >= ROZMIAR_MAC){
        cerr << "Blad: Macierz jest poza zasiegiem.\n"; 
    }
    return Tab[x][y];
}

/*
 *  Funktor macierzy.
 *  Argumenty:
 *      x - numer wiersza.
 *      y - numer kolumny.
 *  Zwraca:
 *      Wartosc macierzy w danym miejscu tablicy.
 */
double &Macierz2x2::operator () (int x, int y){

    if(x >= ROZMIAR_MAC){
        cerr << "Blad: Macierz jest poza zasiegiem.\n"; 
    }
    if(y >= ROZMIAR_MAC){
        cerr << "Blad: Macierz jest poza zasiegiem.\n"; 
    }
    return Tab[x][y];
}

/*
 *  Tworzy macierz rotacji.
 *  Argumenty:
 *      Kat - kat o jaki chcemy obrocic prostokat. 
 */
void Macierz2x2::MacierzRotacji(double Kat){

    Tab[0][0] = cos(Kat*M_PI/180);
    Tab[0][1] = -sin(Kat*M_PI/180);
    Tab[1][0] = sin(Kat*M_PI/180);
    Tab[1][1] = cos(Kat*M_PI/180);
}

/*
 *  Przeciazenie operatora przesuniecia bitowego w lewo.
 *  Argumenty:
 *      Sout - strumien wyjsciowy.
 *      Mac - Macierz. 
 */
ostream &operator << (ostream &Sout, const Macierz2x2 &Mac){

    for(int i=0; i < ROZMIAR_MAC; ++i){
        for(int j=0; j < ROZMIAR_MAC; ++j){
            Sout << " " << Mac(i,j) << "  ";
        }
        cout << endl;
    }
    return Sout;
}
