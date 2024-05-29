#pragma once
#include <mysql.h>
#include <iostream>
#include <string>
#include "ConexionBD.h"

using namespace std;

class Proveedor
{
private:
	int id = 0;
	string proveedor;
	string nit;
	string direccion;
	string telefono;

	//constructor
public:
	Proveedor() {}

	Proveedor(string prov, string n, string dir, string tel, int i) {
		id = i;
		proveedor = prov;
		nit = n;
		direccion = dir;
		telefono = tel;
	};

	//METODOS
	//set (modificar)
	void setId(int i) { id = i; }
	void setProveedor(string prov) { proveedor = prov; }
	void setNit(string n) { nit = n; }
	void setDireccion(string dir) { direccion = dir; }
	void setTelefono(string tel) { telefono = tel; }
	//get (mostrar)
	int getId() { return id; }
	string getProveedor() { return proveedor; }
	string getNit() { return nit; }
	string getDireccion() { return direccion; }
	string getTelefono() { return telefono; }

	void crear() {
		int q_estado;
		ConexionBD cn = ConexionBD();

		if (cn.getConectar()) {
			string insertar =
				"INSERT INTO proveedores(proveedor,nit,direccion, telefono) VALUES('" + proveedor + "','" + nit + "','" + direccion + "'," + telefono + "')';";
			const char* i = insertar.c_str();
			//ejectuar el query
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << "Ingreso Exitoso..." << endl;
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

			string consulta = "select * from proveedores";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "-----------------------Proveedores----------" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << ":" << fila[1] << ":" << fila[2] << ":" << fila[3] << endl;
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
			string actualizar = "update proveedores set proveedor = '" + proveedor +
				"', nit ='" + nit + "', direccion ='" + direccion + "', telefono = '" + telefono + "' where id_proveedor = " + ii + "";
			const char* i = actualizar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << "Actuliazacion Exitosa..." << endl;
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
			string borrar = "delete from proveedores where id_proveedor = " + ii + "";
			const char* i = borrar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << "Eliminacion exitosa..." << endl;
			}
			else {
				cout << "---*Error al borrar*---" << endl;
			}
		}
		else {
			cout << "---*Error en la conexion*---" << endl;
		}
		cn.cerrar_conexion();
	}

};

