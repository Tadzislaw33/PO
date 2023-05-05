#include "Dron.hh"
#include "Macierz3x3.hh"


Dron::Dron(){
  
  KorpusDrona = Prostopadloscian();
  for(int i=0; i<=4; ++i){
    RotorDrona[i] = Graniastoslup6();
  }
}


Dron::Dron(const string &SciezkaDoFolderu, double KatSkretu_stopnie,const Wektor3D &Polozenie){

  string SciezkaDrona = SciezkaDoFolderu + "Dron" + to_string(IdDrona) + "_";
  for(int i=1;i<4;++i){
    string SciezkaRotora = SciezkaDrona + "rotor" + to_string(i) + ".dat";
  }
  string SciezkaKorpusu = SciezkaDrona + "korpus.dat";
  
}

const Wektor3D Dron::TransfDoUklWsprodzica(const Wektor3D &Wierzcholki){
    
  KorpusDrona.Translacja((Polozenie));
  RotorDrona[0].Translacja((Polozenie));
  RotorDrona[1].Translacja((Polozenie));
  RotorDrona[2].Translacja((Polozenie));
  RotorDrona[3].Translacja((Polozenie));
  KorpusDrona.Obrot(KatOrientacji_stopnie*-1);
  RotorDrona[0].Obrot(KatOrientacji_stopnie*-1);
  RotorDrona[1].Obrot(KatOrientacji_stopnie*-1);
  RotorDrona[2].Obrot(KatOrientacji_stopnie*-1);
  RotorDrona[3].Obrot(KatOrientacji_stopnie*-1);

}  


bool Dron::PlanujPoczatkowaSciezke(double KatSkretu_stopnie, double DlugoscLotu, vector<Wektor3D> &PunktySciezki){

  Macierz3x3 Obrot;
  Wektor3D PunktySciezki[3] = Obrot.UstawObrot(KatSkretu_stopnie) * Wektor3D{DlugoscLotu,0,0}; 

  ofstream StrmPlikowy;
  StrmPlikowy.open("../dat/trasa_przelotu.dat");
  if (!StrmPlikowy.is_open()){
    cerr << "Operacja otwarcia do zapisu pliku trasa_przelotu.dat nie powiodla sie." << endl;
    return false;
  }

  StrmPlikowy << PunktySciezki[0] << endl
	            << PunktySciezki[1] << endl
              << PunktySciezki[2] << endl
              << PunktySciezki[3] << endl;
  Lacze.DodajNazwePliku("../dat/trasa_przelotu.dat");
  return !StrmPlikowy.fail();
}


bool Dron::WykonajPionowylot(double DlugoscLotu, PzG::LaczeDoGNUPlota &Lacze){

  Wektor3D Przesuniecie{0,0,DlugoscLotu};
  KorpusDrona.Translacja(Przesuniecie);
  RotorDrona[0].Translacja(Przesuniecie);
  RotorDrona[1].Translacja(Przesuniecie);
  RotorDrona[2].Translacja(Przesuniecie);
  RotorDrona[3].Translacja(Przesuniecie);
  //(*this).ObliczPolozenie();
  /*Lacze
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
  Wsp[2] -= 2;*/

}


bool Dron::WykonajPoziomylot(double DlugoscLotu, PzG::LaczeDoGNUPlota &Lacze){
    
  Wektor3D Przesuniecie{DlugoscLotu,0,0};
  Macierz3x3 Obrot;
  Przesuniecie = Obrot.UstawObrot(KatOrientacji_stopnie) * Przesuniecie;
  KorpusDrona.Translacja(Przesuniecie);
  RotorDrona[0].Translacja(Przesuniecie);
  RotorDrona[1].Translacja(Przesuniecie);
  RotorDrona[2].Translacja(Przesuniecie);
  RotorDrona[3].Translacja(Przesuniecie);
  //(*this).ObliczPolozenie();
  
}


const bool Dron::Oblicz_i_Zapisz_WspGlbKorpusu(Prostopadloscian &KorpusDrona){
    
  ifstream  Plik_BrylaWzorcowa;
  ofstream  Plik_BrylaFinalna;
  int LicznikWierzcholkow=0;

  Plik_BrylaWzorcowa.open("../bryly_wzorcowe/prostopadloscian.dat");
  if (!Plik_BrylaWzorcowa.is_open()) {
    cerr << endl << " Blad otwarcia do odczytu pliku: prostopadloscian.dat" << endl << endl;
    return false;
  }

  Plik_BrylaFinalna.open("../bryly_finalne/prostopadloscian.dat");
  if (!Plik_BrylaFinalna.is_open()) {
    cerr << endl << " Blad otwarcia do odczytu pliku: prostopadloscian.dat" << endl << endl;
    return false;
  }

  Wektor3D Wierzcholki;
  BrylaGeometryczna Bryla;

  while (LicznikWierzcholkow<5){

    Plik_BrylaWzorcowa >> Wierzcholki[LicznikWierzcholkow];
    Bryla.Skaluj(Wierzcholki);
    KorpusDrona.TransfDoUklWsprodzica(Wierzcholki);
    (*this).TransfDoUklWsprodzica(Wierzcholki);
    Plik_BrylaFinalna << Wierzcholki[LicznikWierzcholkow];
    ++LicznikWierzcholkow;
  }
  Plik_BrylaFinalna << endl;

  Plik_BrylaWzorcowa.close();
  Plik_BrylaFinalna.close();

}


const bool Dron::Oblicz_i_Zapisz_WspGlbRotora(Graniastoslup6 &RotorDrona){
    
  ifstream  Plik_BrylaWzorcowa;
  ofstream  Plik_BrylaFinalna;
  int LicznikWierzcholkow=0;

  Plik_BrylaWzorcowa.open("./bryly_wzorcowe/graniastoslup6.dat");
  if (!Plik_BrylaWzorcowa.is_open()) {
    cerr << endl << " Blad otwarcia do odczytu pliku: graniastoslup6.dat" << endl << endl;
    return false;
  }

  Plik_BrylaFinalna.open("./bryly_finalne/graniastoslup6.dat");
  if (!Plik_BrylaFinalna.is_open()) {
    cerr << endl << " Blad otwarcia do odczytu pliku: graniastoslup6.dat" << endl << endl;
    return false;
  }

  Wektor3D Wierzcholki;
  BrylaGeometryczna Bryla;

  while (LicznikWierzcholkow<7){

    Plik_BrylaFinalna << Wierzcholki[LicznikWierzcholkow];
    Bryla.Skaluj(Wierzcholki);
    KorpusDrona.TransfDoUklWsprodzica(Wierzcholki);
    (*this).TransfDoUklWsprodzica(Wierzcholki);
    Plik_BrylaFinalna << Wierzcholki[LicznikWierzcholkow];
    ++LicznikWierzcholkow;
  }
  Plik_BrylaFinalna << endl;

  Plik_BrylaWzorcowa.close();
  Plik_BrylaFinalna.close();

}


const bool Dron::Oblicz_i_Zapisz_WspGlbDrona(){
    
  (*this).Oblicz_i_Zapisz_WspGlbKorpusu(KorpusDrona);
  for(int i=0; i<=4; ++i){
    (*this).Oblicz_i_Zapisz_WspGlbRotora(RotorDrona[i]);
  }
}