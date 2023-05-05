#ifndef MACIERZ_HH
#define MACIERZ_HH

#include "Wektor3D.hh"

/*!
 * \file
 * \brief Definicja szablonu Macierz<>
 *
 * Plik zawiera definicję szablonu Macierz<>.
 */

/*!
 * \brief Modeluje pojecie szablonu macierzy.
 * 
 *  Szablon modeluje klase macierz.
 *  Jej atrybutem jest tablica opisujaca wymiary macierzy.  
 */
template <typename Typ, int Rozmiar>
class Macierz {

    /*!
     * \brief Tablica z rozmiarem macierzy.
     */
    Typ Tab[Rozmiar][Rozmiar];

  public:

    Macierz();
    Macierz(const initializer_list<Typ> &rListaWsp);
    Macierz<Typ,Rozmiar> UstawObrot(double kat);
    Wektor<Typ,Rozmiar> operator * (Wektor<Typ,Rozmiar> Wek);
    Macierz<Typ,Rozmiar> operator * (Macierz<Typ,Rozmiar> Mac);
    Macierz<Typ,Rozmiar> operator + (Macierz<Typ,Rozmiar> Arg);
    /*!
     * \brief Funktor macierzy.
     *
     * \param[in] Ind - indeks macierzy.
     * 
     * \return Zwraca wartosc macierzy w danym miejscu tablicy.
      */
    Typ  operator () (int x, int y) const { return Tab[x][y]; };
    /*!
     * \brief Funktor macierzy.
     *
     * \param[in] Ind - indeks macierzy.
     * 
     * \return Zwraca wartosc macierzy w danym miejscu tablicy jako stala.
      */
    Typ &operator () (int x, int y) { return Tab[x][y]; };   

};

/*!
 * \brief Konstruktor klasy Macierz.
 */
template <typename Typ, int Rozmiar>
Macierz<Typ,Rozmiar>::Macierz()
{
  for(int i=0; i < Rozmiar; ++i){
        for(int j=0; j < Rozmiar; ++j){
            
          if(i==0 && j==0){ Tab[i][j] = 1;}
          else if(i==1 && j==1){ Tab[i][j] = 1;}
          else if(i==2 && j==2){ Tab[i][j] = 1;} 
          else Tab[i][j] = 0;
        }
    }
}

/*!
 * \brief Konstruktor klasy Macierz.
 *
 * \param[in] rListaWsp - lista z rozmiarem macierzy.
 * 
 */
template <typename Typ, int Rozmiar>
Macierz<Typ,Rozmiar>::Macierz(const initializer_list<Typ> &rListaWsp):Macierz()
{
  assert(rListaWsp.size() <= Rozmiar);
  int Ind = -1;
  for (double Wsp_i : rListaWsp) Tab[++Ind] = Wsp_i;
}

/*!
 * \brief Realizuje dodawanie dwóch macierzy.
 *
 * \param[in] Arg - drugi skladnik dodawania.
 * 
 * \return Zwraca wynik dodawania dwoch macierzy. 
 */
template <typename Typ, int Rozmiar>
Macierz<Typ,Rozmiar> Macierz<Typ,Rozmiar>::operator + (Macierz Arg){

    Macierz<Typ,Rozmiar> Wynik;

    for(int i=0; i < Rozmiar; ++i){
        for(int j=0; j < Rozmiar; ++j){
            Wynik(i,j) = Tab[i][j] + Arg(i,j);
        }
    }
    return Wynik;
}

/*!
 * \brief Realizuje mnozenie macierzy przez wektor.
 *
 * \param[in] Arg - wektor przez ktory bedziemy mnozyc.
 * 
 * \return Zwraca wynik mnozenia macierzy przez wektor. 
 */
template <typename Typ, int Rozmiar>
Wektor<Typ,Rozmiar> Macierz<Typ,Rozmiar>::operator * (Wektor<Typ,Rozmiar> Wek){

    Wektor<Typ,Rozmiar> Wynik;

    for(int i=0; i < Rozmiar; ++i){
        for(int j=0; j < Rozmiar; ++j){
            Wynik[i] += Tab[i][j] * Wek[j];
        }
    }
    return Wynik;
}

/*!
 * \brief Realizuje mnozenie macierzy przez macierz.
 *
 * \param[in] Arg - macierz przez ktora bedziemy mnozyc.
 * 
 * \return Zwraca wynik mnozenia macierzy przez macierz. 
 */
template <typename Typ, int Rozmiar>
Macierz<Typ,Rozmiar> Macierz<Typ,Rozmiar>::operator * (Macierz<Typ,Rozmiar> Mac){

    Macierz<Typ,Rozmiar> Wynik;

    for(int i=0; i < Rozmiar; ++i){
        for(int j=0; j < Rozmiar; ++j){
            Wynik(i,j) += Tab[i][j] * Mac(i,j);
        }
    }
    return Wynik;
}

/*!
 * \brief Przeciążenie operatora wyswietlania.
 *
 *  Realizuje wyswietlanie wierzcholkow figury zapisanych w pliku.
 * 
 * \param[in] Sout - strumien wyjsciowy.
 * \param[in] Mac - macierz
 * 
 * \return Zwraca referencje do strumienia wyjsciowego.
 */
template <typename Typ, int Rozmiar>
ostream& operator << (ostream &Sout, const Macierz<Typ,Rozmiar> &Mac)
{
  for(int i=0; i < Rozmiar; ++i){
        for(int j=0; j < Rozmiar; ++j){
            Sout << "  " << Mac(i,j) << "  ";
        }
        cout << endl;
    }
  return Sout;  
}

/*!
 * \brief Ustawia macierz obrotu wedlug odpowiednej osi.
 *
 * \param[in] os - os obrotu (x,y,z).
 * \param[in] kat - kat o ktory zostanie wykonany obrot.
 * 
 * \return Zwraca odpowiednia macierz rotacji. 
 */
template <typename Typ, int Rozmiar>
Macierz<Typ,Rozmiar> Macierz<Typ,Rozmiar>::UstawObrot(double kat){

    Macierz<Typ,Rozmiar> Tab;

    Tab(0,0) = cos(kat*M_PI/180);
    Tab(0,1) = -sin(kat*M_PI/180);
    Tab(0,2) = 0;
    Tab(1,0) = sin(kat*M_PI/180);
    Tab(1,1) = cos(kat*M_PI/180);
    Tab(1,2) = 0;
    Tab(2,0) = 0;
    Tab(2,1) = 0;
    Tab(2,2) = 1;
 
    return Tab;
}

#endif
