#include "Prostopadloscian.hh"

/*!
 * \brief Przesuwa prostopadloscian o podany wektor.
 *
 * \param[in] Wek - wektor o ktory przesuniemy prostopadloscian.
 * 
 */
void Prostopadloscian::PrzesunOWektor(const Wektor3D &Wek){

    for(int i=0; i<LICZBA_WIERZCHOLKOW; ++i){
        wierzcholki[i] = wierzcholki[i] + Wek;
    }
}

/*!
 * \brief Wyswietla wspolrzedne wierzcholkow na stdout.
 *
 * \param[in] Pr - Prostopadloscian.
 * 
 */
void Prostopadloscian::Wyswietl(const Prostopadloscian &Pr){

    for (int i=0; i < LICZBA_WIERZCHOLKOW; ++i)
    {
        cout << setw(16) << fixed << setprecision(10) << Pr[i] << endl; 
    }
}

/*!
 * \brief Przeciazenie operatora przesuniecia bitowego w lewo.
 *
 * \param[in] Sout - strumien wyjsciowy.
 * \param[in] Pr - Prostopadloscian.
 * 
 */
ostream &operator << (ostream &Sout, const Prostopadloscian &Pr){

    Wektor3D  tmp;
    for (int i=0;i<LICZBA_WIERZCHOLKOW;++i)
	{
		tmp=Pr[i];
		Sout << tmp << endl;
        if(i%2==1) Sout << endl;
	}
	return Sout;
}


