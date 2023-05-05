#include "BrylaGeometryczna.hh"


const Wektor3D BrylaGeometryczna::Skaluj(const Wektor3D &Wierzcholki){

    Wektor3D Wynik;
    Wynik[0] = Wierzcholki[0] * Skala[0];
    Wynik[1] = Wierzcholki[1] * Skala[1];
    Wynik[2] = Wierzcholki[2] * Skala[2];
    return Wynik;
}


const string &BrylaGeometryczna::WezNazwePliku_BrylaWzorcowa(){

    

}


const string &BrylaGeometryczna::WezNazwePliku_BrylaFinalna(){


}