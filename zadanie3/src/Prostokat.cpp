#include "Prostokat.hh"
#include "Macierz2x2.hh"

/*
 *  Przesuwa prostokat o podany wektor.
 *  Argumenty:
 *      Wek - wektor o ktory przesuniemy prostokat. 
 */
void Prostokat::PrzesunOWektor(const Wektor2D &Wek){

    for(int i=0; i<LICZBA_WIERZCHOLKOW; i++){
        wierzcholki[i] = wierzcholki[i] + Wek;
    }
}

/*
 *  Obraca prostokat o zadany kat.
 *  Argumenty:
 *      Kat - kat o jaki chcemy obrocic prostokat. 
 */
void Prostokat::Rotacja(const double Kat){

    Macierz2x2 Mac;
    Mac.MacierzRotacji(Kat);
    for(int i=0; i<LICZBA_WIERZCHOLKOW; i++){
        wierzcholki[i] = Mac * wierzcholki[i];
    }
}

/*
 *  Wyswietla wspolrzedne wierzcholkow na stdout.
 *  Argumenty:
 *      Pr - Prostokat. 
 */
void Prostokat::Wyswietl(const Prostokat &Pr){

    for (int i=0; i < LICZBA_WIERZCHOLKOW; ++i)
    {
        cout << setw(16) << fixed << setprecision(10) << Pr[i] << "   " << endl; 
    }
}

/*
 *  Przeciazenie operatora przesuniecia bitowego w lewo.
 *  Argumenty:
 *      Sout - strumien wyjsciowy.
 *      Pr - Prostokat. 
 */
ostream &operator << (ostream &Sout, const Prostokat &Pr){

    Wektor2D  tmp;
    for (int i=0;i<LICZBA_WIERZCHOLKOW;i++)
	{
		tmp=Pr[i];
		Sout << tmp << endl;
	}
	return Sout;
}

/*
 *  Porownuje dlugosc bokow prostokata i je wyswietla. 
 */
void Prostokat::CzyRowne(){
    
    double pierwszy, drugi, trzeci, czwarty;
    pierwszy = DlugoscBoku(wierzcholki[0],wierzcholki[1]);
    drugi = DlugoscBoku(wierzcholki[3],wierzcholki[2]);
    trzeci = DlugoscBoku(wierzcholki[0],wierzcholki[3]);
    czwarty = DlugoscBoku(wierzcholki[1],wierzcholki[2]);

    if(pierwszy==drugi){
        cout << "\nJedne przeciwlegle boki sa sobie rowne." << endl;
		cout << "Dlugosc pierwszego boku: " << fixed << setprecision(16) << pierwszy << endl;
		cout << "  Dlugosc drugiego boku: " << fixed << setprecision(16) << drugi << endl << endl;
    }
        else
        {
        cout << "\nJedne przeciwlegle boki nie sa sobie rowne." << endl;
		cout << "Dlugosc pierwszego boku: " << fixed << setprecision(16) << pierwszy << endl;
		cout << "  Dlugosc drugiego boku: " << fixed << setprecision(16) << drugi << endl << endl;
        }

    if(trzeci==czwarty){
        cout << "\nDrugie przeciwlegle boki sa sobie rowne." << endl;
		cout << "Dlugosc pierwszego boku: " << fixed << setprecision(16) << trzeci << endl;
		cout << "  Dlugosc drugiego boku: " << fixed << setprecision(16) << czwarty << endl << endl; 
    }
        else
        {
        cout << "\nDrugie przeciwlegle boki nie sa sobie rowne." << endl;
		cout << "Dlugosc pierwszego boku: " << fixed << setprecision(16) << trzeci << endl;
		cout << "  Dlugosc drugiego boku: " << fixed << setprecision(16) << czwarty << endl << endl;
        }
}

 
