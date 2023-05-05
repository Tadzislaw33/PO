#include "BazaTestu.hh"

using namespace std;

/*
 * W bazie testu ustawia wybrany test jako biezacy test i indeks pytania
 * ustawia na pierwsze z nich. Pytania testowe wczzytywane sa z dolaczonych plikow.
 * Parametry:
 *    wskBazaTestu - wskaznik na zmienna reprezentujaca baze testu,
 *    wskTabTestu  - wskaznik na tablice zawierajaca wyrazenia arytmetyczne
 *                   bedace przedmiotem testu,
 *    IloscPytan - ilosc pytan w tablicy.
 *    sNazwaTestu - wskaznik na napis wybranego typu testu.
 *   
 * Warunki wstepne:
 *      - Parametr wskBazaTestu nie moze byc pustym wskaznikiem. Musi zawierac adres
 *        zmiennej reprezentujacej baze testu, ktora wczesniej zostal poprawnie
 *        zainicjalizowany poprzez wywolanie funkcji InicjalizujTest.
 *      - Parametr wskTabTestu zawiera wskaznik na istniejaca tablice.
 *      - Parametr IloscPytan zawiera wartosc, ktora nie przekracza ilosci elementow
 *        w tablicy dostepnej poprzez wskTabTestu.
 */
void BazaTestu::UstawTest(WyrazenieZesp *wskTabTestu, unsigned int IloscPytan, const char*  sNazwaTestu )
{
  *this->wskTabTestu = *wskTabTestu;
  this->IloscPytan = IloscPytan;
  this->IndeksPytania = 0;

  ifstream database;
  int i=0;
  
  if (!strcmp(sNazwaTestu,"latwy"))
  database.open("./bazy_testu/bazy_testu/data/baza_latwy.dat");

  if (!strcmp(sNazwaTestu,"trudny"))
  database.open("./bazy_testu/bazy_testu/data/baza_trudny.dat");

  while (true)
  {
    database >> wskTabTestu[i++];
    if(database.good()!=true) break;
  }
  database.close(); 
}

/*
 * Inicjalizuje test kojarzac zmienna dostepna poprzez wskaznik wskBazaTestu
 * z dana tablica wyrazen, ktora reprezentuje jeden z dwoch dopuszczalnych 
 * testow.
 * Parametry:
 *    wskBazaTestu - wskaznik na zmienna reprezentujaca baze testu.
 *    sNazwaTestu  - wskaznik na napis wybranego typu testu.
 *
 * Warunki wstepne:
 *      - Parametr wskBazaTestu nie moze byc pustym wskaznikiem. Musi zawierac adres
 *        zmiennej reprezentujacej baze testu, ktora wczesniej zostal poprawnie
 *        zainicjalizowany poprzez wywolanie funkcji InicjalizujTest.
 *      - Parametr sNazwaTestu musi wskazywac na jedna z nazw tzn. "latwe" lub "trudne".
 *       
 * Zwraca:
 *       true - gdy operacja sie powiedzie i test zostanie poprawnie
 *              zainicjalizowany,
 *       false - w przypadku przeciwnym.
 */
bool BazaTestu::InicjalizujTest(const char *sNazwaTestu )
{
  if (!strcmp(sNazwaTestu,"latwy")) {
    UstawTest(wskTabTestu,sizeof(wskTabTestu)/sizeof(WyrazenieZesp),"latwy");
    return true;
  }
  if (!strcmp(sNazwaTestu,"trudny")) {
    UstawTest(wskTabTestu,sizeof(wskTabTestu)/sizeof(WyrazenieZesp),"trudny");
    return true;
  }

  cerr << "Otwarcie testu '" << sNazwaTestu << "' nie powiodlo sie." << endl;
  return false;
}

/*!
 * Funkcja udostepnia nastepne pytania o ile jest odpowiednia ich ilosc.
 * Parametry:
 *       wskBazaTestu - wskaznik na zmienna reprezentujaca baze testu.
 *       wskWyrazenie - wskaznik na zmienna, do ktorej zostanie wpisane
 *                      kolejne wyrazenie z bazy testu.
 *
 * Warunki wstepne:
 *      - Parametr wskBazaTestu nie moze byc pustym wskaznikiem. Musi zawierac adres
 *        zmiennej reprezentujacej baze testu, ktora wczesniej zostal poprawnie
 *        zainicjalizowany poprzez wywolanie funkcji InicjalizujTest.
 *      - Parametr wskWyrazenie nie moze byc pustym wskaznikiem. Musi wskazywac na
 *        istniejaca zmienna.
 *
 * Zwraca:
 *       true - gdy operacja sie powiedzie i parametrowi *wskWyrazenie zostanie
 *              przypisane nowe wyrazenie zespolone z bazy,
 *       false - w przypadku przeciwnym.
 */
bool BazaTestu::PobierzNastpnePytanie(WyrazenieZesp *wskWyrazenie )
{
  if (this->IndeksPytania >= this->IloscPytan) return false;

  *wskWyrazenie = this->wskTabTestu[this->IndeksPytania];
  ++this->IndeksPytania;
  return true;
}
