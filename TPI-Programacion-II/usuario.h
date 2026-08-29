#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

class Usuario {
private:
    int id;
    char nombreUsuario[30];
    char password[20];
    int idRol;
    bool activo;

public:
    Usuario();

    int cargar();
    void mostrar();

    const char* getNombre() const { return nombreUsuario; }
    const char* getPassword() const { return password; }
    int getId() { return id; }
    int getIdRol() { return idRol; }
    bool getActivo() { return activo; }
        void setActivo(bool a) { activo = a; }
    void setId(int i) { id = i; }
    void setIdRol(int i) { id = i; }
};

#endif
