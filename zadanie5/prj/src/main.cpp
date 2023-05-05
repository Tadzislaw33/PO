/*!
 * \file
 * \brief Przykład animacji przelotu drona
 *
 * Przykład ten ma tylko i wyłącznie za zadanie pokazanie efektów animacji lotu
 * drona. Kod w nim zawarty nie jest pisany w sposób obiektowo zorientowany.
 * Dlatego też nie należy wzorować się na nim.
 * Niemniej można się wzorować na ciągu operacji, które należy wykonać,
 * aby otrzymać właściwą animację.
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <unistd.h>
#include "lacze_do_gnuplota.hh"
#include "Graniastoslup6.hh"
#include "Prostopadloscian.hh"
#include "Scena.hh"
#include "Wektor3D.hh"
#include "Macierz3x3.hh"

using namespace std;

/*
#define ILOSC_WIERZCHOLKOW_GRANIATOSLUPA  6
#define PROMIEN_PODSTAWY                  10
#define GRUBOSC_ROTORA                    5.0
*/

#define ILOSC_WIERZ_LINII_TWORZACEJ            4

#define PLIK_WZORCOWEGO_SZESCIANU       "bryly_wzorcowe/szescian.dat"
#define PLIK_WZORCOWEGO_GRANIASTOSLUPA6 "bryly_wzorcowe/graniastoslup6.dat"
#define PLIK_KORPUSU_DRONA1             "dat/korpus_drana1.dat"

/*!
 * \brief Dokonuje obrotu wokół osi OZ.
 *
 * Transformuje współrzędne wektora dokonując obrót o zadany kąt.
 * \param[in] KatObrotu_st - kąt, o który ma być zrealizowany obrót.
 * \param[in,out] Wsp - współrzędne x i y punktu przekazane jako wektor, które zostaja przetransformowane.
 */
void ObrocWzgledemOsiOZ( double  KatObrotu_st, Wektor3D &Wsp)
{
  Macierz3x3 Mac = Mac.UstawObrot(KatObrotu_st);
  Wsp = Mac * Wsp;
}

/*!
 * \brief Transformuje współrzędne pojedynczego punktu.
 * 
 * Transformuje współrzędne pojedynczego punktu poprzez ich przeskalowanie i 
 * przesunięcie o zdany wektor translacji. Współczynniki skalowania jak też
 * współrzędne wektora translacji są przekazywane przez parametry tej funkcji.
 *
 * \param[in] KatObrotu_st - kąt, o jaki ma być dokonany obrót. Wartość kąta wyrażona
 *                           jest w stopniach.
 * \param[in,out]  Wsp - współrzędne x, y, z punktu przekazane jako wektor, które maja zostać poddane transformacji.
 * \param[in] Skala - współczynnik skalowania przekazany jako wektor.
 * \param[in] Trans - współrzędne x, y, z wektora translacji.
 */
void TransformujWspolrzednePunktu(double  KatObrotu_st, Wektor3D &Wsp, Wektor3D &Skala, Wektor3D &Trans)
{
  ObrocWzgledemOsiOZ(KatObrotu_st, Wsp);
  Wsp[0] = Wsp[0] * Skala[0] + Trans[0];
  Wsp[1] = Wsp[1] * Skala[1] + Trans[1];
  Wsp[2] = Wsp[2] * Skala[2] + Trans[2];  
}

/*!
 * \brief  Transformuje całą bryłę.
 *
 * Czyta ze strumienia wejściowego współrzędne wierzchołków bryły, dokonuje 
 * ich transformacji (skalowanie, obrót i translacja)
 * Zapisuje do strumienia współrzędne wierzchołków przetransformowanej bryły
 * w ten sposób, aby korpus mógł być poprawnie narysowany przez program gnuplot.
 * \param[in,out] StrmWe - strumień zawierający opis bryły, która ma podlegać
 *                                        transformacji. Współrzędne z tego strumienia są
 *                                        tylko czytane.
 * \param[in,out] StrmWy - strumień zawierający opis bryły po dokonanej tranformacji.
 * \param[in] KatObrotu_st - kąt, o jaki ma być dokonany obrót. Wartość kąta wyrażona jest w stopniach.
 * \param[in] Skala - współczynnik skalowania przekazany jako wektor.
 * \param[in] Trans - współrzędne x, y, z wektora translacji.
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - gdy operacja nie powiedzie się z powodu niepowodzenia odczytu lub zapisu do strumienia.
 */
