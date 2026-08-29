#include <iostream>
#include "fecha.h"
using namespace std;


Fecha::Fecha(int d, int m, int a) {
    setDia(d);
    setMes(m);
    setAnio(a);
}

void Fecha::cargar() {
    int d, m, a;
    cout << "Dia: ";
    cin >> d;
    setDia(d);

    cout << "Mes: ";
    cin >> m;
    setMes(m);

    cout << "Anio: ";
    cin >> a;
    setAnio(a);
}

void Fecha::mostrar() {
    cout << dia << "/" << mes << "/" << anio << endl;
}

void Fecha::setDia(int d) {
    if (d >= 1 && d <= 31) {
        dia = d;
    } else {
        dia = 1;
    }
}

void Fecha::setMes(int m) {
    if (m >= 1 && m <= 12) {
        mes = m;
    } else {
        mes = 1;
    }
}

void Fecha::setAnio(int a) {
    if (a > 1900) {
        anio = a;
    } else {
        anio = 1900;
    }
}

int Fecha::getDia() { return dia; }
int Fecha::getMes() { return mes; }
int Fecha::getAnio() { return anio; }
