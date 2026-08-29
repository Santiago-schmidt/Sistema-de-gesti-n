#ifndef VENTA_H
#define VENTA_H

#include "Fecha.h"

class Venta {
private:
    int idVenta;
    int idCliente;
    int idUsuario;
    Fecha fecha;
    float total;
    bool anulada;

public:
    // Constructor
    Venta();

    // Getters
    int getIdVenta();
    int getIdCliente();
    int getIdUsuario();
    Fecha getFecha();
    float getTotal();
    bool getAnulada();

    // Setters
    void setIdVenta(int id);
    void setIdCliente(int idCli);
    void setIdUsuario(int idUsu);
    void setFecha(Fecha f);
    void setTotal(float t);
    void setAnulada(bool estado);

    // Métodos
    void mostrar();
};

#endif
