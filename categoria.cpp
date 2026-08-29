#include <iostream>
#include <cstring>
#include "categoria.h"
using namespace std;

Categoria::Categoria(){
    id = 0;
    // valores por defecto para no dejarlo vacío
    strcpy(nombre, "Sin nombre");
    strcpy(descripcion, "Sin descripcion");
    activa = true;
}

void Categoria::cargar(){
    cin.ignore();

    cout << "Nombre: ";
    cin.getline(nombre, 50);

    cout << "Descripcion: ";
    cin.getline(descripcion, 100);

    activa = true;
}

void Categoria::mostrar(){
    cout << "ID: " << id << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Descripcion: " << descripcion << endl;
    cout << "Estado: " << (activa ? "ACTIVA" : "INACTIVA") << endl;
    cout << "--------------------" << endl;
}

void Categoria::setId(int i){ id = i; }
void Categoria::setNombre(const char* n){ strcpy(nombre, n); }
void Categoria::setDescripcion(const char* d){ strcpy(descripcion, d); }
void Categoria::setActiva(bool a){ activa = a; }

int Categoria::getId(){ return id; }
const char* Categoria::getNombre(){ return nombre; }
const char* Categoria::getDescripcion(){ return descripcion; }
bool Categoria::getActiva(){ return activa; }
