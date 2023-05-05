#ifndef BRYLAGEOMETRYCZNA_HH
#define BRYLAGEOMETRYCZNA_HH

#include "Wektor3D.hh"
#include <fstream>

using namespace std;

class BrylaGeometryczna {

    string NazwaPliku_BrylaWzorcowa;
    string NazwaPliku_BrylaFinalna;
    Wektor3D Skala;

  public:

    const Wektor3D Skaluj(const Wektor3D &Wierzcholki);
    const string &WezNazwePliku_BrylaWzorcowa();
    const string &WezNazwePliku_BrylaFinalna();
}; 

#endif 

