#pragma once
#include <mysql.h>
#include <string>
#include <iostream>
#include "ConexionBD.h"

using namespace std;

class Producto
{
private:

    int id = 0;
    int id_producto = 0;
    string producto;
    int id_marca = 0;
    string descripcion;
    string imagen;
    double precio_costo;
    double precio_venta;
    int existencia = 0;
    tm fecha_ingreso;

public:
    Producto() {}

    Producto(int idp, string p, int im, string d, string img, double pc, double pv, int e, tm fi, int i) {
        id = i;
        id_producto = idp;
        producto = p;
        id_marca = im;
        descripcion = d;
        imagen = img;
        precio_costo = pc;
        precio_venta = pv;
        existencia = e;
        fecha_ingreso = fi;
    }

    // Métodos SET
    void setId(int i) { id = i; }
    void setIdProducto(int idp) { id_producto = idp; }
    void setProducto(string p) { producto = p; }
    void setIdMarca(int im) { id_marca = im; }
    void setDescripcion(string d) { descripcion = d; }
    void setImagen(string i) { imagen = i; }
    void setPrecioCosto(double pc) { precio_costo = pc; }
    void setPrecioVenta(double pv) { precio_venta = pv; }
    void setExistencia(int e) { existencia = e; }
    void setFechaIngreso(tm fi) { fecha_ingreso = fi; }

    // Métodos GET
    int getId() { return id; }
    int getIdProducto() { return id_producto; }
    string getProducto() { return producto; }
    int getIdMarca() { return id_marca; }
    string getDescripcion() { return descripcion; }
    string getImagen() { return imagen; }
    double getPrecioCosto() { return precio_costo; }
    double getPrecioVenta() { return precio_venta; }
    int getExistencia() { return existencia; }
    tm getFechaIngreso() { return fecha_ingreso; }

    //CRUD METODOS
    void crear() {
        int q_estado;
        ConexionBD cn = ConexionBD();

        if (cn.getConectar()) {
            string insertar = "INSERT INTO productos(producto, idMarca, descripcion, imagen, precio_costo, precio_venta, existencia, fecha_ingreso) VALUES('" +
                producto + "', " + to_string(id_marca) + ", '" + descripcion + "', '" + imagen + "', " + to_string(precio_costo) + ", " +
                to_string(precio_venta) + ", " + to_string(existencia) + ", NOW())";
            const char* i = insertar.c_str();
            q_estado = mysql_query(cn.getConectar(), i);
            if (!q_estado) {
                cout << "Ingreso exitoso.." << endl;
            }
            else {
                cout << "--*Error al ingresar*--" << endl;
            }
        }
        else {
            cout << "--*Error en la conexión*--" << endl;
        }
        cn.cerrar_conexion();
    }

    void leer() {
        int q_estado;
        ConexionBD cn = ConexionBD();

        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrirConexion();
        if (cn.getConectar()) {
            string consulta = "SELECT * FROM productos";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConectar(), c);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConectar());
                cout << "-----------------------Productos-----------------" << endl;
                while (fila = mysql_fetch_row(resultado)) {
                    cout << fila[0] << ": " << fila[1] << ": " << fila[2] << ": " << fila[3] << ": " << fila[4] << ": " << fila[5] << ": " << fila[6] << ": " << fila[7] << ": " << fila[8] << endl;
                }
            }
            else {
                cout << "---*Error al consultar*---" << endl;
            }
        }
        else {
            cout << "---*Error en la conexión*---" << endl;
        }
        cn.cerrar_conexion();
    }

    void actualizar() {
        int q_estado;
        ConexionBD cn = ConexionBD();

        cn.abrirConexion();
        string ii = to_string(id);
        if (cn.getConectar()) {
            string actualizar = "UPDATE productos SET producto = '" + producto + "', idMarca = " + to_string(id_marca) + ", descripcion = '" + descripcion + "', imagen = '" + imagen + "', precio_costo = " + to_string(precio_costo) + ", precio_venta = " + to_string(precio_venta) + ", existencia = " + to_string(existencia) + " WHERE idProducto = " + ii;
            const char* i = actualizar.c_str();
            q_estado = mysql_query(cn.getConectar(), i);
            if (!q_estado) {
                cout << "Actualización Exitosa..." << endl;
            }
            else {
                cout << "---*Error al actualizar*---" << endl;
            }
        }
        else {
            cout << "---*Error en la conexión*---" << endl;
        }
        cn.cerrar_conexion();
    }


    void borrar() {
        int q_estado;
        ConexionBD cn = ConexionBD();

        cn.abrirConexion();
        string ii = to_string(id);

        if (cn.getConectar()) {
            string borrar = "DELETE FROM productos WHERE idProducto = " + ii + "";
            const char* i = borrar.c_str();
            q_estado = mysql_query(cn.getConectar(), i);
            if (!q_estado) {
                cout << "Eliminación exitosa" << endl;
            }
            else {
                cout << "---*Error al eliminar*---" << endl;
            }
        }
        else {
            cout << "---*Error en la conexión*---" << endl;
        }
        cn.cerrar_conexion();
    }
};

