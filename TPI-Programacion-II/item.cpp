#include "Item.h"
#include "archivocategoria.h"
#include <iostream>
#include <cstring>
using namespace std;

Item::Item(){

    idItem = 0;
    strcpy(codigo, "");
    strcpy(nombre, "");
    strcpy(descripcion, "");
    idCategoria = 0;
    precioCosto = 0.0;
    precioVenta = 0.0;
    stockActual = 0;
    stockMinimo = 0;
    activo = true;
}

int Item::getIdItem(){ return idItem; }
const char* Item::getCodigo(){ return codigo; }
const char* Item::getNombre(){ return nombre; }
const char* Item::getDescripcion(){ return descripcion; }
int Item::getIdCategoria(){ return idCategoria; }
float Item::getPrecioCosto(){ return precioCosto; }
float Item::getPrecioVenta(){ return precioVenta; }
int Item::getStockActual(){ return stockActual; }
int Item::getStockMinimo(){ return stockMinimo; }
bool Item::getActivo(){ return activo; }

void Item::setIdItem(int id){ idItem = id; }
void Item::setCodigo(const char* cod){ strcpy(codigo, cod); }
void Item::setNombre(const char* nom){ strcpy(nombre, nom); }
void Item::setDescripcion(const char* desc){ strcpy(descripcion, desc); }
void Item::setIdCategoria(int idCat){ idCategoria = idCat; }
void Item::setPrecioCosto(float precio){ precioCosto = precio; }
void Item::setPrecioVenta(float precio){ precioVenta = precio; }
void Item::setStockActual(int stock){ stockActual = stock; }
void Item::setStockMinimo(int stockMin){ stockMinimo = stockMin; }
void Item::setActivo(bool estado){ activo = estado; }


void Item::cargar(){
    cout << "\n================================" << endl;
    cout << "       CARGAR NUEVO ITEM        " << endl;
    cout << "================================" << endl;

    cin.ignore();

    cout << "Ingrese codigo: ";
    cin.getline(codigo, 20);

    cout << "Ingrese nombre: ";
    cin.getline(nombre, 50);

    cout << "Ingrese descripcion: ";
    cin.getline(descripcion, 60);

    cout << "Ingrese precio de costo: ";
    cin >> precioCosto;

    cout << "Ingrese precio de venta: ";
    cin >> precioVenta;

    cout << "Ingrese stock actual: ";
    cin >> stockActual;

    cout << "Ingrese stock minimo: ";
    cin >> stockMinimo;

    ArchivoCategoria archCat("categorias.dat");

    cout << "Ingrese ID de categoria: ";
    cin >> idCategoria;

    // chequeo de categoria
    while(!archCat.categoriaExiste(idCategoria)){
        cout << "Categoria inexistente. Ingrese nuevamente: ";
        cin >> idCategoria;
    }

    activo = true;
    cout << "================================" << endl;
}

void Item::mostrar(){
    cout << "================================" << endl;
    cout << "ID Item: " << idItem << endl;
    cout << "Codigo: " << codigo << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Descripcion: " << descripcion << endl;
    cout << "ID Categoria: " << idCategoria << endl;
    cout << "Precio Costo: $" << precioCosto << endl;
    cout << "Precio Venta: $" << precioVenta << endl;
    cout << "Stock Actual: " << stockActual << endl;
    cout << "Stock Minimo: " << stockMinimo << endl;
    cout << "Estado: " << (activo ? "Activo" : "Inactivo") << endl;
    cout << "================================" << endl;
}
