#ifndef WEKTOR2D_HH
#define WEKTOR2D_HH

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;
#define ROZMIAR_WEKTORA   2

/*
 *  Klasa modeluje pojecie dwuwymiarowego wektora.
 *  Zawiera:
 *    Pole prywatne:
 *      Tablice opisujaca wymiary wektora  
 *    Pole publiczne:  
 *      Konstruktory tej klasy
 *      Przeciazenia odpowiednich operatorow dzialan 
 *      Funktory wektora 
 */
class Wektor2D {

    double Wsp[ROZMIAR_WEKTORA];
    
  public:
  
    Wektor2D();
    Wektor2D(double [ROZMIAR_WEKTORA]);
    Wektor2D  operator + (const Wektor2D &arg2);
    Wektor2D  operator - (const Wektor2D &arg2);
    Wektor2D  operator * (const double &tmp);
    const double &operator [] (int Ind) const;
    double &operator [] (int Ind);
};

double DlugoscBoku(const Wektor2D &arg1, const Wektor2D &arg2);
ostream& operator << (ostream &Sout, const Wektor2D &Wek);
istream& operator >> (istream &Sin, Wektor2D &Wek);

#endif
