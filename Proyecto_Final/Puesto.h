#pragma once
#include <mysql.h>
#include <iostream>
#include <string>
#include "ConexionBD.h"

class Puesto
{
private:
	int id = 0;
	string puesto;

	//constructor
public:
	Puesto() {}

	Puesto(string pue, int i) {
		id = i;
		puesto = pue;
	};

	//METODOS
	//set (modificar)
	void setId(int i) { id = i;  }
	void setPuesto(string pue) { puesto = pue; }
	//get (mostrar)
	int getId() { return id; }
	string getPuesto() { return puesto; }

	void crear() {
		int q_estado;
		ConexionBD cn = ConexionBD();

		cn.abrirConexion();

		if (cn.getConectar()) {
			string insertar =
				"INSERT INTO puestos(puesto) VALUES('" + puesto + "')';";
			const char* i = insertar.c_str();
			//ejecutamos el query
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << "Ingreso exitoso..." << endl;
			}
			else {
				cout << "---*Error al crear*---" << endl;
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

			string consulta = "select * from puestos";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "---------------------Puestos-----------------" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << ":" << fila[1] << endl;
				}
			}
			else {
				cout << "---*Error al consultar*---" << endl;
			}
		}
		else
		{
			cout << "---*Error en la conexion*---" << endl;
		}
	}

	void actualizar() {
		int q_estado;
		ConexionBD cn = ConexionBD();

		cn.abrirConexion();
		string ii = to_string(id);
		if (cn.getConectar()) {
			string actualizar = "update puestos set = '" + puesto + "' where id_puesto = " + ii + "";
			const char* i = actualizar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << "Actualizacion Exitosa" << endl;
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
			string borrar = "delete from puestos where id_puesto = " + ii + "";
			const char* i = borrar.c_str();
			q_estado = mysql_query(cn.getConectar(), i) ;
			if (!q_estado) {
				cout << "Eliminacion Exitosa..." << endl;
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
};

