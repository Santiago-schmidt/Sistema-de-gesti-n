#ifndef ARCHIVOVENTA_H
#define ARCHIVOVENTA_H

#include "Venta.h"
#include "fecha.h"

class ArchivoVenta {
private:
    char nombreArchivo[30];

public:
    // Constructor
    ArchivoVenta(const char* nombre = "ventas.dat");

    // Métodos de archivo básicos
    bool guardar(Venta reg);
    Venta leer(int pos);
    int contarRegistros();
    void listar();
    void listarPorFecha(Fecha desde, Fecha hasta);
    int buscarPorId(int id);
    bool modificar(Venta reg, int pos);

    // FUNCIÓN PRINCIPAL: Registrar una venta completa
    void registrarVenta();

    // INFORMES
    void informeTotalRecaudado();
    void informeVentasPorCliente();
    void informeTopProductos();
};

#endif
