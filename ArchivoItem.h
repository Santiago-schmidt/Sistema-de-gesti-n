#ifndef ARCHIVOITEM_H
#define ARCHIVOITEM_H

#include "Item.h"

class ArchivoItem {
private:
    char nombre[30];

public:
    ArchivoItem(const char* n = "items.dat");

    bool guardar(Item reg);
    Item leer(int pos);
    int contarRegistros();
    void listar();
    int buscar(const char* codigo);
    bool modificar(Item reg, int pos);
    bool modificarItem(int idBuscado);
    int buscarPorId(int id);
    bool bajaLogica(int id);
    void listarBajoStock(int limite);
    void listarPorCategoria(int idCategoria);
};

#endif
