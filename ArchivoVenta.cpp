#include "ArchivoVenta.h"
#include "ArchivoDetalleVenta.h"
#include "ArchivoCliente.h"
#include "ArchivoItem.h"
#include "archivoUsuario.h"
#include "DetalleVenta.h"
#include "fecha.h"
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

ArchivoVenta::ArchivoVenta(const char* nombre) {
    strcpy(nombreArchivo, nombre);
}

bool ArchivoVenta::guardar(Venta reg) {
    FILE* p = fopen(nombreArchivo, "ab");
    if (p == nullptr) {
        return false;
    }
    bool escribio = fwrite(&reg, sizeof(Venta), 1, p);
    fclose(p);
    return escribio;
}

Venta ArchivoVenta::leer(int pos) {
    Venta reg;
    FILE* p = fopen(nombreArchivo, "rb");
    if (p == nullptr) {
        return reg;
    }
    fseek(p, pos * sizeof(Venta), SEEK_SET);
    fread(&reg, sizeof(Venta), 1, p);
    fclose(p);
    return reg;
}

int ArchivoVenta::contarRegistros() {
    FILE* p = fopen(nombreArchivo, "rb");
    if (p == nullptr) {
        return 0;
    }
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Venta);
}

void ArchivoVenta::listar() {
    Venta reg;
    int cant = contarRegistros();

    cout << "\n===== LISTADO DE VENTAS =====" << endl;

    for (int i = 0; i < cant; i++) {
        reg = leer(i);
        if (!reg.getAnulada()) {
            reg.mostrar();
        }
    }
}

void ArchivoVenta::listarPorFecha(Fecha desde, Fecha hasta){
    Venta reg;
    int cant = contarRegistros();

    for(int i = 0; i < cant; i++){
        reg = leer(i);
        Fecha f = reg.getFecha();

        bool mayorOIgualDesde = false;
        bool menorOIgualHasta = false;

        /// Comparar con fecha DESDE
        if(f.getAnio() > desde.getAnio()){
            mayorOIgualDesde = true;
        }
        else if(f.getAnio() == desde.getAnio()){

            if(f.getMes() > desde.getMes()){
                mayorOIgualDesde = true;
            }
            else if(f.getMes() == desde.getMes()){

                if(f.getDia() >= desde.getDia()){
                    mayorOIgualDesde = true;
                }
            }
        }
        /// Comparar con fecha HASTA
        if(f.getAnio() < hasta.getAnio()){
            menorOIgualHasta = true;
        }
        else if(f.getAnio() == hasta.getAnio()){

            if(f.getMes() < hasta.getMes()){
                menorOIgualHasta = true;
            }
            else if(f.getMes() == hasta.getMes()){

                if(f.getDia() <= hasta.getDia()){
                    menorOIgualHasta = true;
                }
            }
        }
        if(mayorOIgualDesde && menorOIgualHasta){
            reg.mostrar();
        }
    }
}

int ArchivoVenta::buscarPorId(int id) {
    Venta reg;
    int cant = contarRegistros();

    for (int i = 0; i < cant; i++) {
        reg = leer(i);
        if (reg.getIdVenta() == id) {
            return i;
        }
    }
    return -1;
}

bool ArchivoVenta::modificar(Venta reg, int pos) {
    FILE* p = fopen(nombreArchivo, "rb+");
    if (p == nullptr) {
        return false;
    }
    fseek(p, pos * sizeof(Venta), SEEK_SET);
    bool escribio = fwrite(&reg, sizeof(Venta), 1, p);
    fclose(p);
    return escribio;
}

