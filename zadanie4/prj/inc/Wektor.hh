#ifndef WEKTOR_HH
#define WEKTOR_HH

#include <iostream>
#include <cassert>
#include <initializer_list>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

/*!
 * \file
 * \brief Definicja szablonu Wektor<>
 *
 * Plik zawiera definicję szablonu Wektor<>.
 */

/*!
 * \brief Modeluje pojecie szablonu wektora.
 * 
 *  Szablon modeluje klase wektor.
 *  Jej atrybutem jest tablica opisujaca wymiary wektora.  
 */
template <typename Typ, int Rozmiar>
class Wektor {

    /*!
     * \brief Tablica z rozmiarem wektora.
     */
    Typ Wsp[Rozmiar];

  public:

    Wektor();
    Wektor(const initializer_list<Typ> &rListaWsp);
    Wektor<Typ,Rozmiar>  operator + (Wektor<Typ,Rozmiar> Arg);
    Wektor<Typ,Rozmiar>  operator - (Typ Arg);
    Wektor<Typ,Rozmiar> &operator *= (Typ Mnoznik);
    Wektor<Typ,Rozmiar>  operator * (Typ Mnoznik) const;
    /*!
     * \brief Funktor wektora.
     *
     * \param[in] Ind - indeks wektora.
     * 
     * \return Zwraca wartosc wektora w danym miejscu tablicy.
      */
    Typ  operator [] (int Ind) const { assert(Ind < Rozmiar); return Wsp[Ind]; };
    /*!
     * \brief Funktor wektora.
     *
     * \param[in] Ind - indeks wektora.
     * 
     * \return Zwraca wartosc wektora w danym miejscu tablicy jako stala.
      */
    Typ &operator [] (int Ind) { assert(Ind < Rozmiar); return Wsp[Ind]; };  
    double DlugoscBoku(const Wektor<Typ,Rozmiar> &arg1, const Wektor<Typ,Rozmiar> &arg2);

};

/*!
 * \brief Konstruktor klasy Wektor.
 */
template <typename Typ, int Rozmiar>
Wektor<Typ,Rozmiar>::Wektor()
{
  for (Typ &rWsp_i : Wsp)  rWsp_i = 0;  
}

/*!
 * \brief Konstruktor klasy Wektor.
 *
 * \param[in] rListaWsp - lista z rozmiarem wektora.
 * 
 */
template <typename Typ, int Rozmiar>
Wektor<Typ,Rozmiar>::Wektor(const initializer_list<Typ> &rListaWsp):Wektor()
{
  assert(rListaWsp.size() <= Rozmiar);
  int Ind = -1;
  for (double Wsp_i : rListaWsp) Wsp[++Ind] = Wsp_i;
}

/*!
 * \brief Realizuje dodawanie dwóch wektorów.
 *
 * \param[in] Arg - drugi skladnik dodawania.
 * 
 * \return Zwraca wynik dodawania dwoch wektorow. 
 */
template <typename Typ, int Rozmiar>
Wektor<Typ,Rozmiar> Wektor<Typ,Rozmiar>::operator + (Wektor<Typ,Rozmiar> Arg)
{
  Wektor<Typ,Rozmiar> Wynik;

    for(int Ind=0; Ind < Rozmiar; ++Ind){
        Wynik[Ind] = Wsp[Ind] + Arg[Ind];
    }
    return Wynik;
}

/*!
 * \brief Realizuje odejmowanie dwóch wektorów.
 *
 * \param[in] Arg - drugi skladnik odejmowania.
 * 
 * \return Zwraca wynik odejmowania dwoch wektorow. 
 */
template <typename Typ, int Rozmiar>
Wektor<Typ,Rozmiar> Wektor<Typ,Rozmiar>::operator - (Typ Arg)
{
  Wektor<Typ,Rozmiar> Wynik;

    for(int Ind=0; Ind < Rozmiar; ++Ind){
        Wynik[Ind] = Wsp[Ind] - Arg[Ind];
    }
    return Wynik;
}

/*!
 * \brief Przeciazenie operatora mnozenia i porownania wartosci.
 *
 * \param[in] Mnoznik - argument przez ktory bedziemy mnozyc.
 * 
 * \return Zwraca wynik mnozenia wektora przez liczbe. 
 */
template <typename Typ, int Rozmiar>
Wektor<Typ,Rozmiar> & Wektor<Typ,Rozmiar>::operator *= (Typ Mnoznik)
{
  for (Typ &rWsp_i : Wsp)  rWsp_i *= Mnoznik;
  return *this;
}

/*!
 * \brief Przeciazenie operatora mnozenia.
 *
 * \param[in] Mnoznik - argument przez ktory bedziemy mnozyc.
 * 
 * \return Zwraca wynik mnozenia wektora przez liczbe. 
 */
template <typename Typ, int Rozmiar>
Wektor<Typ,Rozmiar> Wektor<Typ,Rozmiar>::operator * (Typ Mnoznik) const
{
  Wektor<Typ,Rozmiar> Iloraz = *this;                         
  return Iloraz *= Mnoznik;
}


/*!
 * \brief Przeciążenie operatora wczytywania.
 *
 *  Realizuje wczytywanie wierzcholkow figury z pliku.
 * 
 * \param[in] Sin - strumien wejsciowy.
 * \param[in] Wek - wektor
 * 
 * \return Zwraca referencje do strumienia wejsciowego.
 */
template <typename Typ, int Rozmiar>
inline
istream& operator >> (istream &Sin, Wektor<Typ,Rozmiar> &Wek)
{
  for (int Ind=0; Ind < Rozmiar; ++Ind)
  {
     Sin >> Wek[Ind]; 
  }
  cout << endl;
  return Sin;
}

/*!
 * \brief Przeciążenie operatora wyswietlania.
 *
 *  Realizuje wyswietlanie wierzcholkow figury zapisanych w pliku.
 * 
 * \param[in] Sout - strumien wyjsciowy.
 * \param[in] Wek - wektor
 * 
 * \return Zwraca referencje do strumienia wyjsciowego.
 */
template <typename Typ, int Rozmiar>
inline
ostream& operator << (ostream &Sout, const Wektor<Typ,Rozmiar> &Wek)
{
  for (int Ind = 0; Ind < Rozmiar; ++Ind)
  {  
     Sout << setw(16) << fixed << setprecision(10) << Wek[Ind] << "  ";
  }
  return Sout;  
}

/*!
 * \brief Funkcja liczaca dlugosc boku prostopadloscianu.
 *
 * \param[in] arg1 - pierwszy wektor.
 * \param[in] arg2 - drugi wektor.
 * \param[in] arg3 - trzeci wektor.
 * 
 * \return Odleglosc dwoch wierzcholkow prostopadloscianu.
 */
template <typename Typ, int Rozmiar>
double DlugoscBoku(const Wektor<Typ,Rozmiar> &arg1, const Wektor<Typ,Rozmiar> &arg2){

    double dlugosc, RoznicaX, RoznicaY, RoznicaZ;
    RoznicaX = arg1[0] - arg2[0];
    RoznicaY = arg1[1] - arg2[1];
    RoznicaZ = arg1[2] - arg2[2];

    return dlugosc = sqrt(pow(RoznicaX,2) + pow(RoznicaY,2) + pow(RoznicaZ,2));
}

#endif
