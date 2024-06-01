#pragma once
#include <mysql.h>
#include <string>
#include <iostream>
#include "ConexionBD.h"

using namespace std;

class Compras
{
private:
	int id = 0;
	int no_orden_compra;
	int id_proveedor;
	tm fecha_orden;
	tm fecha_ingreso;

public:
	Compras() {}

	Compras(int nc, int idp, tm fo, tm fi, int i) {
		id = i;
		no_orden_compra = nc;
		id_proveedor = idp;
		fecha_orden = fo;
		fecha_ingreso = fi;
	}

	//METODOS
	//set (modificar)
	void setId(int i) { id = i; }
	void setnoOrdenCompra(int nc) { no_orden_compra = nc; }
	void setIdProveedor(int idp) { id_proveedor = idp; }
	void setFechaOrden(tm fo) { fecha_orden = fo; }
	void setFechaIngreso(tm fi) { fecha_ingreso = fi; }

	//get (Mostrar)
	int getId() { return id; }
	int getnoOrdenCompra() { return no_orden_compra; }
	int getid_proveedor() { return id_proveedor; }
	tm getFecha_orden() { return fecha_orden; }
	tm getFechaIngreso() { return fecha_ingreso; }

	void crear() {
		int q_estado;
		ConexionBD cn = ConexionBD();

		if (cn.getConectar()) {
			string insertar = "INSERT INTO compras(no_orden_compra, idproveedor, fecha_orden, fechaingreso) VALUES(" +
				to_string(no_orden_compra) + ", " + to_string(id_proveedor) + ", '" +
				to_string(fecha_orden.tm_year + 1900) + "-" + to_string(fecha_orden.tm_mon + 1) + "-" + to_string(fecha_orden.tm_mday) + "', NOW())";
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
			string consulta = "SELECT * FROM compras";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "-----------------------Compras-----------------" << endl;
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
			string actualizar = "UPDATE compras SET no_orden_compra = " + to_string(no_orden_compra) + ", idproveedor = " + to_string(id_proveedor) + ", fecha_orden = '" +
				to_string(fecha_orden.tm_year + 1900) + "-" + to_string(fecha_orden.tm_mon + 1) + "-" + to_string(fecha_orden.tm_mday) + "' WHERE idcompra = " + ii;
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
			string borrar = "DELETE FROM compras WHERE idcompra = " + ii;
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

