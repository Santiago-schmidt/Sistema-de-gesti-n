#ifndef CATEGORIA_H_INCLUDED
#define CATEGORIA_H_INCLUDED

class Categoria {
private:
    int id;
    char nombre[50];
    char descripcion[100];
    bool activa;
public:
    Categoria();
    void cargar();
    void mostrar();

    void setId(int i);
    void setNombre(const char* n);
    void setDescripcion(const char* d);
    void setActiva(bool a);

    int getId();
    const char* getNombre();
    const char* getDescripcion();
    bool getActiva();
};


#endif // CATEGORIA_H_INCLUDED
