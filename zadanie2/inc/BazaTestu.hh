#ifndef BAZATESTU_HH
#define BAZATESTU_HH

#include "WyrazenieZesp.hh"

/*
 * Modeluje pojecie bazy testu z zestawem pytan w tablicy
 * oraz informacji o maksymalnej ilosci pytan, jak
 * tez indeksem nastepnego pytania, ktore ma byc pobrane
 * z bazy.
 */
struct BazaTestu {
  WyrazenieZesp   wskTabTestu[4];   /* Wskaznik na tablice zawierajaca pytania testu */
  unsigned int    IloscPytan;    /* Ilosc wszystkich pytan */
  unsigned int    IndeksPytania; /* Numer pytania, ktore ma byc pobrane jako nastepne */

  void UstawTest(WyrazenieZesp *wskTabTestu, unsigned int IloscPytan, const char*  sNazwaTestu );
  bool InicjalizujTest(const char*  sNazwaTestu ); // Inicjalizuje test powiazany z dana nazwa.
  bool PobierzNastpnePytanie(WyrazenieZesp *wskWyr ); //Udostepnia nastepne pytanie z bazy.
};

#endif
