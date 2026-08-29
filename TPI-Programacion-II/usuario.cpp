#include <iostream>
#include <cstring>
#include "usuario.h"
using namespace std;

Usuario::Usuario(){
    id = 0;
    nombreUsuario[0] = '\0';
    password[0] = '\0';
    idRol = 0;
    activo = true;
}

int Usuario::cargar(){
    char confirmPassword[20];

    cin.ignore();

    cout << "Nombre completo: ";
    cin.getline(nombreUsuario, 30);

    cout << "Contrasena: ";
    cin.getline(password, 20);

    cout << "Repita su contrasena: ";
    cin.getline(confirmPassword, 20);

    if(strcmp(password, confirmPassword) != 0){
        return -2;    // no coinciden
    }

    activo = true;
    return 1;
}

void Usuario::mostrar(){
    cout << "ID: " << id << endl;
    cout << "Nombre: " << nombreUsuario << endl;
    cout << "Estado: " << (activo ? "Activo" : "Inactivo") << endl;
}