bool TworzOpisPrzetransformowanejBryly(istream &StrmWe, ostream &StrmWy, double KatObrotu_st, Wektor3D &Skala, Wektor3D &Trans)
{
  assert(StrmWe.good());
  assert(StrmWy.good());

  Wektor3D Wsp;

  StrmWe >> Wsp;
  while (!StrmWe.fail()) {

    for (unsigned int IloscWierzcholkow = 0; IloscWierzcholkow < ILOSC_WIERZ_LINII_TWORZACEJ;++IloscWierzcholkow) {

      TransformujWspolrzednePunktu(KatObrotu_st, Wsp, Skala, Trans);
      StrmWy << Wsp[0] << " " << Wsp[1] << " " << Wsp[2] << endl;
      StrmWe >> Wsp;
      
      assert(IloscWierzcholkow == ILOSC_WIERZ_LINII_TWORZACEJ-1 || !StrmWe.fail());
    }

    StrmWy << endl;
  }
  return !StrmWy.fail();
}

/*!
 * \brief  Transformuje całą bryłę.
 *
 * Czyta z pliku wejściowego współrzędne wierzchołków bryły, dokonuje 
 * ich transformacji (skalowanie, obrót i translacja)
 * Zapisuje do drugiego pliku współrzędne wierzchołków przetransformowanej bryły
 * w ten sposób, aby mogły korpus mógł być poprawnie narysowany przez program gnuplot.
 * \param[in,out] NazwaPlikuWej - nazwa pliku zawierający opis bryły, która ma podlegać
 *                                        transformacji. Współrzędne z tego strumienia są
 *                                        tylko czytane.
 * \param[in,out] NazwaPlikuWyj - nazwa pliku, który ma zawierać opis bryły
 *                                         po dokonanej tranformacji.
 * \param[in] KatObrotu_st - kąt, o jaki ma być dokonany obrót. Wartość kąta wyrażona
 *                           jest w stopniach.
 * \param[in] Skala - współczynnik skalowania przekazany jako wektor.
 * \param[in] Trans - współrzędne x, y, z wektora translacji.
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - gdy operacja nie powiedzie się z powodu braku możliwości 
 *                 otwarcia jednego z plików lub niepowodzenia odczytu lub zapisu do pliku.
 */
bool TworzOpisPrzetranformowanejBryly(const char* NazwaPlikuWej, const char* NazwaPlikuWyj, double KatObrotu_st, Wektor3D &Skala, Wektor3D &Trans)
{ 
  ifstream  Plik_BrylaWzorcowa(NazwaPlikuWej);
  ofstream  Plik_KorpusuDrona(NazwaPlikuWyj);

  if (!Plik_BrylaWzorcowa.is_open()) {
    cerr << endl << " Blad otwarcia do odczytu pliku: " << NazwaPlikuWej << endl << endl;
    return false;
  }

  if (!Plik_KorpusuDrona.is_open()) {
    cerr << endl << " Blad otwarcia do odczytu pliku: " << NazwaPlikuWyj << endl << endl;
    return false;
  }
  
  return TworzOpisPrzetransformowanejBryly(Plik_BrylaWzorcowa, Plik_KorpusuDrona, KatObrotu_st, Skala, Trans);
}

/*!
 * \brief Tworzy plik z wierzchołkami były modelującej rotor drona.
 *
 * Tworzy plik, w którym zostają zapise współrzędne wierzchołków
 * tworzących pojedynczy rotor drona. Zapisane one są w ten sposób, aby program gnuplot
 * mógł wyświetlić graniastosłubp Tworzona bryła zostaje obrócona
 * względem swojej pierwotnej orientacji o zadany kąt oraz przesunięta o wektor
 * translacji, którego współrzędne podane są jako parametry tej funkcji.
 *
 * \param[in] NazwPliku_RotorWDronie - nazwa pliku, w którym zostaną zapisane współrzędne
 *                                       wierzchołków bryły tworzącej rotor drona.
 * \param[in] KatObrotuRotora_st - kąt obrotu korpusu. Jego wartość wyrażona jest w stopniach.
 * \param[in] tx_trans - x-owa współrzędna wektora translacji.
 * \param[in] ty_trans - y-owa współrzędna wektora translacji.
 * \param[in] tz_trans - z-owa współrzędna wektora translacji.
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - gdy operacja nie powiedzie się z powodu braku możliwości 
 *                 otwarcia jednego z plików lub niepowodzenia odczytu lub zapisu do pliku.
 */
