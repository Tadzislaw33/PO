#ifndef DRON_HH
#define DRON_HH

#include <vector>
#include "Prostopadloscian.hh"
#include "Graniastoslup6.hh"
#include "lacze_do_gnuplota.hh"

class Dron {

    static unsigned int IdDrona;
    Wektor3D Polozenie;
    double KatOrientacji_stopnie;
    Prostopadloscian KorpusDrona;
    Graniastoslup6 RotorDrona[4];
    PzG::LaczeDoGNUPlota Lacze;
    const bool Oblicz_i_Zapisz_WspGlbKorpusu(Prostopadloscian &KorpusDrona);
    const bool Oblicz_i_Zapisz_WspGlbRotora(Graniastoslup6 &RotorDrona);

  public:
    
    Dron();
    Dron(const string &SciezkaDoFolderu, double KatSkretu_stopnie,const Wektor3D &Polozenie);
    bool PlanujPoczatkowaSciezke(double KatSkretu_stopnie, double DlugoscLotu, vector<Wektor3D> &PunktySciezki);
    bool WykonajPionowylot(double DlugoscLotu, PzG::LaczeDoGNUPlota &Lacze);
    bool WykonajPoziomylot(double DlugoscLotu, PzG::LaczeDoGNUPlota &Lacze);  
    const bool Oblicz_i_Zapisz_WspGlbDrona();

  protected:

    const Wektor3D TransfDoUklWsprodzica(const Wektor3D &Wierzcholki); 
}; 

#endif 