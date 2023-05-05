#ifndef PROSTOKAT_HH
#define PROSTOKAT_HH

#include "Macierz3x3.hh"

#define LICZBA_WIERZCHOLKOW 8

/*!
 * \file
 * \brief Definicja klasy Prostopadloscian
 *
 * Plik zawiera definicję klasy Prostopadloscian.
 */

/*!
 * \brief Modeluje pojecie klasy prostopadloscianu.
 * 
 *  Modeluje klase prostopadloscian.
 *  Jej atrybutem jest tablica opisujaca wymiary prostopadloscianu.  
 */
class Prostopadloscian {

    /*!
     * \brief Tablica z rozmiarem prostopadloscianu.
     */
    Wektor3D wierzcholki[LICZBA_WIERZCHOLKOW];
    
  public:

    Wektor3D operator [] (int Ind) const { return wierzcholki[Ind];}
    Wektor3D &operator [] (int Ind) {return wierzcholki[Ind];}
    void PrzesunOWektor(const Wektor3D &Wek);
    void Wyswietl(const Prostopadloscian &Pr);
    void Obrot(Macierz3x3 MacierzRotacji);
    void CzyRowne();
};

ostream& operator << ( ostream &Sout, const Prostopadloscian &Pr);

#endif


