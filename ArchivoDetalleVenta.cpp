#include "ArchivoDetalleVenta.h"
#include "ArchivoItem.h"
#include "ArchivoVenta.h"
#include "ArchivoCliente.h"
#include "archivoUsuario.h"
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

ArchivoDetalleVenta::ArchivoDetalleVenta(const char* nombre){
   strcpy(nombreArchivo, nombre);
}

bool ArchivoDetalleVenta::guardar(DetalleVenta reg){
    FILE* p = fopen(nombreArchivo, "ab");
    if(p == nullptr) return false;
    bool escribio = fwrite(&reg, sizeof(DetalleVenta), 1, p);
    fclose(p);
    return escribio;
}

// leer x posicion
DetalleVenta ArchivoDetalleVenta::leer(int pos){
    DetalleVenta r;
    FILE* p = fopen(nombreArchivo, "rb");
    if(!p) return r;
    fseek(p, pos * sizeof(DetalleVenta), SEEK_SET);
    fread(&r, sizeof(DetalleVenta), 1, p);
    fclose(p);
    return r;
}

int ArchivoDetalleVenta::contarRegistros(){
    FILE* p = fopen(nombreArchivo, "rb");
    if(p == nullptr) return 0;
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(DetalleVenta);
}

void ArchivoDetalleVenta::listar(){
    DetalleVenta reg;
    ArchivoVenta archVenta("ventas.dat");
    ArchivoCliente archCli("clientes.dat");
    ArchivoUsuario archUsu("usuarios.dat");
    int cant = contarRegistros();

    cout << "\n================================================" << endl;
    cout << "     LISTADO COMPLETO DE DETALLES DE VENTAS    " << endl;
    cout << "================================================" << endl;

    for(int i = 0; i < cant; i++){
        reg = leer(i);

        int posVenta = archVenta.buscarPorId(reg.getIdVenta());
        if(posVenta != -1){
            Venta venta = archVenta.leer(posVenta);

            cout << "\n--- VENTA #" << reg.getIdVenta() << " ---" << endl;

            int posCliente = archCli.buscarPorId(venta.getIdCliente());
            if(posCliente != -1){
                Cliente cli = archCli.leerRegistro(posCliente);
                cout << "Cliente: " << cli.getNombre() << " " << cli.getApellido() << endl;
            }

            int posUsuario = archUsu.buscarPorId(venta.getIdUsuario());
            if(posUsuario != -1){
                Usuario usu;
                archUsu.leer(usu, posUsuario);
                cout << "Vendedor: " << usu.getNombre() << endl;
            }

            cout << "Fecha: ";
            venta.getFecha().mostrar();
        }

        reg.mostrar();
        cout << "================================================" << endl;
    }
}

void ArchivoDetalleVenta::listarPorVenta(int idVenta){
    DetalleVenta d;
    ArchivoVenta archVenta("ventas.dat");
    ArchivoCliente archCli("clientes.dat");
    ArchivoUsuario archUsu("usuarios.dat");
    int cant = contarRegistros();

    cout << "\n================================================" << endl;
    cout << "         DETALLE COMPLETO DE VENTA #" << idVenta << endl;
    cout << "================================================" << endl;

    int posVenta = archVenta.buscarPorId(idVenta);
    if(posVenta != -1){
        Venta venta = archVenta.leer(posVenta);

        int posCliente = archCli.buscarPorId(venta.getIdCliente());
        if(posCliente != -1){
            Cliente cli = archCli.leerRegistro(posCliente);
            cout << "\nCliente: " << cli.getNombre() << " " << cli.getApellido() << endl;
            cout << "DNI: " << cli.getDni() << endl;
        }

        int posUsuario = archUsu.buscarPorId(venta.getIdUsuario());
        if(posUsuario != -1){
            Usuario usu;
            archUsu.leer(usu, posUsuario);
            cout << "Vendedor: " << usu.getNombre() << endl;
        }

        cout << "Fecha: ";
        venta.getFecha().mostrar();
        cout << "\n--- PRODUCTOS VENDIDOS ---\n" << endl;
    }

    bool hayDetalles = false;

    for(int i = 0; i < cant; i++){
        d = leer(i);
        if(d.getIdVenta() == idVenta){
            d.mostrar();
            hayDetalles = true;
        }
    }

    if(!hayDetalles){
        cout << "   No hay detalles para esta venta." << endl;
    }
    cout << "================================================" << endl;
}

// buscar por id
int ArchivoDetalleVenta::buscarPorId(int id){
    DetalleVenta tmp;
    int cant = contarRegistros();
    for(int i = 0; i < cant; i++){
        tmp = leer(i);
        if(tmp.getIdDetalle() == id){
            return i;
        }
    }
    return -1;
}
