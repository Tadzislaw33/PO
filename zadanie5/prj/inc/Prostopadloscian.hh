#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH

#include "BrylaGeometryczna.hh"
#define LICZBA_WIERZCHOLKOW 16

class Prostopadloscian: public BrylaGeometryczna {

    Wektor3D Wierzcholek[LICZBA_WIERZCHOLKOW];
    Wektor3D Polozenie;
    double KatOrientacji_stopnie;

  public:

    Prostopadloscian();
    Prostopadloscian(Wektor3D Polozenie, double KatOrientacji_stopnie, string NazwaBryly);
    Wektor3D operator [] (int Ind) const { return Wierzcholek[Ind];}
    Wektor3D &operator [] (int Ind) {return Wierzcholek[Ind];}
    const Wektor3D TransfDoUklWsprodzica(Wektor3D &Wsp);      
    Prostopadloscian& Obrot(double Kat);
    Prostopadloscian& Translacja(Wektor3D &Wek);
}; 

ostream& operator << ( ostream &Sout, const Prostopadloscian &Pr);

#endif 