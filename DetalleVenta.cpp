#include "DetalleVenta.h"
#include "ArchivoItem.h"
#include <iostream>
using namespace std;

DetalleVenta::DetalleVenta(){
    idDetalle = 0;
    idVenta = 0;
    idItem = 0;
    cantidad = 0;
    precioUnitario = 0.0f;
}

int DetalleVenta::getIdDetalle(){ return idDetalle; }
int DetalleVenta::getIdVenta(){ return idVenta; }
int DetalleVenta::getIdItem(){ return idItem; }
int DetalleVenta::getCantidad(){ return cantidad; }
float DetalleVenta::getPrecioUnitario(){ return precioUnitario; }

void DetalleVenta::setIdDetalle(int id){ idDetalle = id; }
void DetalleVenta::setIdVenta(int idV){ idVenta = idV; }
void DetalleVenta::setIdItem(int idI){ idItem = idI; }
void DetalleVenta::setCantidad(int cant){ cantidad = cant; }
void DetalleVenta::setPrecioUnitario(float precio){ precioUnitario = precio; }


void DetalleVenta::mostrar(){
    ArchivoItem archItem("items.dat");   // uso el archivo para buscar info del item

    cout << "----------------------------" << endl;

    int posItem = archItem.buscarPorId(idItem);

    if (posItem != -1){
        Item item = archItem.leer(posItem);
        cout << "Producto: " << item.getNombre() << endl;
        cout << "Codigo: " << item.getCodigo() << endl;
        cout << "Precio Unit: $" << precioUnitario << endl;
        cout << "Cantidad: " << cantidad << endl;
    } else {
        cout << "ID Item: " << idItem << " (No encontrado)" << endl;
        cout << "Cantidad: " << cantidad << endl;
        cout << "Precio Unit: $" << precioUnitario << endl;
    }

    cout << "----------------------------" << endl;
}