bool TworzRotor(const char* NazwPliku_RotorWDronie, double KatObrotuRotora_st, Wektor3D &Trans)
{
  Wektor3D Skala;
  Skala[0]=8; Skala[1]=8; Skala[2]=2;
  return TworzOpisPrzetranformowanejBryly(PLIK_WZORCOWEGO_GRANIASTOSLUPA6, NazwPliku_RotorWDronie, KatObrotuRotora_st, Skala, Trans);
}

/*!
 * \brief Tworzy plik z wierzchołkami były modelującej korpus drona.
 *
 * Tworzy plik, w którym zostają zapise współrzędne wierzchołków
 * tworzących korpus drona. Zapisane one są w ten sposób, aby program gnuplot
 * mógł wyświetlić prostopadłościan. Tworzona bryła zostaje obrócona
 * względem swojej pierwotnej orientacji o zadany kąt oraz przesunięta o wektor
 * translacji, którego współrzędne podane są jako parametry tej funkcji.
 *
 * \param[in] NazwPliku_KorpusuWDronie - nazwa pliku, w którym zostaną zapisane współrzędne
 *                                       wierzchołków bryły tworzącej korpus drona.
 * \param[in] KatObrotuKorpusu_st - kąt obrotu korpusu. Jego wartość wyrażona jest w stopniach.
 * \param[in] tx_trans - x-owa współrzędna wektora translacji.
 * \param[in] ty_trans - y-owa współrzędna wektora translacji.
 * \param[in] tz_trans - z-owa współrzędna wektora translacji.
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - gdy operacja nie powiedzie się z powodu braku możliwości 
 *                 otwarcia jednego z plików lub niepowodzenia odczytu lub zapisu do pliku. 
 */
bool TworzKorpus(const char* NazwPliku_KorpusuWDronie, double KatObrotuKorpusu_st, Wektor3D &Trans)
{
  Wektor3D Skala;
  Skala[0]=10; Skala[1]=8; Skala[2]=4;
  return TworzOpisPrzetranformowanejBryly(PLIK_WZORCOWEGO_SZESCIANU, NazwPliku_KorpusuWDronie, KatObrotuKorpusu_st, Skala, Trans);
}

#define PLIK_ROBOCZY__DRON1_KORPUS  "dat/PlikRoboczy_Dron1_Korpus.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR1  "dat/PlikRoboczy_Dron1_Rotor1.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR2  "dat/PlikRoboczy_Dron1_Rotor2.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR3  "dat/PlikRoboczy_Dron1_Rotor3.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR4  "dat/PlikRoboczy_Dron1_Rotor4.dat"

#define PLIK_WLASCIWY__DRON1_KORPUS  "dat/PlikWlasciwy_Dron1_Korpus.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR1  "dat/PlikWlasciwy_Dron1_Rotor1.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR2  "dat/PlikWlasciwy_Dron1_Rotor2.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR3  "dat/PlikWlasciwy_Dron1_Rotor3.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR4  "dat/PlikWlasciwy_Dron1_Rotor4.dat"

/*!
 * \brief Tworzy pliki pozwalające na wizualizację drona.
 * 
 * Zapisuje do odpwiednich plików opisy brył tworzących wizualizację drona.
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - gdy operacja nie powiedzie się z powodu braku możliwości 
 *                 otwarcia jednego z plików lub niepowodzenia odczytu lub zapisu do pliku.
 */
bool TworzDrona()
{
  static double KatObrotuRotora_st = 0; 

  Wektor3D TransD, TransRLP, TransRPP, TransRLT, TransRPT;
  TransD[0]=0; TransD[1]=0; TransD[2]=2;
  TransRLP[0]=5; TransRLP[1]=4; TransRLP[2]=5;
  TransRPP[0]=5; TransRPP[1]=-4; TransRPP[2]=5;
  TransRLT[0]=-5; TransRLT[1]=4; TransRLT[2]=5;
  TransRPT[0]=-5; TransRPT[1]=-4; TransRPT[2]=5;

  //----------------------------------------------------------
  // Korpus drona jest podniesiony o 4. Dzięki temu początek układu
  // współrzędnych drona jest na środku dolnej podstawy korpusu.
  //
  if (!TworzKorpus(PLIK_ROBOCZY__DRON1_KORPUS,0,TransD)) return false;

  if (!TworzRotor(PLIK_ROBOCZY__DRON1_ROTOR1, KatObrotuRotora_st,TransRLP)) return false;
  if (!TworzRotor(PLIK_ROBOCZY__DRON1_ROTOR2, -KatObrotuRotora_st,TransRPP)) return false;
  if (!TworzRotor(PLIK_ROBOCZY__DRON1_ROTOR3, -KatObrotuRotora_st,TransRLT)) return false;
  if (!TworzRotor(PLIK_ROBOCZY__DRON1_ROTOR4, KatObrotuRotora_st,TransRPT)) return false;

  #define SKOK_OBROTU_ROTOROW_stopnie  10
  KatObrotuRotora_st += SKOK_OBROTU_ROTOROW_stopnie;
  return true;
}

