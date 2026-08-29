#include <iostream>
#include <cstring>
#include "fecha.h"
#include "categoria.h"
#include "archivocategoria.h"
#include "item.h"
#include "ArchivoItem.h"
#include "Cliente.h"
#include "ArchivoCliente.h"
#include "usuario.h"
#include "archivoUsuario.h"
#include "Venta.h"
#include "ArchivoVenta.h"
#include "DetalleVenta.h"
#include "ArchivoDetalleVenta.h"
#include "archivoUsuario.h"

using namespace std;

// Prototipos de funciones
void menuCategorias();
void menuItems();
void menuClientes();
void menuUsuarios();
void menuVentas();
void pausar();

int main() {
    int opcion;

    do {
        system("cls");

        cout << "\n";
        cout << "   ================================================\n";
        cout << "                                                  \n";
        cout << "        SISTEMA DE GESTION - LOCAL DE ROPA 2025   \n";
        cout << "                                    \n";
        cout << "                                                  \n";
        cout << "   ================================================\n";
        cout << "\n";
        cout << "   ------------------------------------------------\n";
        cout << "                  MENU PRINCIPAL                  \n";
        cout << "   ------------------------------------------------\n";
        cout << "\n";
        cout << "     [1] Gestionar Categorias\n";
        cout << "     [2] Gestionar Items\n";
        cout << "     [3] Gestionar Clientes\n";
        cout << "     [4] Gestionar Usuarios\n";
        cout << "     [5] Gestionar Ventas \n";
        cout << "\n";
        cout << "     [0] Salir del Sistema\n";
        cout << "\n";
        cout << "   ------------------------------------------------\n";
        cout << "\n   Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                menuCategorias();
                break;
            case 2:
                menuItems();
                break;
            case 3:
                menuClientes();
                break;
            case 4:
                menuUsuarios();
                break;
            case 5:
                menuVentas();
                break;
            case 0:
                system("cls");
                cout << "\n\n";
                cout << "   ================================================\n";
                cout << "                                                  \n";
                cout << "         Gracias por usar el sistema!            \n";
                cout << "              Hasta pronto...                     \n";
                cout << "                                                  \n";
                cout << "   ================================================\n";
                cout << "\n\n";
                break;
            default:
                cout << "\n   >> Opcion invalida. Intente nuevamente.\n";
                pausar();
        }
    } while(opcion != 0);

    return 0;
}

void pausar() {
    cout << "\n   Presione ENTER para continuar...";
    cin.ignore();
    cin.get();
}
void menuCategorias() {
    ArchivoCategoria arch("categorias.dat");
    Categoria cat;
    int opcion;

    do {
        system("cls");
        cout << "\n";
        cout << "   ================================================\n";
        cout << "              GESTION DE CATEGORIAS              \n";
        cout << "   ================================================\n";
        cout << "\n";
        cout << "     [1] Agregar Categoria\n";
        cout << "     [2] Listar Categorias\n";
        cout << "     [3] Buscar por ID\n";
        cout << "     [4] Modificar Categoria\n";
        cout << "     [5] Eliminar Categoria\n";
        cout << "\n";
        cout << "     [0] Volver al Menu Principal\n";
        cout << "\n   Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                system("cls");
                cout << "\n   --- NUEVA CATEGORIA ---\n\n";
                cat.cargar();
                if(arch.guardar(cat)) {
                    cout << "\n   >> Categoria guardada exitosamente!\n";
                } else {
                    cout << "\n   >> Error al guardar categoria.\n";
                }
                pausar();
                break;
            case 2:
                system("cls");
                arch.listarCategorias();
                pausar();
                break;
            case 3: {
                system("cls");
                int id;
                cout << "\n   Ingrese ID de categoria: ";
                cin >> id;
                int pos=arch.buscarPorId(id);
                if(pos!=-1) {
                    Categoria c=arch.leer(pos);
                    cout << "\n   >> Categoria encontrada:\n\n";
                    c.mostrar();
                } else {
                    cout << "\n   >> Categoria no encontrada.\n";
                }
                pausar();
                break;
            }
            case 4:{
                system("cls");
                int id;
                cout<<"\n   --- MODIFICAR CATEGORIA ---\n\n";
                cout<<"   ID de la categoria a modificar: ";
                cin>>id;
                int pos=arch.buscarPorId(id);
                if(pos==-1){
                    cout<<"\n   >> Categoria no encontrada.\n";
                    pausar();
                    break;
                }
                Categoria catActual=arch.leer(pos);
                cout<<"\n   Categoria actual:\n";
                catActual.mostrar();
                cout<<"\n   Ingrese nuevos datos:\n\n";
                Categoria catNueva;
                catNueva.cargar();
                catNueva.setId(id);
                if(arch.modificarCategoria(catNueva,pos)){
                    cout<<"\n   >> Categoria modificada exitosamente!\n";
                }else{
                    cout<<"\n   >> Error al modificar.\n";
                }
                pausar();
                break;
            }
            case 5:{
                system("cls");
                int id;
                cout<<"\n   --- ELIMINAR CATEGORIA ---\n\n";
                cout<<"   ID de la categoria a eliminar: ";
                cin>>id;
                int pos=arch.buscarPorId(id);
                if(pos==-1){
                    cout<<"\n   >> Categoria no encontrada.\n";
                    pausar();
                    break;
                }
                Categoria cat=arch.leer(pos);
                cout<<"\n   Categoria a eliminar:\n";
                cat.mostrar();
                char confirmar;
                cout<<"\n   Esta seguro? (S/N): ";
                cin>>confirmar;
                if(confirmar=='S' || confirmar=='s'){
                    if(arch.bajaLogica(id)){
                        cout<<"\n   >> Categoria eliminada exitosamente!\n";
                    }else{
                        cout<<"\n   >> Error al eliminar.\n";
                    }
                }else{
                    cout<<"\n   >> Operacion cancelada.\n";
                }
                pausar();
                break;
            }
            case 0:
                break;
            default:
                cout << "\n   >> Opcion invalida.\n";
                pausar();
        }
    } while(opcion != 0);
}

