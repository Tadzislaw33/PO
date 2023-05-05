#ifndef STATYSTYKATESTU_HH
#define STATYSTYKATESTU_HH

#include <iostream>

struct StatystykaTest{
    int l_poprawnych;
    int l_niepoprawnych;

    void Wyswietl();
    double Oblicz();
    void dodaj_poprawna();
    void dodaj_niepoprawna();
    void inicjalizuj(); 
};

#endif