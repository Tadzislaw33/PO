#ifndef MACIERZ2X2_HH
#define MACIERZ2X2_HH

#include "Wektor2D.hh"
#include <cstdlib>

#define ROZMIAR_MAC  2

/*
 *  Klasa modeluje pojecie dwuwymiarowej macierzy.
 *  Zawiera:
 *    Pole prywatne:
 *      Tablice opisujaca wymiary macierzy 
 *    Pole publiczne:  
 *      Konstruktory tej klasy
 *      Przeciazenia odpowiednich operatorow dzialan 
 *      Funktory macierzy
 *      Metode opisujaca macierz rotacji
 */
class Macierz2x2 {

    double Tab[ROZMIAR_MAC][ROZMIAR_MAC];

  public:

    Macierz2x2();
    Macierz2x2(double [ROZMIAR_MAC][ROZMIAR_MAC]);
    Wektor2D operator * (Wektor2D arg2);
    Macierz2x2 operator + (Macierz2x2 arg2);
    const double &operator () (int x, int y) const;
    double &operator () (int x, int y);   
    void MacierzRotacji(double Kat);
};

ostream &operator << (ostream &Sout, const Macierz2x2 &Mac);

#endif
