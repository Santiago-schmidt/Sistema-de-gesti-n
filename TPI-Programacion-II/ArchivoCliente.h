#ifndef ARCHIVOCLIENTE_H_INCLUDED
#define ARCHIVOCLIENTE_H_INCLUDED

#include "Cliente.h"

class ArchivoCliente {
private:
    char nombreArchivo[30];
public:
    ArchivoCliente(const char* n);
    bool grabarRegistro(Cliente reg);
    Cliente leerRegistro(int pos);
    int buscarPorDNI(const char* dniBuscado);
    int buscarPorId(int id);
    bool modificarRegistro(Cliente reg, int pos);
    void listarActivos();
    void listarInactivos();
    int contarRegistros();

    bool bajaLogica(int pos);
    bool altaLogica(int pos);

    int buscarPorApellido(const char* ape);
    bool modificarClientePorID(int id);
};

#endif // ARCHIVOCLIENTE_H_INCLUDED
