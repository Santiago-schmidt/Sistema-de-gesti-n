#include <iostream>
#include <cstring>
#include "Cliente.h"
using namespace std;

// getters
int Cliente::getIdCliente(){ return idCliente; }
const char* Cliente::getNombre(){ return nombre; }
const char* Cliente::getApellido(){ return apellido; }
const char* Cliente::getDni(){ return dni; }
const char* Cliente::getTelefono(){ return telefono; }
const char* Cliente::getEmail(){ return email; }
bool Cliente::getActivo(){ return activo; }


// setters
void Cliente::setIdCliente(int id){ idCliente = id; }
void Cliente::setNombre(const char* n){ strcpy(nombre, n); }
void Cliente::setApellido(const char* a){ strcpy(apellido, a); }
void Cliente::setDni(const char* d){ strcpy(dni, d); }
void Cliente::setTelefono(const char* t){ strcpy(telefono, t); }
void Cliente::setEmail(const char* e){ strcpy(email, e); }
void Cliente::setActivo(bool a){ activo = a; }


void Cliente::cargar(){
    cin.ignore();

    cout << "Nombre: " << endl;
    cin >> nombre;

    cout << "Apellido: " << endl;
    cin >> apellido;

    cout << "DNI: " << endl;
    cin >> dni;

    cout << "Telefono: " << endl;
    cin >> telefono;

    cout << "Email: " << endl;
    cin >> email;

    activo = true;
}

void Cliente::mostrar(){
    if (!activo) return;   // si está dado de baja no muestro nada

    cout << "-----------------------------\n";
    cout << "ID: " << idCliente << endl;
    cout << "Nombre: " << nombre << " " << apellido << endl;
    cout << "DNI: " << dni << endl;
    cout << "Telefono: " << telefono << endl;
    cout << "Email: " << email << endl;
    cout << "Activo: " << (activo ? "SI" : "NO") << endl;
}
