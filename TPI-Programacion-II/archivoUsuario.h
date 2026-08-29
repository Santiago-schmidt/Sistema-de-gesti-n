#ifndef ARCHIVOUSUARIO_H_INCLUDED
#define ARCHIVOUSUARIO_H_INCLUDED

#include "usuario.h"

class ArchivoUsuario {
private:
    char nombreArchivo[30];

public:
    ArchivoUsuario(const char *n = "usuarios.dat");
    bool guardar(const Usuario &reg);
    bool leer(Usuario &reg, int pos);
    int contarRegistros();
    int buscarPorNombre(const char *n);
    bool modificar(const Usuario &reg, int pos);
    void listarRegistros();
    int buscarPorId(int id);
    bool bajaLogica(int id);
    bool cambiarPassword(int id);
};

#endif // ARCHIVOUSUARIO_H_INCLUDED
