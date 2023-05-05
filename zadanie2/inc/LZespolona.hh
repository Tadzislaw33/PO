#ifndef LZESPOLONA_HH
#define LZESPOLONA_HH

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <fstream>

using namespace std;

/*!
 * Modeluje pojecie liczby zespolonej
 */
struct  LZespolona {
  double   re;    /*! Pole repezentuje czesc rzeczywista. */
  double   im;    /*! Pole repezentuje czesc urojona. */

  LZespolona  operator + (LZespolona Skl2);
  LZespolona  operator - (LZespolona Skl2);
  LZespolona  operator * (LZespolona Skl2);
  LZespolona  operator / (LZespolona Skl2);
  bool  operator == (LZespolona Skl2);
  LZespolona Sprzezenie();
  double Modul2();

};

ostream& operator << ( ostream& sout, LZespolona lzesp); 
istream& operator >> ( istream& sin, LZespolona& lzesp);

// += referencja do pierwszego argumentu  
LZespolona &operator += (LZespolona &Skl1, LZespolona &Skl2);
LZespolona &operator *= (LZespolona &Skl1, LZespolona &Skl2);

#endif
