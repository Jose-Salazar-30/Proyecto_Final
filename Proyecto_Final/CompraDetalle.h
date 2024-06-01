#pragma once
#include <mysql.h>
#include <string>
#include <iostream>
#include "ConexionBD.h"

using namespace std;

class CompraDetalle
{
private:
	int id = 0;
	int id_compra;
	int id_producto;
	int cantidad;
	double precio_costo_unitario;

public:
	CompraDetalle() {}

	CompraDetalle(int ic, int ip, int cant, double pcu, int i) {
		id = i;
		id_compra = ic;
		id_producto = ip;
		cantidad = cant;
		precio_costo_unitario = pcu;
	}

	//METODOS
	//set (modificar)
	void setId(int i) { id = i; }
	void setIdCompra(int ic) { id_compra = ic; }
	void setIdProducto(int ip) { id_producto = ip; }
	void setCantidad(int cant) { cantidad = cant; }
	void setPrecioCostoUnitario(double pcu) { precio_costo_unitario = pcu; }

	//get (Mostrar)
	int getId() { return id; }
	int getIdCompra() { return id_compra; }
	int getIdProducto() { return id_producto; }
	int getCantidad() { return cantidad; }
	double getPrecioCostoUnitario() { return precio_costo_unitario; }

	void crear() {
		int q_estado;
		ConexionBD cn = ConexionBD();

		if (cn.getConectar()) {
			string insertar = "INSERT INTO compras_detalle(id_compra, id_producto, cantidad, precio_costo_unitario) VALUES(" +
				to_string(id_compra) + ", " + to_string(id_producto) + ", " + to_string(cantidad) + ", " + to_string(precio_costo_unitario) + ")";
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
			string consulta = "SELECT * FROM compras_detalle";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "-----------------------Detalles de Compras-----------------" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << ": " << fila[1] << ": " << fila[2] << ": " << fila[3] << ": " << fila[4] << endl;
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
			string actualizar = "UPDATE compras_detalle SET id_compra = " + to_string(id_compra) + ", id_producto = " + to_string(id_producto) +
				", cantidad = " + to_string(cantidad) + ", precio_costo_unitario = " + to_string(precio_costo_unitario) +
				" WHERE id_compra_detalle = " + ii;
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
			string borrar = "DELETE FROM compras_detalle WHERE id_compra_detalle = " + ii;
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