void ArchivoVenta::registrarVenta() {
    ArchivoCliente archCli("clientes.dat");
    ArchivoItem archItem("items.dat");
    ArchivoDetalleVenta archDetalle("detalleVentas.dat");
    ArchivoUsuario archUsu("usuarios.dat");

    Venta venta;
    int idUsuario;
    char dniCliente[10], codigo[20];
    int cantidad;
    float totalVenta = 0.0f;

    cout << "\n================================" << endl;
    cout << "     REGISTRAR NUEVA VENTA      " << endl;
    cout << "================================" << endl;

    cout << "Ingrese ID del usuario (vendedor): ";
    cin >> idUsuario;

    int posUsuario = archUsu.buscarPorId(idUsuario);
    if (posUsuario == -1) {
        cout << "ERROR: Usuario no encontrado." << endl;
        return;
    }

    Usuario usuario;
    archUsu.leer(usuario, posUsuario);

    if(!usuario.getActivo()){
        cout << "ERROR: Usuario inactivo." << endl;
        return;
    }

    char passwordIngresada[20];
    cout << "Ingrese la contrasena: ";
    cin.ignore();
    cin.getline(passwordIngresada, 20);

    if(strcmp(passwordIngresada, usuario.getPassword()) != 0){
        cout << "ERROR: Contrasena incorrecta." << endl;
        return;
    }

    cout << "Usuario autenticado: " << usuario.getNombre() << endl;

    cout << "\nIngrese DNI del cliente: ";
    cin >> dniCliente;

    int posCliente = archCli.buscarPorDNI(dniCliente);
    if (posCliente == -1) {
        cout << "ERROR: Cliente no encontrado." << endl;
        return;
    }

    Cliente cliente = archCli.leerRegistro(posCliente);
    cout << "Cliente: " << cliente.getNombre() << " " << cliente.getApellido() << endl;
    int idCliente = cliente.getIdCliente();
    int nuevoIdVenta = contarRegistros() + 1;
    venta.setIdVenta(nuevoIdVenta);
    venta.setIdCliente(idCliente);
    venta.setIdUsuario(idUsuario);

    Fecha fechaVenta;
    cout << "\n--- FECHA DE LA VENTA ---" << endl;
    fechaVenta.cargar();
    venta.setFecha(fechaVenta);

    int contadorDetalle = archDetalle.contarRegistros();

    cout << "\n--- AGREGAR ITEMS A LA VENTA ---" << endl;
    cout << "(Ingrese codigo '0' para terminar)" << endl;

    cin.ignore();

    while (true) {
        cout << "\nCodigo del item (0 para terminar): ";
        cin.getline(codigo, 20);

        if (strcmp(codigo, "0") == 0) {
            break;
        }

        int posItem = archItem.buscar(codigo);

        if (posItem == -1) {
            cout << "ERROR: Item no encontrado." << endl;
            continue;
        }

        Item item = archItem.leer(posItem);

        cout << "Item encontrado: " << item.getNombre() << endl;
        cout << "Stock disponible: " << item.getStockActual() << endl;
        cout << "Precio: $" << item.getPrecioVenta() << endl;

        cout << "Cantidad a vender: ";
        cin >> cantidad;
        cin.ignore();

        if (cantidad > item.getStockActual()) {
            cout << "ERROR: Stock insuficiente." << endl;
            continue;
        }

        DetalleVenta detalle;
        contadorDetalle++;
        detalle.setIdDetalle(contadorDetalle);
        detalle.setIdVenta(nuevoIdVenta);
        detalle.setIdItem(item.getIdItem());
        detalle.setCantidad(cantidad);
        detalle.setPrecioUnitario(item.getPrecioVenta());

        if (archDetalle.guardar(detalle)) {
            cout << "Item agregado a la venta." << endl;

            int nuevoStock = item.getStockActual() - cantidad;
            item.setStockActual(nuevoStock);

            if (archItem.modificar(item, posItem)) {
                cout << "Stock actualizado. Nuevo stock: " << nuevoStock << endl;
            }

            totalVenta += cantidad*item.getPrecioVenta();

        } else {
            cout << "ERROR: No se pudo guardar el detalle." << endl;
        }
    }

    venta.setTotal(totalVenta);
    venta.setAnulada(false);

    if (guardar(venta)) {
        cout << "\n================================" << endl;
        cout << "   VENTA REGISTRADA EXITOSAMENTE" << endl;
        cout << "================================" << endl;
        venta.mostrar();

        cout << "\n--- DETALLE DE LA VENTA ---" << endl;
        archDetalle.listarPorVenta(nuevoIdVenta);

    } else {
        cout << "ERROR: No se pudo guardar la venta." << endl;
    }
}

void ArchivoVenta::informeTotalRecaudado() {
    Venta reg;
    int cant = contarRegistros();
    float totalRecaudado = 0.0f;
    int cantidadVentas = 0;

    cout << "\n================================================" << endl;
    cout << "          INFORME: TOTAL RECAUDADO             " << endl;
    cout << "================================================" << endl;

    for (int i = 0; i < cant; i++) {
        reg = leer(i);
        if (!reg.getAnulada()) {
            totalRecaudado += reg.getTotal();
            cantidadVentas++;
        }
    }

    cout << "\nCantidad de ventas: " << cantidadVentas << endl;
    cout << "Total recaudado: $" << totalRecaudado << endl;

    if (cantidadVentas > 0) {
        cout << "Promedio por venta: $" << (totalRecaudado / cantidadVentas) << endl;
    }

    cout << "================================================" << endl;
}

