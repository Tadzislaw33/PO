#ifndef PROSTOKAT_HH
#define PROSTOKAT_HH

#include "Wektor2D.hh"

#define LICZBA_WIERZCHOLKOW 4

/*
 *  Klasa modeluje pojecie prostokata.
 *  Zawiera:
 *    Pole prywatne:
 *      Tablice wektorow opisujaca prostokat 
 *    Pole publiczne:   
 *      Funktory prostokata
 *      Metody wykonujaca przsuniecie, rotacje, porownanie, wyswietlenie prostokata
 */
class Prostokat {

    Wektor2D wierzcholki[LICZBA_WIERZCHOLKOW];
    
  public:

    Wektor2D operator [] (int Ind) const { return wierzcholki[Ind];}
    Wektor2D &operator [] (int Ind) {return wierzcholki[Ind];}
    void PrzesunOWektor(const Wektor2D &Wek);
    void Rotacja(const double Kat);
    void CzyRowne();  
    void Wyswietl(const Prostokat &Pr);
};

ostream &operator << (ostream &Sout, const Prostokat &Pr);

#endif
