#include <iostream>
#include <cstdio>
#include <cstring>
#include "ArchivoCliente.h"
using namespace std;

ArchivoCliente::ArchivoCliente(const char* n){
   // nombre archivo
 strcpy(nombreArchivo, n);
}

bool ArchivoCliente::grabarRegistro(Cliente reg){
    FILE* p = fopen(nombreArchivo, "ab");
    if (p==nullptr) return false;

    int nuevoId = contarRegistros()+1; // id nuevo
    reg.setIdCliente(nuevoId);

    bool ok = fwrite(&reg,sizeof(Cliente),1,p);
    fclose(p);
    return ok;
}

Cliente ArchivoCliente::leerRegistro(int pos){
    Cliente reg;
    FILE* p=fopen(nombreArchivo,"rb");
    if(!p) return reg;

    fseek(p, pos*sizeof(Cliente) ,SEEK_SET);
    fread(&reg,sizeof(Cliente),1,p);
    fclose(p);

    return reg;
}

int ArchivoCliente::contarRegistros(){
 FILE* p = fopen(nombreArchivo,"rb");
 if(p==NULL) return 0;

 fseek(p,0,SEEK_END);
 int bytes = ftell(p);
 fclose(p);

 return  bytes / sizeof(Cliente);;
}

int ArchivoCliente::buscarPorDNI(const char* dniBuscado){
    Cliente x;
    FILE* p=fopen(nombreArchivo,"rb");
    if(p==nullptr) return -1;

    int pos=0;
    while(fread(&x,sizeof(Cliente),1,p)){
        if(strcmp(x.getDni(),dniBuscado)==0){
            fclose(p);
            return pos;
        }
        pos++;
    }

    fclose(p);
    return -1;
}

bool ArchivoCliente::modificarRegistro(Cliente r, int pos){
    FILE* p=fopen(nombreArchivo,"rb+");
    if(p==NULL) return false;

    fseek(p, pos * sizeof(Cliente) , SEEK_SET);
    bool ok = fwrite(&r,sizeof(Cliente),1,p);
    fclose(p);
    return ok;
}

int ArchivoCliente::buscarPorId(int id){
    Cliente c;
    FILE* p=fopen(nombreArchivo,"rb");
    if(!p) return -1;
    int pos=0;

    while(fread(&c,sizeof(Cliente),1,p)){
       if(c.getIdCliente()==id){
           fclose(p);
           return pos;
       }
       pos++;
    }

    fclose(p);
    return -1;
}

bool ArchivoCliente::modificarClientePorID(int idBuscado){
int pos = buscarPorId(idBuscado);
 if(pos<0) return false;

   Cliente c = leerRegistro(pos);
   cout<<"--MODIFICAR CLIENTE--";
   c.cargar();      // recarga datos
   c.setIdCliente(idBuscado);

 return modificarRegistro(c,pos);
}

void ArchivoCliente::listarActivos(){
   int tot = contarRegistros();

   for(int i=0;i<tot;i++){
       Cliente c = leerRegistro(i);
       if (c.getActivo()){
          c.mostrar();
      cout<<"------------\n";
       }
   }
}

void ArchivoCliente::listarInactivos(){
   int tot = contarRegistros();

   for(int i=0;i<tot;i++){
       Cliente c = leerRegistro(i);
       if (c.getActivo() == false){
          c.mostrar();
      cout<<"------------\n";
       }
   }
}

bool ArchivoCliente::bajaLogica(int pos){
    Cliente c = leerRegistro(pos);
    if(c.getIdCliente()==-1) return false;

    c.setActivo(false);
    return modificarRegistro(c,pos);
}

bool ArchivoCliente::altaLogica(int pos){
    Cliente c = leerRegistro(pos);
    if(c.getIdCliente()==-1) return false;

    c.setActivo(true);
    return modificarRegistro(c,pos);
}

int ArchivoCliente::buscarPorApellido(const char* ape){
   int tot = contarRegistros();

   for(int i=0;i<tot;i++){
       Cliente c = leerRegistro(i);
       if(strcmp(c.getApellido(),ape)==0){
           return i;
       }
   }

   return -1;
}
