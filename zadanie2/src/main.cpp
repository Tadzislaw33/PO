#include "BazaTestu.hh"
#include "Statystyka.hh"

int main(int argc, char **argv){
/*
  LZespolona skl1,skl2;
  cin >> skl1;
  cin >> skl2;
  skl1 += skl2;
  cout << skl1 << endl;
*/
  StatystykaTest stat;

  stat.inicjalizuj();

  if (argc < 2) {
    cout << endl;
    cout << " Brak opcji okreslajacej rodzaj testu." << endl;
    cout << " Dopuszczalne nazwy to:  latwy, trudny." << endl;
    cout << endl;
    return 1;
  }

  BazaTestu   BazaT = {0};

  if (BazaT.InicjalizujTest(argv[1]) == false) {
    cerr << " Inicjalizacja testu nie powiodla sie." << endl;
    return 1;
  }

  cout << endl;
  cout << " Start testu arytmetyki zespolonej: " << argv[1] << endl;
  cout << endl;

  WyrazenieZesp   WyrZ_PytanieTestowe;
  LZespolona  LZesp_Odpowiedz;
  
  while (BazaT.PobierzNastpnePytanie(&WyrZ_PytanieTestowe)) {
    
    cout << "\n Podaj wynik operacji: " << WyrZ_PytanieTestowe << " =" << endl;
    cout << " Twoja odpowiedz: ";
    cin >> LZesp_Odpowiedz;
   
    while(cin.fail()){
      
      cout << "\n Blad zapisu liczby zespolonej. Sprobuj jeszcze raz.\n\n";
      cin.clear();
      cin.ignore(1000,'\n');
      cout << " Twoja odpowiedz: ";
      cin >> LZesp_Odpowiedz;
    }

    if(WyrZ_PytanieTestowe.Oblicz()==LZesp_Odpowiedz){
      cout << "\n Odpowiedz poprawna.\n";
      stat.dodaj_poprawna();
    }
      else{
        cout << " Blad. Prawidlowym wynikiem jest: " << WyrZ_PytanieTestowe.Oblicz() << endl;
        stat.dodaj_niepoprawna();
      }
  }
  cout << endl;
  cout << " Koniec testu" << endl;
  cout << endl;

  stat.Wyswietl();
}
