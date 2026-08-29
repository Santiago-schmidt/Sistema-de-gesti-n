#ifndef DETALLEVENTA_H
#define DETALLEVENTA_H

class DetalleVenta {
private:
    int idDetalle;
    int idVenta;
    int idItem;
    int cantidad;
    float precioUnitario;

public:
    // Constructor
    DetalleVenta();

    // Getters
    int getIdDetalle();
    int getIdVenta();
    int getIdItem();
    int getCantidad();
    float getPrecioUnitario();

    // Setters
    void setIdDetalle(int id);
    void setIdVenta(int idV);
    void setIdItem(int idI);
    void setCantidad(int cant);
    void setPrecioUnitario(float precio);

    // Métodos
    void mostrar();
};

#endif
