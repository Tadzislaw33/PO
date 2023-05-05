#ifndef GRANIASTOSLUP6_HH
#define GRANIASTOSLUP6_HH

#include "BrylaGeometryczna.hh"
#define LICZBA_WIERZCHOLKOW_G 24

class Graniastoslup6: public BrylaGeometryczna {

    Wektor3D Polozenie;
    double KatOrientacji_stopnie;
    Wektor3D Wierzcholek[LICZBA_WIERZCHOLKOW_G];

  public:

    Graniastoslup6();
    Graniastoslup6(Wektor3D Polozenie, double KatOrientacji_stopnie, string NazwaBryly);
    Wektor3D operator [] (int Ind) const { return Wierzcholek[Ind];}
    Wektor3D &operator [] (int Ind) {return Wierzcholek[Ind];}
    const Wektor3D TransfDoUklWsprodzica(Wektor3D &Wsp);      
    Graniastoslup6& Obrot(double Kat);
    Graniastoslup6& Translacja(Wektor3D &Wek);

}; 

ostream& operator << ( ostream &Sout, const Graniastoslup6 &Gr);

#endif 