// Item.h
#ifndef ITEM_H
#define ITEM_H

class Item {
private:
    int idItem;
    char codigo[20];
    char nombre[50];
    char descripcion[60];
    int idCategoria;
    float precioCosto;
    float precioVenta;
    int stockActual;
    int stockMinimo;
    bool activo;

public:
    Item();

    // Getters
    int getIdItem();
    const char* getCodigo();
    const char* getNombre();
    const char* getDescripcion();
    int getIdCategoria();
    float getPrecioCosto();
    float getPrecioVenta();
    int getStockActual();
    int getStockMinimo();
    bool getActivo();


    void setIdItem(int id);
    void setCodigo(const char* cod);
    void setNombre(const char* nom);
    void setDescripcion(const char* desc);
    void setIdCategoria(int idCat);
    void setPrecioCosto(float precio);
    void setPrecioVenta(float precio);
    void setStockActual(int stock);
    void setStockMinimo(int stockMin);
    void setActivo(bool estado);

    void mostrar();
    void cargar();
};

#endif