/*!
 * \brief Ustawia dron w żądanej pozycji i orientacji.
 *
 * Dron zostaje przeniesiony do wskazanej pozycji. Jego orientacja zostaje zmieniona
 * zgodnie z zadanym kątem.
 *
 * \param[in] KatOrDrona_st - kąta orientacji drona. Jest to kąt względem osi OZ.
 *                            Wartość orientacji drona wyrażona jest w stopniach.
 * \param[in] x_PozDrona - x-owa współrzędna pozycji drona.
 * \param[in] y_PozDrona - y-owa współrzędna pozycji drona.
 * \param[in] z_PozDrona - z-owa współrzędna pozycji drona.
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - w przypadku przeciwnym.
 *                 Może się to zdarzyć, gdy niepowiedzie się otwarcie jednego z plików,
 *                 z których korzysta ta funkcja,
 *                 lub niepowodzenia odczytu lub zapisu do wspomnianych plików.
 */
bool PrzemiescDrona(double KatOrDrona_st, Wektor3D PozDrona)
{
  Wektor3D Skala;
  Skala[0]=1; Skala[1]=1; Skala[2]=1;
  
  if (!TworzDrona()) return false;
  //--------------------------------------------------
  // Transformacja elementów drona do właściwej pozycji
  //
  const char *NazwyPlikowRoboczych[] = { PLIK_ROBOCZY__DRON1_KORPUS, PLIK_ROBOCZY__DRON1_ROTOR1,
					 PLIK_ROBOCZY__DRON1_ROTOR2, PLIK_ROBOCZY__DRON1_ROTOR3,
					 PLIK_ROBOCZY__DRON1_ROTOR4, nullptr
                                        };
  const char *NazwyPlikowWlasciwych[] = { PLIK_WLASCIWY__DRON1_KORPUS, PLIK_WLASCIWY__DRON1_ROTOR1,
					 PLIK_WLASCIWY__DRON1_ROTOR2, PLIK_WLASCIWY__DRON1_ROTOR3,
					 PLIK_WLASCIWY__DRON1_ROTOR4, nullptr
                                        };
  
  assert(sizeof(NazwyPlikowRoboczych) == sizeof(NazwyPlikowWlasciwych));

  for (unsigned int Idx = 0; NazwyPlikowRoboczych[Idx] != nullptr; ++Idx) {
    if (!TworzOpisPrzetranformowanejBryly(NazwyPlikowRoboczych[Idx], NazwyPlikowWlasciwych[Idx], KatOrDrona_st, Skala, PozDrona)) return false;
  }
  return true;
}

#define PLIK_TRASY_PRZELOTU "dat/trasa_przelotu.dat"

/*!
 * \brief Dodaje trasę przelotu.
 *
 * Tworzony jest plik z trasę przelotu w postaci łamanej.
 * Nazwa pliku zostaje dodana do łącza do gnuplota.
 * Dzięki temu dane zawarte w tym pliku zostaną użyte przez
 * gnuplota do narysowania łamanej.
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - w przypadku przeciwnym.
 *                 Może się to zdarzyć, gdy niepowiedzie się otwarcie plików,
 *                 do którego zapisywane są współrzędne łamanej modelującej ścieżkę
 *                 przelotu drona, lub niepowodzenia zapisu do tego pliku.
 */
bool DodajTrasePrzelotu(PzG::LaczeDoGNUPlota &Lacze)
{
  ofstream  StrmWy(PLIK_TRASY_PRZELOTU);

  if (!StrmWy.is_open()) {
    cerr << endl << " Nie mozna otworzyc do zapisu pliku: " << PLIK_TRASY_PRZELOTU << endl << endl;
    return false;
  }

  StrmWy << "20  20   0" << endl
	       << "20  20  80" << endl
         << "150 150 80" << endl
         << "150 150  0" << endl;
  Lacze.DodajNazwePliku(PLIK_TRASY_PRZELOTU);
  return !StrmWy.fail();
}

