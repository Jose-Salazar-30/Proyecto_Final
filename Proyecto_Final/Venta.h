#pragma once
#include <mysql.h>
#include <string>
#include <ctime>
#include <iostream>
#include "ConexionBD.h"

using namespace std;

class Venta
{
private:
	int id = 0;
	int id_venta;
	int no_factura;
	string serie;
	tm fecha_factura;
	int id_cliente;
	int id_empleado;
	tm fecha_ingreso;

public:
	Venta() {}

	Venta(int nf, string s, tm ff, int ic, int ie, tm fi, int i) {
		id = i;
		no_factura = nf;
		serie = s;
		fecha_factura = ff;
		id_cliente = ic;
		id_empleado = ie;
		fecha_ingreso = fi;
	}

	//METODOS
	//set (modificar)
	void setId(int i) { id = i; }
	void setnoFactura(int nf) { no_factura = nf; }
	void setSerie(int s) { serie = s; }
	void setfecha_factura(tm ff) { fecha_factura = ff; }
	void setIdCliente(int ic) { id_cliente = ic; }
	void setIdEmpleado(int ie) { id_empleado = ie;  }
	void setfechaIngreso(tm fi) { fecha_ingreso = fi; }

	//get (Mostrar)
	int getId() { return id; }
	int getnoFactura() { return no_factura;  }
	string getSerie() { return serie; }
	tm getfechaFactura() { return fecha_factura; }
	int getidCliente() { return id_cliente; }
	int getidEmpleado() { return id_empleado; }
	tm getFechaIngreso() { return fecha_ingreso; }

	void crear() {
		int q_estado;
		ConexionBD cn = ConexionBD();

		if (cn.getConectar()) {
			string insertar = "INSERT INTO ventas(nofactura, serie, fecha_factura, id_cliente, id_empleado, fecha_ingreso) VALUES(" +
				to_string(no_factura) + ", '" + serie + "', '" + to_string(fecha_factura.tm_year + 1900) + "-" +
				to_string(fecha_factura.tm_mon + 1) + "-" + to_string(fecha_factura.tm_mday) + "', " + to_string(id_cliente) + ", " +
				to_string(id_empleado) + ", NOW())";
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
			cout << "--*Error en la conxion*--" << endl;
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
			string consulta = "SELECT * FROM ventas";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "-----------------------Ventas-----------------" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << ": " << fila[1] << ": " << fila[2] << ": " << fila[3] << ": " << fila[4] << ": " << fila[5] << ": " << fila[6] << endl;
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
			string actualizar = "UPDATE ventas SET nofactura = " + to_string(no_factura) + ", serie = '" + serie + "', fechafactura = '" +
				to_string(fecha_factura.tm_year + 1900) + "-" + to_string(fecha_factura.tm_mon + 1) + "-" + to_string(fecha_factura.tm_mday) +
				"', idcliente = " + to_string(id_cliente) + ", idempleado = " + to_string(id_empleado) + " WHERE id_venta = " + ii;
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
			string borrar = "DELETE FROM ventas WHERE id_venta = " + ii;
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

