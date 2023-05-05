#include "Wektor2D.hh"
#include "Macierz2x2.hh"
#include "Prostokat.hh"
#include "lacze_do_gnuplota.hh"

/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do strumienia wyjściowego.
 * Dane sa odpowiednio sformatowane, tzn. przyjęto notację stałoprzecinkową
 * z dokładnością do 10 miejsca po przecinku. Szerokość wyświetlanego pola 
 * to 16 miejsc, sposób wyrównywania - do prawej strony.
 * \param[in] StrmWy - strumien wyjsciowy, do ktorego maja zostac zapisane
 *                     kolejne wspolrzedne.
 * \param[in] Przesuniecie - ten parameter jest tylko po to, aby pokazać
 *                          mozliwosc zmiany wspolrzednych i prostokata
 *                          i zmiane jego polorzenia na okienku graficznym
 *                         rysownym przez gnuplota.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
void ZapisDoStrumienia( ostream& StrmWy, Prostokat Pr)
{
  StrmWy << Pr << Pr[0] << endl;
}

/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do pliku, z ktorego
 * dane odczyta program gnuplot i narysuje je w swoim oknie graficznym.
 * \param[in] sNazwaPliku - nazwa pliku, do którego zostana zapisane
 *                          wspolrzędne punktów.
 * \param[in] Przesuniecie - ten parameter jest tylko po to, aby pokazać
 *                          mozliwosc zmiany wspolrzednych i prostokata
 *                          i zmiane jego polorzenia na okienku graficznym
 *                         rysownym przez gnuplota.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool ZapisDoPliku( const char *sNazwaPliku, Prostokat Pr)
{
  ofstream  StrmPlikowy;

  StrmPlikowy.open(sNazwaPliku);
  if (!StrmPlikowy.is_open())  {
    cerr << ":(  Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << endl
	 << ":(  nie powiodla sie." << endl;
    return false;
  }
  ZapisDoStrumienia(StrmPlikowy,Pr);
  StrmPlikowy.close();
  return !StrmPlikowy.fail();
}

void menu(){

       cout << "|---------------------MENU--------------------|" << endl;
       cout << "| o - obrot prostokata o zadany kat           |" << endl;
       cout << "| p - przesuniecie prostokata o zadany wektor |" << endl;
       cout << "| w - wyswietlenie wierzcholkow               |" << endl;
       cout << "| m - wyswietlenie menu                       |" << endl;
       cout << "| k - koniec dzialania programu               |" << endl;
       cout << "|---------------------------------------------|" << endl;
}

int main(){

       PzG::LaczeDoGNUPlota  Lacze;  // Ta zmienna jest potrzebna do wizualizacji rysunku prostokata
                                   
       //  Wspolrzedne wierzcholkow beda zapisywane w pliku "prostokat.dat"
       //  Ponizsze metody powoduja, ze dane z pliku beda wizualizowane
       //  na dwa sposoby:
       //   1. Rysowane jako linia ciagl o grubosci 2 piksele
       //
       Lacze.DodajNazwePliku("prostokat.dat",PzG::RR_Ciagly,2);
       //
       //   2. Rysowane jako zbior punktow reprezentowanych przez kwadraty,
       //      których połowa długości boku wynosi 2.
       //
       Lacze.DodajNazwePliku("prostokat.dat",PzG::RR_Punktowy,2);
       //
       //  Ustawienie trybu rysowania 2D, tzn. rysowany zbiór punktów
       //  znajduje się na wspólnej płaszczyźnie. Z tego powodu powoduj
       //  jako wspolrzedne punktow podajemy tylko x,y.
       //
       Lacze.ZmienTrybRys(PzG::TR_2D);

       Wektor2D wektor1;
       Wektor2D wektor2;
       Wektor2D wektor3;
       Wektor2D wektor4;
       wektor1[0]=10;
       wektor1[1]=10;
       wektor2[0]=110;
       wektor2[1]=10;
       wektor3[0]=110;
       wektor3[1]=60;
       wektor4[0]=10;
       wektor4[1]=60;
       Prostokat Pr;
       Pr[0]=wektor1;
       Pr[1]=wektor2;
       Pr[2]=wektor3;
       Pr[3]=wektor4;
  
       Wektor2D WektorPrzesuniecia;
       char wybor;   
       int powtorzenia;
       double kat;

       Pr.CzyRowne();
       menu();

       while(wybor != 'k'){
              
              cout << "\nTwoj wybor? (m - menu) > ";
              cin >> wybor;
              cout << endl;

              switch (wybor)
              {
                     case 'o':  
                            cout << "Podaj wartosc kata obrotu w stopniach:\n";
                            cin >> kat;
                            cout << "Ile razy operacja obrotu ma byc powtorzona?\n";
                            cin >> powtorzenia;
                            for(int i=0;i < powtorzenia; ++i){
                                   Pr.Rotacja(kat);
                            } 
                            if (!ZapisDoPliku("prostokat.dat",Pr)) return 1;
                            Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
                            Pr.CzyRowne();
                            break;

                     case 'p':  
                            cout << "Wprowadz wspolrzedne wektora translacji (x i y) w postaci dwoch liczb:\n";
                            cin >> WektorPrzesuniecia[0] >> WektorPrzesuniecia[1];          
                            Pr.PrzesunOWektor(WektorPrzesuniecia);
                            if (!ZapisDoPliku("prostokat.dat",Pr)) return 1;
                            Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
                            break;

                     case 'w':  
                            Pr.Wyswietl(Pr);       break;

                     case 'm':  
                            menu();       break;

                     case 'k':  
                            cout << "Koniec dzialania programu\n";    break;
              }
       }
}