void menuItems() {
    ArchivoItem arch("items.dat");
    Item item;
    int opcion;

    do {
        system("cls");
        cout << "\n";
        cout << "   ================================================\n";
        cout << "                GESTION DE ITEMS                 \n";
        cout << "   ================================================\n";
        cout << "\n";
        cout << "     [1] Agregar Item\n";
        cout << "     [2] Listar Items\n";
        cout << "     [3] Buscar por Codigo\n";
        cout << "     [4] Buscar por ID\n";
        cout << "     [5] Modificar Item\n";
        cout << "     [6] Modificar Stock\n";
        cout << "     [7] Eliminar Item\n";
        cout << "     [8] Items con Bajo Stock\n";
        cout << "     [9] Listar por Categoria\n";
        cout << "\n";
        cout << "     [0] Volver al Menu Principal\n";
        cout << "\n   Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                system("cls");
                item.cargar();
                if(arch.guardar(item)) {
                    cout << "\n   >> Item guardado exitosamente!\n";
                } else {
                    cout << "\n   >> Error al guardar item.\n";
                }
                pausar();
                break;
            case 2:
                system("cls");
                cout << "\n   --- LISTADO DE ITEMS ---\n\n";
                arch.listar();
                pausar();
                break;
            case 3: {
                system("cls");
                char codigo[20];
                cout << "\n   Codigo del item: ";
                cin.ignore();
                cin.getline(codigo, 20);
                int pos = arch.buscar(codigo);
                if(pos != -1) {
                    cout << "\n   >> Item encontrado:\n\n";
                    Item itemEncontrado = arch.leer(pos);
                    itemEncontrado.mostrar();
                } else {
                    cout << "\n   >> Item no encontrado.\n";
                }
                pausar();
                break;
            }
            case 4: {
                system("cls");
                int id;
                cout << "\n   ID del item: ";
                cin >> id;
                int pos = arch.buscarPorId(id);
                if(pos != -1) {
                    cout << "\n   >> Item encontrado:\n\n";
                    Item itemEncontrado = arch.leer(pos);
                    itemEncontrado.mostrar();
                } else {
                    cout << "\n   >> Item no encontrado.\n";
                }
                pausar();
                break;
            }
            case 5: {
                system("cls");
                int id;
                cout << "\n   --- MODIFICAR ITEM ---\n\n";
                cout << "   ID del item a modificar: ";
                cin >> id;
                if(arch.modificarItem(id)) {
                    cout << "\n   >> Item modificado exitosamente!\n";
                } else {
                    cout << "\n   >> Item no encontrado o inactivo.\n";
                }
                pausar();
                break;
            }
            case 6: {
                system("cls");
                char codigo[20];
                cout << "\n   Codigo del item: ";
                cin.ignore();
                cin.getline(codigo, 20);
                int pos = arch.buscar(codigo);
                if(pos != -1) {
                    Item itemModificar = arch.leer(pos);
                    cout << "\n   Item actual:\n\n";
                    itemModificar.mostrar();

                    int nuevoStock;
                    cout << "\n   Nuevo stock: ";
                    cin >> nuevoStock;
                    itemModificar.setStockActual(nuevoStock);

                    if(arch.modificar(itemModificar, pos)) {
                        cout << "\n   >> Stock actualizado!\n";
                    } else {
                        cout << "\n   >> Error al actualizar.\n";
                    }
                } else {
                    cout << "\n   >> Item no encontrado.\n";
                }
                pausar();
                break;
            }
            case 7: {
                system("cls");
                int idItem;
                cout << "\n   ID del item a eliminar: ";
                cin >> idItem;

                if(arch.bajaLogica(idItem)) {
                    cout << "\n   >> Item eliminado.\n";
                } else {
                    cout << "\n   >> No se pudo eliminar.\n";
                }
                pausar();
                break;
            }
            case 8: {
                system("cls");
                int limite;
                cout << "\n   Limite de stock: ";
                cin >> limite;
                cout << "\n   --- ITEMS CON BAJO STOCK ---\n\n";
                arch.listarBajoStock(limite);
                pausar();
                break;
            }
            case 9: {
                system("cls");
                int idCategoria;
                cout << "\n   ID de categoria: ";
                cin >> idCategoria;
                cout << "\n   --- ITEMS DE LA CATEGORIA ---\n\n";
                arch.listarPorCategoria(idCategoria);
                pausar();
                break;
            }
            case 0:
                break;
            default:
                cout << "\n   >> Opcion invalida.\n";
                pausar();
        }
    } while(opcion != 0);
}void menuClientes() {
    ArchivoCliente arch("clientes.dat");
    Cliente cliente;
    int opcion;

    do {
        system("cls");
        cout << "\n";
        cout << "   ================================================\n";
        cout << "               GESTION DE CLIENTES               \n";
        cout << "   ================================================\n";
        cout << "\n";
        cout << "     [1] Agregar Cliente\n";
        cout << "     [2] Listar Clientes\n";
        cout << "     [3] Buscar por DNI\n";
        cout << "     [4] Buscar por ID\n";
        cout << "     [5] Modificar Cliente\n";
        cout << "     [6] Eliminar Cliente\n";
        cout << "\n";
        cout << "     [0] Volver al Menu Principal\n";
        cout << "\n   Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                system("cls");
                cout << "\n   --- NUEVO CLIENTE ---\n\n";
                cliente.cargar();
                if(arch.grabarRegistro(cliente)) {
                    cout << "\n   >> Cliente guardado!\n";
                } else {
                    cout << "\n   >> Error al guardar.\n";
                }
                pausar();
                break;
            case 2:
                system("cls");
                cout << "\n   --- LISTADO DE CLIENTES ---\n\n";
                arch.listarActivos();
                pausar();
                break;
            case 3: {
                system("cls");
                char dni[10];
                cout << "\n   DNI del cliente: ";
                cin.ignore();
                cin.getline(dni, 10);
                int pos = arch.buscarPorDNI(dni);
                if(pos != -1) {
                    cout << "\n   >> Cliente encontrado:\n\n";
                    Cliente clienteEncontrado = arch.leerRegistro(pos);
                    clienteEncontrado.mostrar();
                } else {
                    cout << "\n   >> Cliente no encontrado.\n";
                }
                pausar();
                break;
            }
            case 4: {
                system("cls");
                int id;
                cout << "\n   ID del cliente: ";
                cin >> id;
                int pos = arch.buscarPorId(id);
                if(pos != -1) {
                    cout << "\n   >> Cliente encontrado:\n\n";
                    Cliente clienteEncontrado = arch.leerRegistro(pos);
                    clienteEncontrado.mostrar();
                } else {
                    cout << "\n   >> Cliente no encontrado.\n";
                }
                pausar();
                break;
            }
            case 5:{
                system("cls");
                int id;
                cout<<"\n   --- MODIFICAR CLIENTE ---\n\n";
                cout<<"   ID del cliente a modificar: ";
                cin>>id;
                int pos=arch.buscarPorId(id);
                if(pos==-1){
                    cout<<"\n   >> Cliente no encontrado.\n";
                    pausar();
                    break;
                }
                Cliente cliActual=arch.leerRegistro(pos);
                cout<<"\n   Cliente actual:\n";
                cliActual.mostrar();
                cout<<"\n   Ingrese nuevos datos:\n\n";
                if(arch.modificarClientePorID(id)){
                    cout<<"\n   >> Cliente modificado exitosamente!\n";
                }else{
                    cout<<"\n   >> Error al modificar.\n";
                }
                pausar();
                break;
            }
            case 6:{
                system("cls");
                int id;
                cout<<"\n   --- ELIMINAR CLIENTE ---\n\n";
                cout<<"   ID del cliente a eliminar: ";
                cin>>id;
                int pos=arch.buscarPorId(id);
                if(pos==-1){
                    cout<<"\n   >> Cliente no encontrado.\n";
                    pausar();
                    break;
                }
                Cliente cli=arch.leerRegistro(pos);
                cout<<"\n   Cliente a eliminar:\n";
                cli.mostrar();
                char confirmar;
                cout<<"\n   Esta seguro? (S/N): ";
                cin>>confirmar;
                if(confirmar=='S'||confirmar=='s'){
                    if(arch.bajaLogica(pos)){
                        cout<<"\n   >> Cliente eliminado exitosamente!\n";
                    }else{
                        cout<<"\n   >> Error al eliminar.\n";
                    }
                }else{
                    cout<<"\n   >> Operacion cancelada.\n";
                }
                pausar();
                break;
            }
            case 0:
                break;
            default:
                cout << "\n   >> Opcion invalida.\n";
                pausar();
        }
    } while(opcion != 0);
}void menuUsuarios() {
    ArchivoUsuario arch("usuarios.dat");
    Usuario usuario;
    int opcion;

    do {
        system("cls");
        cout << "\n";
        cout << "   ================================================\n";
        cout << "               GESTION DE USUARIOS               \n";
        cout << "   ================================================\n";
        cout << "\n";
        cout << "     [1] Agregar Usuario\n";
        cout << "     [2] Listar Usuarios\n";
        cout << "     [3] Buscar por ID\n";
        cout << "     [4] Modificar Usuario\n";
        cout << "     [5] Eliminar Usuario\n";
        cout << "\n";
        cout << "     [0] Volver al Menu Principal\n";
        cout << "\n   Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                system("cls");
                cout << "\n   --- NUEVO USUARIO ---\n\n";
                int resultado = usuario.cargar();
                if(resultado == 1) {
                    if(arch.guardar(usuario)) {
                        cout << "\n   >> Usuario guardado!\n";
                    } else {
                        cout << "\n   >> Error al guardar.\n";
                    }
                } else if(resultado == -2) {
                    cout << "\n   >> Las contrasenas no coinciden.\n";
                }
                pausar();
                break;
            }
            case 2: {
                system("cls");
                int cant = arch.contarRegistros();
                if(cant == 0) {
                    cout << "\n   >> No hay usuarios registrados.\n";
                } else {
                    cout << "\n   --- LISTADO DE USUARIOS ---\n\n";
                    for(int i = 0; i < cant; i++) {
                        Usuario u;
                        if(arch.leer(u, i)) {
                            u.mostrar();
                            cout << "   ---------------------\n";
                        }
                    }
                }
                pausar();
                break;
            }
            case 3: {
                system("cls");
                int id;
                cout << "\n   ID del usuario: ";
                cin >> id;
                int pos = arch.buscarPorId(id);
                if(pos != -1) {
                    Usuario u;
                    if(arch.leer(u, pos)) {
                        cout << "\n   >> Usuario encontrado:\n\n";
                        u.mostrar();
                    }
                } else {
                    cout << "\n   >> Usuario no encontrado.\n";
                }
                pausar();
                break;
            }
            case 4:{
                system("cls");
                int id;
                cout<<"\n   --- MODIFICAR USUARIO ---\n\n";
                cout<<"   ID del usuario a modificar: ";
                cin>>id;
                int pos=arch.buscarPorId(id);
                if(pos==-1){
                    cout<<"\n   >> Usuario no encontrado.\n";
                    pausar();
                    break;
                }
                Usuario usuActual;
                arch.leer(usuActual,pos);
                cout<<"\n   Usuario actual:\n";
                usuActual.mostrar();
                cout<<"\n   Ingrese nuevos datos:\n\n";
                Usuario usuNuevo;
                int resultado=usuNuevo.cargar();
                if(resultado==1){
                    usuNuevo.setId(id);
                    if(arch.modificar(usuNuevo,pos)){
                        cout<<"\n   >> Usuario modificado exitosamente!\n";
                    }else{
                        cout<<"\n   >> Error al modificar.\n";
                    }
                }else if(resultado==-2){
                    cout<<"\n   >> Las contrasenas no coinciden.\n";
                }
                pausar();
                break;
            }
            case 5:{
                system("cls");
                int id;
                cout<<"\n   --- ELIMINAR USUARIO ---\n\n";
                cout<<"   ID del usuario a eliminar: ";
                cin>>id;
                int pos=arch.buscarPorId(id);
                if(pos==-1){
                    cout<<"\n   >> Usuario no encontrado.\n";
                    pausar();
                    break;
                }
                Usuario usu;
                arch.leer(usu,pos);
                cout<<"\n   Usuario a eliminar:\n";
                usu.mostrar();
                char confirmar;
                cout<<"\n   Esta seguro? (S/N): ";
                cin>>confirmar;
                if(confirmar=='S'||confirmar=='s'){
                    if(arch.bajaLogica(id)){
                        cout<<"\n   >> Usuario eliminado exitosamente!\n";
                    }else{

                        cout<<"\n   >> Error al eliminar.\n";
                    }
                }else{
                    cout<<"\n   >> Operacion cancelada.\n";
                }
                pausar();
                break;
            }
            case 0:
                break;
            default:
                cout << "\n   >> Opcion invalida.\n";
                pausar();
        }
    } while(opcion != 0);
}
void menuVentas() {
    ArchivoVenta archVenta("ventas.dat");
    ArchivoDetalleVenta archDetalle("detalleVentas.dat");
    int opcion;

    do {
        system("cls");
        cout << "\n";
        cout << "   ================================================\n";
        cout << "              GESTION DE VENTAS     \n";
        cout << "   ================================================\n";
        cout << "\n";
        cout << "     [1] Registrar Nueva Venta\n";
        cout << "     [2] Listar Todas las Ventas\n";
        cout << "     [3] Buscar Venta por ID\n";
        cout << "     [4] Ver Detalles de una Venta\n";
        cout << "     [5] Listar Todos los Detalles\n";
        cout << "\n";
        cout << "     --- INFORMES ---\n";
        cout << "     [6] Informe: Total Recaudado\n";
        cout << "     [7] Informe: Ventas por Cliente\n";
        cout << "     [8] Informe: Top 10 Productos\n";
        cout << "\n";
        cout << "     [0] Volver al Menu Principal\n";
        cout << "\n   Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                system("cls");
                archVenta.registrarVenta();
                pausar();
                break;
            case 2:
                system("cls");
                archVenta.listar();
                pausar();
                break;
            case 3: {
                system("cls");
                int id;
                cout << "\n   ID de venta: ";
                cin >> id;
                int pos = archVenta.buscarPorId(id);
                if(pos != -1) {
                    cout << "\n   >> Venta encontrada:\n\n";
                    Venta v = archVenta.leer(pos);
                    v.mostrar();
                } else {
                    cout << "\n   >> Venta no encontrada.\n";
                }
                pausar();
                break;
            }
            case 4: {
                system("cls");
                int id;
                cout << "\n   ID de venta: ";
                cin >> id;
                archDetalle.listarPorVenta(id);
                pausar();
                break;
            }
            case 5:
                system("cls");
                archDetalle.listar();
                pausar();
                break;
            case 6:
                system("cls");
                archVenta.informeTotalRecaudado();
                pausar();
                break;
            case 7:
                system("cls");
                archVenta.informeVentasPorCliente();
                pausar();
                break;
            case 8:
                system("cls");
                archVenta.informeTopProductos();
                pausar();
                break;
            case 0:
                break;
            default:
                cout << "\n   >> Opcion invalida.\n";
                pausar();
        }
    } while(opcion != 0);
}

