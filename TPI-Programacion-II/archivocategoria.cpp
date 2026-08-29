#include <iostream>
#include <cstdio>
#include <cstring>
#include "archivocategoria.h"
using namespace std;

ArchivoCategoria::ArchivoCategoria(const char* nombre) {
    // guardo el nombre del archivo
    strcpy(nombreArchivo, nombre);
}

bool ArchivoCategoria::guardar(Categoria reg) {
    FILE* p = fopen(nombreArchivo, "ab");
    if (p == nullptr) {
        return false;
    }

    int nuevoId = getCantidadRegistros() + 1;   // le asigno id nuevo
    reg.setId(nuevoId);

    bool escribio = fwrite(&reg, sizeof(Categoria), 1, p);
    fclose(p);
    return escribio;
}

void ArchivoCategoria::listarCategorias() {
    Categoria reg;
    FILE* p = fopen(nombreArchivo, "rb");
    if (p == nullptr) {
        cout << "error al abrir el archivo" << endl;
        return;
    }

    cout << "-----LISTADO DE CATEGORIAS-----" << endl;

    while (fread(&reg, sizeof(Categoria), 1, p) == 1) {
        if (reg.getActiva()) {
            reg.mostrar();
        }
    }

    fclose(p);
}

Categoria ArchivoCategoria::leer(int pos) {
    Categoria reg;
    FILE* p = fopen(nombreArchivo, "rb");
    if (p == nullptr) {
        return reg;
    }

    fseek(p, pos * sizeof(Categoria), SEEK_SET);
    fread(&reg, sizeof(Categoria), 1, p);
    fclose(p);
    return reg;
}

int ArchivoCategoria::getCantidadRegistros() {
    FILE* p = fopen(nombreArchivo, "rb");
    if (p == nullptr) {
        return 0;
    }

    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);

    return bytes / (int)sizeof(Categoria);
}

bool ArchivoCategoria::categoriaExiste(int id) {
    int cantidad = getCantidadRegistros();

    for (int m = 0; m < cantidad; m++) {
        Categoria reg = leer(m);
        if (reg.getId() == id && reg.getActiva()) {
            return true;
        }
    }

    return false;
}

int ArchivoCategoria::buscarPorId(int id) {
    int cantidad = getCantidadRegistros();

    for (int i = 0; i < cantidad; i++) {
        Categoria reg = leer(i);
        if (reg.getId() == id) {
            return i;
        }
    }

    return -1;
}

bool ArchivoCategoria::modificarCategoria(Categoria reg, int pos) {
    FILE* p = fopen(nombreArchivo, "rb+");
    if (p == nullptr) {
        return false;
    }

    fseek(p, pos * sizeof(Categoria), SEEK_SET);
    bool escribio = fwrite(&reg, sizeof(Categoria), 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoCategoria::bajaLogica(int id) {
    int pos = buscarPorId(id);
    if (pos == -1) {
        return false;
    }

    Categoria reg = leer(pos);
    reg.setActiva(false);

    return modificarCategoria(reg, pos);
}

bool ArchivoCategoria::altaLogica(int id) {
    int pos = buscarPorId(id);
    if (pos == -1) {
        return false;
    }

    Categoria reg = leer(pos);
    reg.setActiva(true);

    return modificarCategoria(reg, pos);
}
