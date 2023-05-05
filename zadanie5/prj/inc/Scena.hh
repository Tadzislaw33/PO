#ifndef Scena_HH
#define Scena_HH

#include "BrylaGeometryczna.hh"
#include "lacze_do_gnuplota.hh"
#include "Dron.hh"

class Scena{

    Dron TabDronow[2];
    PzG::LaczeDoGNUPlota Lacze;

  public:

    const Dron &WezAktywnegoDrona();      
    Dron &UzyjAktywnegoDrona();
      
}; 

#endif 