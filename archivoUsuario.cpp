#include <cstdio>
#include <cstring>
#include <iostream>
#include "archivoUsuario.h"
using namespace std;

ArchivoUsuario::ArchivoUsuario(const char *n){
    strcpy(nombreArchivo, n);
}

bool ArchivoUsuario::guardar(const Usuario &reg){
    FILE *p = fopen(nombreArchivo, "ab");
    if (p == nullptr) return false;

    Usuario regConId = reg;

    int nuevoId = contarRegistros() + 1;
    regConId.setId(nuevoId);

    bool ok = fwrite(&regConId, sizeof(Usuario), 1, p);
    fclose(p);
    return ok;
}

bool ArchivoUsuario::leer(Usuario &reg, int pos){
    FILE *p = fopen(nombreArchivo, "rb");
    if (!p) return false;

    // voy  a la posición
    fseek(p, pos * sizeof(Usuario), SEEK_SET);

    bool ok = fread(&reg, sizeof(Usuario), 1, p);
    fclose(p);

    return ok;
}

int ArchivoUsuario::contarRegistros(){
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return 0;

    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);

    fclose(p);
    return bytes / sizeof(Usuario);
}

void ArchivoUsuario::listarRegistros() {
    Usuario reg;
    FILE* p = fopen(nombreArchivo, "rb");
    if (p == nullptr) {
        cout << "error al abrir el archivo" << endl;
        return;
    }

    cout << "-----LISTADO DE USUARIOS-----" << endl;

    while (fread(&reg, sizeof(Usuario), 1, p) == 1) {
        if (reg.getActivo()) {
            reg.mostrar();
        }
    }

    fclose(p);
}

int ArchivoUsuario::buscarPorId(int id){
    Usuario reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return -1;

    int pos = 0;

    while (fread(&reg, sizeof(Usuario), 1, p)){
        if (reg.getId() == id){
            fclose(p);
            return pos;
        }
        pos++;
    }

    fclose(p);
    return -1;
}

int ArchivoUsuario::buscarPorNombre(const char *n){
    Usuario reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return -1;

    int pos = 0;

    while (fread(&reg, sizeof(Usuario), 1, p)){
        if (strcmp(reg.getNombre(),n) == 0){
            fclose(p);
            return pos;
        }
        pos++;
    }

    fclose(p);
    return -1;
}

bool ArchivoUsuario::modificar(const Usuario &reg, int pos){
    FILE *p = fopen(nombreArchivo, "rb+");
    if (!p) return false;

    fseek(p, pos * sizeof(Usuario), SEEK_SET);

    bool ok = fwrite(&reg, sizeof(Usuario), 1, p);
    fclose(p);

    return ok;
}

bool ArchivoUsuario::bajaLogica(int id){
    int pos = buscarPorId(id);
    if (pos < 0) return false;

    Usuario reg;

    // levanto el usuario antes de modificarlo
    if (!leer(reg, pos)) return false;

    reg.setActivo(false);

    return modificar(reg, pos);
}

bool ArchivoUsuario::cambiarPassword(int id){

}
