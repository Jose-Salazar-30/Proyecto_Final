#pragma once
#include <mysql.h>
#include <iostream>
#include <string>
#include <ctime>
#include "ConexionBD.h"

using namespace std;

class Cliente
{
private:
	int id = 0;
	string nombres;
	string apellidos;
	string nit;
	unsigned int genero : 1;
	string telefono;
	string correo_electronico;
	tm fecha_ingreso;

	//constructor
public:
	Cliente() {}

	Cliente(string nom, string ape, string n, unsigned int gen, string tel, string correo, tm fi, int i) {
		id = i;
		nombres = nom;
		apellidos = ape;
		nit = n;
		genero = gen;
		telefono = tel;
		correo_electronico = correo;
		fecha_ingreso = fi;
	};

	//METODOS
	//set (modificar)
	void setId(int i) { id = i; }
	void setNombres(string nom) { nombres = nom; }
	void setApellidos(string ape) { apellidos = ape; }
	void setNit(string n) { nit = n; }
	void setGenero(unsigned int gen) { genero = gen; }
	void setTelefono(string tel) { telefono = tel; }
	void setCorreoElectronico(string correo) { correo_electronico = correo; }
	void setFechaIngreso(tm fi) { fecha_ingreso = fi; }
	//get (mostrar)
	int getId() { return id; }
	string getNombres() { return nombres; }
	string getApellidos() { return apellidos; }
	string getNit() { return nit; }
	unsigned int getGenero() { return genero; }
	string getTelefono() { return telefono; }
	string getCorreoElectronico() { return correo_electronico; }
	tm getFechaIngreso() { return fecha_ingreso; }

	void crear() {
		int q_estado;
		ConexionBD cn = ConexionBD();

		if (cn.getConectar()) {
			string insertar =
				"INSERT INTO clientes(nombres, apellidos, nit, genero, telefono, correo_electronico, fecha_ingreso)	VALUES('" +
				nombres + "','" + apellidos + "','" + nit + "','" + to_string(genero) + "','" + telefono + "','" + correo_electronico +
				"','" + to_string(fecha_ingreso.tm_year + 1900) + "-" + to_string(fecha_ingreso.tm_mon + 1) + "-" + to_string(fecha_ingreso.tm_mday) + "')";
		
			const char* i = insertar.c_str();
			//Ejecutar el query
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

			string consulta = "select * from clientes";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
	
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "-----------------------Clientes-----------------" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << ":" << fila[1] << ":" << fila[2] <<
						":" << fila[3] << ":" << fila[4] << ":" << fila[5] << ":" << fila[6] << ":" << fila[7] << endl;
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
			string actualizar = "update clientes set nombres = '" + nombres + "', apellidos ='" + apellidos + "', nit = '"
				+ nit + "', genero ='" + to_string(genero) + "', telefono = '" + telefono + "', correo_electronico = '"
				+ correo_electronico + "', fecha_ingreso = '" + to_string(fecha_ingreso.tm_year + 1900) + "-" + to_string(fecha_ingreso.tm_mon + 1)
				+ "-" + to_string(fecha_ingreso.tm_mday) + "' where id_cliente = " + ii;
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
			string borrar = "delete from clientes where id_cliente = " + ii;
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