void ArchivoVenta::informeVentasPorCliente() {
    Venta reg;
    ArchivoCliente archCli("clientes.dat");
    int cant = contarRegistros();

    cout << "\n================================================" << endl;
    cout << "        INFORME: VENTAS POR CLIENTE            " << endl;
    cout << "================================================" << endl;

    int ventasPorCliente[100] = {0};
    float totalPorCliente[100] = {0.0f};

    for (int i = 0; i < cant; i++) {
        reg = leer(i);
        if (!reg.getAnulada() && reg.getIdCliente() < 100) {
            ventasPorCliente[reg.getIdCliente()]++;
            totalPorCliente[reg.getIdCliente()] += reg.getTotal();
        }
    }

    for (int i = 0; i < 100; i++) {
        if (ventasPorCliente[i] > 0) {
            int posCliente = archCli.buscarPorId(i);
            if (posCliente != -1) {
                Cliente cli = archCli.leerRegistro(posCliente);
                cout << "\nCliente: " << cli.getNombre() << " " << cli.getApellido() << endl;
                cout << "Cantidad de compras: " << ventasPorCliente[i] << endl;
                cout << "Total gastado: $" << totalPorCliente[i] << endl;
                cout << "----------------------------" << endl;
            }
        }
    }

    cout << "================================================" << endl;
}

void ArchivoVenta::informeTopProductos() {
    ArchivoDetalleVenta archDetalle("detalleVentas.dat");
    ArchivoItem archItem("items.dat");
    int cantDetalles = archDetalle.contarRegistros();

    cout << "\n================================================" << endl;
    cout << "        INFORME: TOP 10 PRODUCTOS              " << endl;
    cout << "================================================" << endl;

    int idsProductos[100];
    int cantidadPorProducto[100] = {0};
    float totalPorProducto[100] = {0.0f};
    int cantProductos = 0;

    for (int i = 0; i < cantDetalles; i++) {
        DetalleVenta det = archDetalle.leer(i);
        int idItem = det.getIdItem();

        int pos = -1;
        for (int j = 0; j < cantProductos; j++) {
            if (idsProductos[j] == idItem) {
                pos = j;
                break;
            }
        }

        if (pos != -1) {
            cantidadPorProducto[pos] += det.getCantidad();
            totalPorProducto[pos] += det.getPrecioUnitario() * det.getCantidad();
        }
        else if (cantProductos < 100) {
            idsProductos[cantProductos] = idItem;
            cantidadPorProducto[cantProductos] = det.getCantidad();
            totalPorProducto[cantProductos] = det.getPrecioUnitario() * det.getCantidad();
            cantProductos++;
        }
    }

    for (int i = 0; i < cantProductos - 1; i++) {
        for (int j = 0; j < cantProductos - i - 1; j++) {
            if (cantidadPorProducto[j] < cantidadPorProducto[j + 1]) {
                int tempCant = cantidadPorProducto[j];
                cantidadPorProducto[j] = cantidadPorProducto[j + 1];
                cantidadPorProducto[j + 1] = tempCant;

                float tempTotal = totalPorProducto[j];
                totalPorProducto[j] = totalPorProducto[j + 1];
                totalPorProducto[j + 1] = tempTotal;

                int tempId = idsProductos[j];
                idsProductos[j] = idsProductos[j + 1];
                idsProductos[j + 1] = tempId;
            }
        }
    }

    cout << "\nProductos mas vendidos:\n" << endl;

    int limite = (cantProductos < 10) ? cantProductos : 10;

    for (int i = 0; i < limite; i++) {
        int posItem = archItem.buscarPorId(idsProductos[i]);
        if (posItem != -1) {
            Item item = archItem.leer(posItem);
            cout << (i + 1) << ". " << item.getNombre() << endl;
            cout << "   Unidades vendidas: " << cantidadPorProducto[i] << endl;
            cout << "   Total recaudado: $" << totalPorProducto[i] << endl;
            cout << "   ----------------------------" << endl;
        }
    }

    if (cantProductos == 0) {
        cout << "   No hay ventas registradas." << endl;
    }

    cout << "================================================" << endl;
}
