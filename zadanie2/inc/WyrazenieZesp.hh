#ifndef WYRAZENIEZESP_HH
#define WYRAZENIEZESP_HH

#include "LZespolona.hh"

/*!
 * Modeluje zbior operatorow arytmetycznych.
 */
enum Operator { Op_Dodaj, Op_Odejmij, Op_Mnoz, Op_Dziel };

/*
 * Modeluje pojecie dwuargumentowego wyrazenia zespolonego
 */
struct WyrazenieZesp {
  LZespolona   Arg1;   // Pierwszy argument wyrazenia arytmetycznego
  Operator     Op;     // Opertor wyrazenia arytmetycznego
  LZespolona   Arg2;   // Drugi argument wyrazenia arytmetycznego

  LZespolona Oblicz();
};

ostream& operator << ( ostream &sout, WyrazenieZesp &WyrZ); 
istream& operator >> ( istream &sin, WyrazenieZesp &WyrZ);
ostream& operator << ( ostream &sout, Operator &Op);
istream& operator >> ( istream &sin, Operator &Op);

#endif
