#include "Wektor3D.hh"
#include "Macierz3x3.hh"
#include "Prostopadloscian.hh"
#include "lacze_do_gnuplota.hh"

using namespace std;

/*!
 * Funkcja zapisu wspolrzednych zbioru punktow do strumienia wyjścioweg
 * Dane sa odpowiednio sformatowane, tzn. przyjęto notację stałoprzecinkową
 * z dokładnością do 10 miejsca po przecinku. Szerokość wyświetlanego pola 
 * to 16 miejsc, sposób wyrównywania - do prawej strony.
 * \param[in] StrmWy - strumien wyjsciowy, do ktorego maja zostac zapisane
 *                     kolejne wspolrzedne.
 * \param[in] Pr - element klasy typy Prostopadloscian zawierajacy wierzcholki.
 */
void ZapisDoStrumienia( ostream& StrmWy, Prostopadloscian Pr)
{
  StrmWy << Pr << Pr[0] << endl << Pr[1] << endl;
}

/*!
 * Funkcja zapisu wspolrzednych zbioru punktow do pliku, z ktorego
 * dane odczyta program gnuplot i narysuje je w swoim oknie graficznym.
 * \param[in] sNazwaPliku - nazwa pliku, do którego zostana zapisane
 *                          wspolrzędne punktów.
 * \param[in] Pr - element klasy typy Prostopadloscian zawierajacy wierzcholki.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool ZapisDoPliku( const char *sNazwaPliku, Prostopadloscian Pr)
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

  cout << "|-----------------------MENU-----------------------|" << endl;
  cout << "| o - obrot bryly o zadana sekwencje katow         |" << endl;
  cout << "| p - przesuniecie bryly o zadany wektor           |" << endl;
  cout << "| r - wywietlenie macierzy rotacji                 |" << endl;
  cout << "| w - wyswietlenie wspolrzednych wierzcholkow      |" << endl;
  cout << "| s - sprawdzenie dlugosci przeciwleglych bokow    |" << endl;
  cout << "| m - wyswietlenie menu                            |" << endl;
  cout << "| k - koniec dzialania programu                    |" << endl;
  cout << "|--------------------------------------------------|" << endl;
}

int main(){

    PzG::LaczeDoGNUPlota  Lacze;  // Ta zmienna jest potrzebna do wizualizacji rysunku prostokata

    //-------------------------------------------------------
    //  Wspolrzedne wierzcholkow beda zapisywane w pliku "prostokat.dat"
    //  Ponizsze metody powoduja, ze dane z pliku beda wizualizowane
    //  na dwa sposoby:
    //   1. Rysowane jako linia ciagl o grubosci 2 piksele
    //
    Lacze.DodajNazwePliku("prostopadloscian.dat",PzG::RR_Ciagly,2);
    //
    //  Ustawienie trybu rysowania 3D, tzn. rysowany zbiór punktów
    //  znajduje się na wspólnej płaszczyźnie. Z tego powodu powoduj
    //  jako wspolrzedne punktow podajemy x,y,z.
    //
    Lacze.ZmienTrybRys(PzG::TR_3D);

    // Ustawienie zakresow poszczegolnych osi
    Lacze.UstawZakresY(-300,300);
    Lacze.UstawZakresX(-300,300);
    Lacze.UstawZakresZ(-300,300);

    Wektor3D wektor1, wektor2, wektor3, wektor4;
    Wektor3D wektor5, wektor6, wektor7, wektor8;

    wektor1[0]=10;   wektor1[1]=10;   wektor1[2]=10;
    wektor2[0]=100;  wektor2[1]=10;   wektor2[2]=10;
    wektor3[0]=10;   wektor3[1]=100;  wektor3[2]=10;
    wektor4[0]=100;  wektor4[1]=100;  wektor4[2]=10;

    wektor5[0]=10;   wektor5[1]=100;  wektor5[2]=100;
    wektor6[0]=100;  wektor6[1]=100;  wektor6[2]=100;
    wektor7[0]=10;   wektor7[1]=10;   wektor7[2]=100;
    wektor8[0]=100;  wektor8[1]=10;   wektor8[2]=100;
    
    Prostopadloscian Pr;
    Pr[0]=wektor1; Pr[1]=wektor2;
    Pr[2]=wektor3; Pr[3]=wektor4;
    Pr[4]=wektor5; Pr[5]=wektor6;
    Pr[6]=wektor7; Pr[7]=wektor8;

    
    Wektor3D WektorPrzesuniecia;
    Macierz3x3 MacierzRotacji, Mac, PamietajMacierz;
    
    char wybor, os, powtorzenia;   
    double kat;

    Pr.CzyRowne();
    menu();
    if (!ZapisDoPliku("prostopadloscian.dat",Pr)) return 1;
    Lacze.Rysuj();
    
    while(wybor != 'k'){
                  
        cout << "\nTwoj wybor? (m - menu) > ";
        cin >> wybor;
        cout << endl;

        switch (wybor)
        {
          case 'o':  
              cout << "Podaj sekwencje oznaczen osi oraz katy obrotu w stopniach:\n";
              do{
                cin>>os;
                  if(os!='.'){
                    cin>>kat;
                      if(os!='x' && os!='y' && os!='z' ){
                        cout<<"Bledne oznaczenie osi. Dopuszczalne nazwy x,y,z"<<endl;
                        cout<<"Sprobuj jeszcze raz"<<endl;
                      }
                      else{
                        Mac.UstawObrot(os,kat);
                        MacierzRotacji = MacierzRotacji * Mac;                                       
                      }
                  }
              }while(os!='.');  // wczytywanie do znaku .   
              cout << "Ile razy operacja obrotu ma byc powtorzona?\n";
              cin >> powtorzenia;
                for(int i=0;i < powtorzenia; ++i){
                  Pr.Obrot(MacierzRotacji);
                }       
              if (!ZapisDoPliku("prostopadloscian.dat",Pr)) return 1;
              Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
              Pr.CzyRowne();
                                                        break;

          case 'p':  
              cout << "Wprowadz wspolrzedne wektora translacji (x y z) w postaci trzech liczb:\n";
              cin >> WektorPrzesuniecia;        
              Pr.PrzesunOWektor(WektorPrzesuniecia);
              if (!ZapisDoPliku("prostopadloscian.dat",Pr)) return 1;
              Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
                                                        break;

          case 'w':  
              Pr.Wyswietl(Pr);                          break;

          case 'r':  
              cout << MacierzRotacji << endl;           break;

          case 's':  
              Pr.CzyRowne();                            break;    

          case 'm':  
              menu();                                   break;

          case 'k':  
              cout << "Koniec dzialania programu\n";    break;
        }
    }
}
