#include "Graniastoslup6.hh"
#include "Macierz3x3.hh"

Graniastoslup6::Graniastoslup6(){
    
    KatOrientacji_stopnie=0;
    Polozenie={0,0,0};
    for(int i=0; i<24; i++)
    {
        Wierzcholek[i]={0,0,0};
    }
}


Graniastoslup6::Graniastoslup6(Wektor3D Polozenie, double KatOrientacji_stopnie, string NazwaBryly){
    
    ofstream StrmPlikowy;
    StrmPlikowy.open("../bryly_wzorcowe/graniastoslup6.dat");
    for(int i=0; i<24; ++i){
        StrmPlikowy << Wierzcholek[i];
    }
    (*this).Obrot(KatOrientacji_stopnie);
    (*this).Translacja(Polozenie);

    string NazwaPlikuBryla = NazwaBryly + ".dat";
    StrmPlikowy.close();
}


Graniastoslup6& Graniastoslup6::Obrot(double Kat){

    Macierz3x3 Rotacja;
    for(int i=0; i<LICZBA_WIERZCHOLKOW_G; ++i){
        (*this)[i] = Rotacja.UstawObrot(Kat) * (*this)[i];
    }
    return (*this);
}

Graniastoslup6& Graniastoslup6::Translacja(Wektor3D &Wek){

    for(int i=0; i<LICZBA_WIERZCHOLKOW_G; ++i){
        (*this)[i] = (*this)[i] + Wek; 
    }
    return (*this);
}

const Wektor3D Graniastoslup6::TransfDoUklWsprodzica(Wektor3D &Wsp){

    (*this).Translacja(Polozenie);
    (*this).Obrot(KatOrientacji_stopnie*-1);
    
    return Wsp;
}


/*!
 * \brief Przeciazenie operatora przesuniecia bitowego w lewo.
 *
 * \param[in] Sout - strumien wyjsciowy.
 * \param[in] Gr - Wierzcholki graniastoslupa.
 * 
 */
ostream &operator << (ostream &Sout, const Graniastoslup6 &Gr){

    Wektor3D  tmp;
    for (int i=0;i<LICZBA_WIERZCHOLKOW_G;++i)
	{
		tmp=Gr[i];
		Sout << tmp << endl;
        if(i%2==1) Sout << endl;
	}
	return Sout;
}

