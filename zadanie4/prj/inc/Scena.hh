#ifndef SCENA_HH
#define SCENA_HH

#include <vector>
#include "Macierz3x3.hh"
#include "Prostopadloscian.hh"

/*!
 * \file
 * \brief Definicja klasy Scena.
 *
 * Plik zawiera definicję klasy Rotacja.
 */

/*!
 * \brief Modeluje pojecie klasy Rotacja.
 * 
 *  Modeluje klase Rotacja.
 *  Jej atrybutami sa os oraz kat obrotu Prostopadloscianu.  
 */
class Rotacja {

      char os;
      double kat;

    public:

      Macierz3x3 UstawObrot(char os, double kat);
      Macierz3x3 UstawObrotKoncowy(vector<Rotacja> lista_rotacji);
      void Obrot();
}; 

#endif 

