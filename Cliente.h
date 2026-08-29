#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

class Cliente {
private:
    int idCliente;
    char nombre[30];
    char apellido [30];
    char dni[10];
    char telefono[20];
    char email[40];
    bool activo;

public:
int getIdCliente();
void setIdCliente(int id);
const char* getNombre();
void setNombre(const char* n);
const char* getApellido();
void setApellido(const char* a);
const char* getDni();
void setDni(const char* d);
const char* getTelefono();
void setTelefono(const char* t);
const char* getEmail();
void setEmail(const char* e);
bool getActivo();
void setActivo(bool a);
void cargar();
void mostrar();

};

#endif // CLIENTE_H_INCLUDED