/*!
 * \brief Anicja przelotu drona.
 *
 * Animacja przelotu drona.
 * Animacja ta jest robiona na "sztywno"
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - w przypadku przeciwnym.
 *                 Może się to zdarzyć, gdy niepowiedzie się otwarcie jednego z plików,
 *                 z których korzysta ta funkcja,
 *                 lub niepowodzenia odczytu lub zapisu do wspomnianych plików.
 */
bool AnimacjaLotuDrona(PzG::LaczeDoGNUPlota &Lacze)
{
  Wektor3D Wsp;
  Wsp[0]=20; Wsp[1]=20; Wsp[2]=0;
  double KatOr_st = 0;

  //-------------------------------------
  // Wznoszenie ...
  //
  cout << endl << "Wznoszenie ... " << endl;
  for (; Wsp[2] <= 80; Wsp[2] += 2) {
    if (!PrzemiescDrona(KatOr_st,Wsp)) return false;
    usleep(100000); // 0.1 ms
    Lacze.Rysuj();
  }
  Wsp[2] -= 2;
  
  cout << "Zmiana orientacji ... " << endl;
  for (; KatOr_st <= 45; KatOr_st += 5) {
    if (!PrzemiescDrona(KatOr_st,Wsp)) return false;
    usleep(100000);
    Lacze.Rysuj();
  }
  KatOr_st -= 5;

  //-------------------------------------
  // Lot do przodu ...
  //  
  cout << "Lot do przodu ... " << endl;
  for (; Wsp[0] <= 150; Wsp[0] += 1, Wsp[1] += 1) {
    if (!PrzemiescDrona(KatOr_st,Wsp)) return false;
    usleep(100000);
    Lacze.Rysuj();
  }  
  Wsp[0] -= 1, Wsp[1] -= 1;


  //-------------------------------------
  // Opadanie ...
  //
  cout << "Opadanie ... " << endl;
  for (; Wsp[2] >= 0; Wsp[3] -= 2) {
    if (!PrzemiescDrona(KatOr_st,Wsp)) return false;
    usleep(100000); // 0.1 ms
    Lacze.Rysuj();
  }

  return true;
}





int main()
{
  PzG::LaczeDoGNUPlota  Lacze;

  Lacze.DodajNazwePliku("bryly_wzorcowe/plaszczyzna.dat");
  /*Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_KORPUS);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR1);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR2);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR3);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR4);
*/
  Lacze.ZmienTrybRys(PzG::TR_3D);
  Lacze.Inicjalizuj();  // Tutaj startuje gnuplot.

  Lacze.UstawZakresX(0, 200);
  Lacze.UstawZakresY(0, 200);
  Lacze.UstawZakresZ(0, 120);

  Wektor3D PozDrona;
  PozDrona[0]=20; PozDrona[1]=20; PozDrona[2]=0;

  Lacze.UstawRotacjeXZ(64,65); // Tutaj ustawiany jest widok
/*
  if (!PrzemiescDrona(0,PozDrona)) return 0;

*/
  Lacze.Rysuj();        // Teraz powinno pojawic sie okienko gnuplota
                        // z rysunkiem, o ile istnieje plik "prostopadloscian1.pow"
  cout << "Nacisnij ENTER, aby pokazac sciezke przelotu drona " << flush;
  cin.ignore(10000,'\n');

  cout << endl << "Aktualna ilosc wektorow: " << Wektor3D::WezWartoscAktywnegoLicznikaObiektow() << endl;
  cout << "Ogolna Ilosc wektorow: " << Wektor3D::WezWartoscLicznikaObiektow() << endl;

  Lacze.DodajNazwePliku("dat/trasa_przelotu.dat");
  Lacze.Rysuj();
/*
  Dron Dr;
  if (!Dr.PlanujPoczatkowaSciezke(40,100,)) return 1;
  Lacze.Rysuj();
*/

  cout << "Nacisnij ENTER, aby wykonac animacje lotu drona " << flush;
  cin.ignore(10000,'\n');
  /*if (!AnimacjaLotuDrona(Lacze)) return 1;

  cout << endl << "Nacisnij ENTER, aby usunac sciezke ... " << flush;
  cin.ignore(10000,'\n');

  Lacze.UsunNazwePliku(PLIK_TRASY_PRZELOTU);
  Lacze.Rysuj();
  
  cout << "Nacisnij ENTER, aby zakonczyc ... " << flush;
  cin.ignore(10000,'\n');*/
  
}
