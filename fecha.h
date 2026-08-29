#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

class Fecha {
private:
    int dia, mes, anio;
public:
    Fecha(int d = 1, int m = 1, int a = 1900);

    void cargar();
    void mostrar();

    void setDia(int d);
    void setMes(int m);
    void setAnio(int a);
    int getDia();
    int getMes();
    int getAnio();
};

#endif // FECHA_H_INCLUDED
