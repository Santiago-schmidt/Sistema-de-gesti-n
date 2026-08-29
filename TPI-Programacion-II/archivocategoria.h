#ifndef ARCHIVOCATEGORIA_H_INCLUDED
#define ARCHIVOCATEGORIA_H_INCLUDED
#include "categoria.h"

class ArchivoCategoria{
private:
    char nombreArchivo [50];
public:
    ArchivoCategoria (const char* nombre);
    bool guardar (Categoria reg);
    Categoria leer (int pos);
    bool modificarCategoria(Categoria reg, int pos);
    void listarCategorias();
    int getCantidadRegistros();
    bool bajaLogica(int id);
    bool altaLogica(int id);
    bool categoriaExiste (int id);
    int buscarPorId(int id);
};


#endif // ARCHIVOCATEGORIA_H_INCLUDED
