#include "Venta.h"
#include "ArchivoCliente.h"
#include "ArchivoUsuario.h"
#include <iostream>
using namespace std;

Venta::Venta(){
    idVenta = 0;
    idCliente = 0;
    idUsuario = 0;
    Fecha fechaDeVenta;
    total = 0.0f;
    anulada = false;
}

int Venta::getIdVenta(){ return idVenta; }
int Venta::getIdCliente(){ return idCliente; }
int Venta::getIdUsuario(){ return idUsuario; }
Fecha Venta::getFecha(){ return fecha; }
float Venta::getTotal(){ return total; }
bool Venta::getAnulada(){ return anulada; }

void Venta::setIdVenta(int id){ idVenta = id; }
void Venta::setIdCliente(int idCli){ idCliente = idCli; }
void Venta::setIdUsuario(int idUsu){ idUsuario = idUsu; }
void Venta::setFecha(Fecha f){ fecha = f; }
void Venta::setTotal(float t){ total = t; }
void Venta::setAnulada(bool estado){ anulada = estado; }


// muestra  venta con datos del cliente y usuario
void Venta::mostrar(){
    ArchivoCliente archCli("clientes.dat");
    ArchivoUsuario archUsu("usuarios.dat");

    cout << "================================" << endl;
    cout << "ID Venta: " << idVenta << endl;

    int posCliente = archCli.buscarPorId(idCliente);
    if(posCliente != -1){
        Cliente cli = archCli.leerRegistro(posCliente);
        cout << "Cliente: " << cli.getNombre() << " " << cli.getApellido() << endl;
        cout << "DNI: " << cli.getDni() << endl;
    } else {
        cout << "ID Cliente: " << idCliente << " (No encontrado)" << endl;
    }

    // info del usuario  vendedor
    int posUsuario = archUsu.buscarPorId(idUsuario);
    if(posUsuario != -1){
        Usuario u;
        archUsu.leer(u, posUsuario);
        cout << "Vendedor: " << u.getNombre() << endl;
    } else {
        cout << "ID Usuario: " << idUsuario << " (No encontrado)" << endl;
    }

    cout << "Fecha: ";
    fecha.mostrar();

    cout << "Total: $" << total << endl;
    cout << "Estado: " << (anulada ? "ANULADA" : "ACTIVA") << endl;
    cout << "================================" << endl;
}
