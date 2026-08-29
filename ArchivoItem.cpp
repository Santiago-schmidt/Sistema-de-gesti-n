#include "ArchivoItem.h"
#include <iostream>
#include <cstring>
using namespace std;

ArchivoItem::ArchivoItem(const char* n){
   strcpy(nombre, n);   // nombre archivo
}

bool ArchivoItem::guardar(Item reg){
    FILE *p;
    p = fopen(nombre, "ab");
    if(p == NULL){
        return false;
    }

    int nuevoId = contarRegistros() + 1;
    reg.setIdItem(nuevoId);

    bool escribio = fwrite(&reg, sizeof reg, 1, p);
    fclose(p);
    return escribio;
}

Item ArchivoItem::leer(int pos){
    Item reg;
    FILE *p;
    p = fopen(nombre, "rb");
    if(p == NULL){
        return reg;
    }

    fseek(p, pos * sizeof reg, 0);
    fread(&reg, sizeof reg, 1, p);
    fclose(p);

    return reg;
}

int ArchivoItem::contarRegistros(){
    FILE *p;
    p = fopen(nombre, "rb");
    if(p == NULL){
        return 0;
    }

    fseek(p, 0, 2);
    int cant = ftell(p) / sizeof(Item);
    fclose(p);

    return cant;
}

void ArchivoItem::listar(){
    Item reg;
    int cant = contarRegistros();

    for(int i = 0; i < cant; i++){
        reg = leer(i);
        if (reg.getActivo()){
            reg.mostrar();
        }
    }
}

int ArchivoItem::buscar(const char* codigo){
    Item reg;
    int cant = contarRegistros();

    for(int i = 0; i < cant; i++){
        reg = leer(i);
        if(strcmp(reg.getCodigo(), codigo) == 0 && reg.getActivo()){
            return i;
        }
    }

    return -1;
}

bool ArchivoItem::modificar(Item reg, int pos){
    FILE *p;
    p = fopen(nombre, "rb+");
    if(p == NULL){
        return false;
    }

    fseek(p, pos * sizeof(Item), 0);
    bool escribio = fwrite(&reg, sizeof(Item), 1, p);
    fclose(p);

    return escribio;
}

bool ArchivoItem::modificarItem(int idBuscado){
    Item reg;
    FILE *p = fopen(nombre, "rb+");
    if (p == NULL) return false;

    while (fread(&reg, sizeof(Item), 1, p)){
        if (reg.getIdItem() == idBuscado && reg.getActivo()){

            cout << "Item encontrado:\n";
            reg.mostrar();

            cout << "\n\nIngrese nuevos datos:\n";

            Item nuevo;
            nuevo.cargar();
            nuevo.setIdItem(idBuscado);
            nuevo.setActivo(true);

            fseek(p, -sizeof(Item), SEEK_CUR);
            fwrite(&nuevo, sizeof(Item), 1, p);

            fclose(p);
            return true;
        }
    }

    fclose(p);
    return false;
}

int ArchivoItem::buscarPorId(int id){
    Item reg;
    int cant = contarRegistros();

    for(int i = 0; i < cant; i++){
        reg = leer(i);
        if(reg.getIdItem() == id){
            return i;
        }
    }

    return -1;
}

bool ArchivoItem::bajaLogica(int id){
    int pos = buscarPorId(id);
    if(pos == -1) return false;

    Item reg = leer(pos);
    reg.setActivo(false);

    return modificar(reg, pos);
}

void ArchivoItem::listarBajoStock(int limite){
    Item reg;
    int cant = contarRegistros();

    for (int i = 0; i < cant; i++){
        reg = leer(i);
        if(reg.getActivo() && reg.getStockActual() < limite){
            reg.mostrar();
            cout << "---------------------\n";
        }
    }
}

void ArchivoItem::listarPorCategoria(int idCategoria){
    Item reg;
    bool band = false;
    int cant = contarRegistros();

    for (int i = 0; i < cant; i++){
        reg = leer(i);
        if(reg.getActivo() && reg.getIdCategoria() == idCategoria){
            reg.mostrar();
            cout << "---------------------\n";
            band = true;
        }
    }

    if(!band) cout << "Categoria no existe... " << endl;
}
