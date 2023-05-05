#include "Prostopadloscian.hh"
#include "Macierz3x3.hh"

Prostopadloscian::Prostopadloscian(){

    KatOrientacji_stopnie = 0;
    Polozenie = {0,0,0};
    for(int i=0; i<16; i++)
    {
        Wierzcholek[i] = {0,0,0};
    }
}


Prostopadloscian::Prostopadloscian(Wektor3D Polozenie, double KatOrientacji_stopnie, string NazwaBryly){

    ofstream StrmPlikowy;
    StrmPlikowy.open("../bryly_wzorcowe/prostopadloscian.dat");
    for(int i=0; i<16; ++i){
        StrmPlikowy << Wierzcholek[i];
    }
    (*this).Obrot(KatOrientacji_stopnie);
    (*this).Translacja(Polozenie);

    string NazwaPlikuBryla = NazwaBryly + ".dat";
    StrmPlikowy.close();
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

Prostopadloscian& Prostopadloscian::Obrot(double Kat){

    Macierz3x3 Rotacja;
    for(int i=0; i<LICZBA_WIERZCHOLKOW; ++i){
        (*this)[i] = Rotacja.UstawObrot(Kat) * (*this)[i];
    }
    return (*this);
}

Prostopadloscian& Prostopadloscian::Translacja(Wektor3D &Wek){

    for(int i=0; i<LICZBA_WIERZCHOLKOW; ++i){
        (*this)[i] = (*this)[i] + Wek; 
    }
    return (*this);
}

const Wektor3D Prostopadloscian::TransfDoUklWsprodzica(Wektor3D &Wsp){

    (*this).Translacja(Polozenie);
    (*this).Obrot(KatOrientacji_stopnie*-1);
    
    return Wsp;
}
