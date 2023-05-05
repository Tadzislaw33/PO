#include "Scena.hh"
#include "Macierz3x3.hh"

Macierz3x3 Rotacja::UstawObrot(char os, double kat){

    Macierz3x3 Tab;

    switch(os){

        case 'x':

            Tab(0,0) = cos(kat*M_PI/180);
            Tab(0,1) = -sin(kat*M_PI/180);
            Tab(0,2) = 0;
            Tab(1,0) = sin(kat*M_PI/180);
            Tab(1,1) = cos(kat*M_PI/180);
            Tab(1,2) = 0;
            Tab(2,0) = 0;
            Tab(2,1) = 0;
            Tab(2,2) = 1;

        break;

        case 'y':

            Tab(0,0) = cos(kat*M_PI/180);
            Tab(0,1)  = 0;
            Tab(0,2) = sin(kat*M_PI/180);
            Tab(1,0) = 0;
            Tab(1,1) = 1;
            Tab(1,2) = 0;
            Tab(2,0) = -sin(kat*M_PI/180);
            Tab(2,1) = 0;
            Tab(2,2) = cos(kat*M_PI/180);

        break;

        case 'z':

            Tab(0,0) = 1;
            Tab(0,1) = 0;
            Tab(0,2) = 0;
            Tab(1,0) = 0;
            Tab(1,1) = cos(kat*M_PI/180);
            Tab(1,2) = -sin(kat*M_PI/180);
            Tab(2,0) = 0;
            Tab(2,1) = sin(kat*M_PI/180);
            Tab(2,2) = cos(kat*M_PI/180);

        break;
    }
    return Tab;
}

Macierz3x3 Rotacja::UstawObrotKoncowy(vector<Rotacja> lista_rotacji){

    Macierz3x3 macierz_koncowa;

        for(unsigned int ind=0; ind<lista_rotacji.size(); ++ind){

            Rotacja rot_tmp = lista_rotacji[ind];
            macierz_koncowa = macierz_koncowa * UstawObrot(rot_tmp.os, rot_tmp.kat);
        }
        return macierz_koncowa;
}

void Rotacja::Obrot(){
    
    vector<Rotacja> lista_rotacji;
    Prostopadloscian wierzcholki;

    for(int i=0; i<LICZBA_WIERZCHOLKOW; i++){
        wierzcholki[i] = UstawObrotKoncowy(lista_rotacji) * wierzcholki[i];
    }
}
