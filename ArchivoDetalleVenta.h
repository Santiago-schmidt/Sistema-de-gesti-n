#ifndef ARCHIVODETALLEVENTA_H
#define ARCHIVODETALLEVENTA_H

#include "DetalleVenta.h"

class ArchivoDetalleVenta {
private:
    char nombreArchivo[30];

public:
    // Constructor
    ArchivoDetalleVenta(const char* nombre = "detalleVentas.dat");

    // Métodos de archivo
    bool guardar(DetalleVenta reg);
    DetalleVenta leer(int pos);
    int contarRegistros();
    void listar();
    void listarPorVenta(int idVenta);
    int buscarPorId(int id);
};

#endif
