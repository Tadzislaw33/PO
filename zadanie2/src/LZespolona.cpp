#include "LZespolona.hh"

LZespolona &operator += (LZespolona &Skl1, LZespolona &Skl2){

  Skl1.re = Skl1.re + Skl2.re;
  Skl1.im = Skl1.im + Skl2.im;

  return Skl1;
}

LZespolona &operator *= (LZespolona &Skl1, LZespolona &Skl2){

  Skl1.re = Skl1.re * Skl2.re;
  Skl1.im = Skl1.im * Skl2.im;

  return Skl1;
}


/*!
 * Realizuje porownanie dwoch liczb zespolonych.
 * Argumenty:
 *    Skl1 - pierwszy skladnik ,
 *    Skl2 - drugi skladnik.
 * Zwraca:
 *    Wartosc bool w zaleznosci od poprawnosci porownania.
 */
bool  LZespolona::operator == (LZespolona Skl2){

  if((re == Skl2.re)&&(im == Skl2.im))
      return true;
    else
      return false;
}

/*!
 * Realizuje dodanie dwoch liczb zespolonych.
 * Argumenty:
 *    Skl1 - pierwszy skladnik dodawania,
 *    Skl2 - drugi skladnik dodawania.
 * Zwraca:
 *    Sume dwoch skladnikow przekazanych jako parametry.
 */
LZespolona  LZespolona::operator + (LZespolona  Skl2)
{
  LZespolona  Wynik;

  Wynik.re = re + Skl2.re;
  Wynik.im = im + Skl2.im;
  
  return Wynik;
}

/*!
 * Realizuje odejmowanie dwoch liczb zespolonych.
 * Argumenty:
 *    Skl1 - pierwszy skladnik odejmowania,
 *    Skl2 - drugi skladnik odejmowania.
 * Zwraca:
 *    Roznica dwoch skladnikow przekazanych jako parametry.
 */
LZespolona LZespolona::operator - (LZespolona  Skl2){

  LZespolona Wynik;

  Wynik.re = re - Skl2.re;
  Wynik.im = im - Skl2.im;

  return Wynik;
}

/*!
 * Realizuje mnozenie dwoch liczb zespolonych.
 * Argumenty:
 *    Skl1 - pierwszy skladnik mnozenia,
 *    Skl2 - drugi skladnik mnozenia.
 * Zwraca:
 *    iloczyn dwoch skladnikow przekazanych jako parametry.
 */
LZespolona LZespolona::operator * (LZespolona  Skl2){

  LZespolona Wynik;

  Wynik.re = re * Skl2.re - im * Skl2.im;
  Wynik.im = re * Skl2.im + Skl2.re * im;

  return Wynik;
}

/*!
 * Realizuje dzielenie dwoch liczb zespolonych.
 * Argumenty:
 *    Skl1 - pierwszy skladnik dzielenia,
 *    Skl2 - drugi skladnik dzielenia.
 * Zwraca:
 *    iloraz dwoch skladnikow przekazanych jako parametry.
 */
LZespolona LZespolona::operator / (LZespolona  Skl2){

  LZespolona Wynik, licznik;
  double modul2;

  modul2 = Skl2.Modul2();
  licznik = *this*Skl2.Sprzezenie();

  if(modul2 == 0){
    throw domain_error("Dzielenie przez 0\n");
  } 

  Wynik.re = licznik.re/modul2;
  Wynik.im = licznik.im/modul2;
  
  return Wynik;
}

/*!
 * Wykonuje sprzezenie liczby zespolonej.
 * Argumenty:
 *    lzesp - liczba zespolona.
 * Zwraca:
 *    liczba zespolona z przeciwna czescia urojona.
 */
LZespolona LZespolona::Sprzezenie(){

  LZespolona Wynik;

  Wynik.re = re;
  Wynik.im = -im;

  return Wynik;
}

/*!
 * Oblicza modul do kwadratu liczby zespolonej.
 * Argumenty:
 *    lzesp - liczba zespolona.
 * Zwraca:
 *    liczbe rzeczywista jako kwadrat modulu liczby zespolonej.
 */
double LZespolona::Modul2(){

  return re*re + im*im;
}

/*!
 * Przeciazenie operatora << do wyswietlania liczby zespolonej.
 * Argumenty:
 *    &sout - referencja do obiektu ostream,
 *    lzesp - liczba zespolona.
 * Zwraca:
 *    referencja do strumienia wyjsciowego(wyswietla lzesp w zadanym formacie).
 */
ostream& operator << ( ostream& sout, LZespolona lzesp){

  sout << "(" << lzesp.re << showpos << lzesp.im << noshowpos << "i)";

  return sout;
}

/*!
 * Przeciazenie operatora >> do wczytywania liczby zespolonej.
 * Argumenty:
 *    &sin - referencja do obiektu istream,
 *    &lzesp - referencja do liczby zespolonej.
 * Zwraca:
 *    referencja do strumienia wejsciowego(wczytuje lzesp w zadanym formacie).
 */
istream& operator >> ( istream& sin, LZespolona& lzesp){

  char Nawias, Litera;
  
  sin >> Nawias;
  if(sin.fail()) return sin;
  if(Nawias!='('){
    sin.setstate(ios::failbit);
    return sin;
  }

  sin >> lzesp.re;
  if(sin.fail()) return sin;

  sin >> lzesp.im;
  if(sin.fail()) return sin;

  sin >> Litera;
  if(sin.fail()) return sin;
  if(Litera!='i'){
    sin.setstate(ios::failbit);
    return sin;
  }

  sin >> Nawias;
  if(sin.fail()) return sin;
  if(Nawias!=')'){
    sin.setstate(ios::failbit);
    return sin;
  }

  return sin;
}
