#pragma once
#include <mysql.h>
#include <iostream>
#include <string>
#include "ConexionBD.h"

using namespace std;

class VentaDetalle
{
private:
	int id = 0;
	int id_venta_detalle;
	int id_venta;
	int id_producto;
	int cantidad;
	double precio_unitario;

public:
	
	VentaDetalle() {}

	VentaDetalle(int idv, int idp, int cant, int pu, int i) {
		id = i;
		id_venta = idv;
		id_producto = idp;
		cantidad = cant;
		precio_unitario = pu;
	}

	//METODOS
	//set (modificar)
	void setId(int i) { id = i; }
	void setIdVenta(int idv) { id_venta = idv; }
	void setIdProducto(int idp) { id_producto = idp; }
	void setCantidad(int cant) { cantidad = cant; }
	void setPrecioUnitario(double pu) { precio_unitario = pu; }

	//get (Mostrar)
	int getID() { return id; }
	int getIdVenta() { return id_venta; }
	int getIdProducto() { return id_producto; }
	int getCantidad() { return cantidad; }
	int getPrecioUnitario() { return precio_unitario; }

	void crear() {
		int q_estado;
		ConexionBD cn = ConexionBD();

		cn.abrirConexion();

		if (cn.getConectar()) {
			string insertar = "INSERT INTO ventas_detalle(id_venta, id_producto, cantidad, precio_unitario) VALUES(" +
				to_string(id_venta) + ", " + to_string(id_producto) + ", " + to_string(cantidad) + ", " + to_string(precio_unitario) + ")";
			const char* i = insertar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << "Ingreso Exitoso..." << endl;
			}
			else {
				cout << "---*Error al ingresar*---" << endl;
			}
		}
		else {
			cout << "---*Error en la conexion*---" << endl;
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
			string consulta = "SELECT * FROM ventas_detalle";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "-----------------------Ventas Detalle-----------------" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << ": " << fila[1] << ": " << fila[2] << ": " << fila[3] << ": " << fila[4] << endl;
				}
			}
			else {
				cout << "---*Error al consultar*---" << endl;
			}
		}
		else {
			cout << "---*Error en la conexion*---" << endl;
		}
	}


	void actualizar() {
		int q_estado;
		ConexionBD cn = ConexionBD();

		cn.abrirConexion();
		string ii = to_string(id);
		if (cn.getConectar()) {
			string actualizar = "UPDATE ventas_detalle SET idVenta = " + to_string(id_venta) + ", idProducto = " + to_string(id_producto) +
				", cantidad = " + to_string(cantidad) + ", precio_unitario = " + to_string(precio_unitario) +
				" WHERE id_venta_detalle = " + ii;
			const char* i = actualizar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << "Actualizacion Exitosa..." << endl;
			}
			else {
				cout << "---*Error al actualizar*---" << endl;
			}
		}
		else {
			cout << "---*Error en la conexion*---" << endl;
		}
		cn.cerrar_conexion();
	}


	void borrar() {
		int q_estado;
		ConexionBD cn = ConexionBD();

		cn.abrirConexion();
		string ii = to_string(id);
		if (cn.getConectar()) {
			string borrar = "DELETE FROM ventas_detalle WHERE id_venta_detalle = " + ii;
			const char* i = borrar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << "Eliminacion exitosa" << endl;
			}
			else {
				cout << "---*Error al eliminar*---" << endl;
			}
		}
		else {
			cout << "---*Error en la conexion*---" << endl;
		}
		cn.cerrar_conexion();
	}
};

