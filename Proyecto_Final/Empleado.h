#pragma once
#include <mysql.h>
#include <string>
#include <iostream>
#include "ConexionBD.h"

using namespace std;

class Empleado
{
private:
	int id = 0;
	string nombres;
	string apellidos;
	string direccion;
	string telefono;
	string DPI;
	unsigned int genero : 1;
	tm fecha_nacimiento;
	int id_puesto;
	tm fecha_inicio_labores;
	tm fecha_ingreso;


public:

	Empleado() {}

	Empleado(string n, string a, string d, string t, string dpi, bool g, tm fn, int ip, tm fil, tm fi, int i) {
		id = i;
		nombres = n;
		apellidos = a;
		direccion = d;
		telefono = t;
		DPI = dpi;
		genero = g;
		fecha_nacimiento = fn;
		id_puesto = ip;
		fecha_inicio_labores = fil;
		fecha_ingreso = fi;
	}

	//Metodo SET
	void setId(int i) { id = i; }
	void setNombres(string n) { nombres = n; }
	void setApellidos(string a) { apellidos = a; }
	void setDireccion(string d) { direccion = d; }
	void setTelefono(string t) { telefono = t; }
	void setDPI(string dpi) { DPI = dpi; }
	void setGenero(unsigned int g) { genero = g; }
	void setFechaNacimiento(tm fn) { fecha_nacimiento = fn; }
	void setIdPuesto(int ip) { id_puesto = ip; }
	void setFechaInicioLabores(tm fil) { fecha_inicio_labores = fil; }
	void setFechaIngreso(tm fi) { fecha_ingreso = fi; }

	//Metodo GET
	int getIdEmpleado() { return id; }
	string getNombres() { return nombres; }
	string getApellidos() { return apellidos; }
	string getDireccion() { return direccion; }
	string getTelefono() { return telefono; }
	string getDPI() { return DPI; }
	unsigned int getGenero() { return genero; }
	tm getFechaNacimiento() { return fecha_nacimiento; }
	int getIdPuesto() { return id_puesto; }
	tm getFechaInicioLabores() { return fecha_inicio_labores; }
	tm getFechaIngreso() { return fecha_ingreso; }

	//CRUD Metodos
	void crear() {
		int q_estado;
		ConexionBD cn = ConexionBD();

		if (cn.getConectar()) {
			string insertar = "INSERT INTO empleados(nombres, apellidos, direccion, telefono, DPI, genero, fecha_nacimiento, id_puesto, fecha_inicio_labores, fecha_ingreso) VALUES('" +
				nombres + "', '" + apellidos + "', '" + direccion + "', '" + telefono + "', '" + DPI + "', " + to_string(genero) + ", '" +
				to_string(fecha_nacimiento.tm_year + 1900) + "-" + to_string(fecha_nacimiento.tm_mon + 1) + "-" + to_string(fecha_nacimiento.tm_mday) + "', " +
				to_string(id_puesto) + ", '" + to_string(fecha_inicio_labores.tm_year + 1900) + "-" + to_string(fecha_inicio_labores.tm_mon + 1) + "-" +
				to_string(fecha_inicio_labores.tm_mday) + "', NOW())";
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
			string consulta = "SELECT * FROM empleados";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "-----------------------Empleados-----------------" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << ": " << fila[1] << ": " << fila[2] << ": " << fila[3] << ": " << fila[4] << ": " << fila[5] << ": " << fila[6] << ": " << fila[7] << ": " << fila[8] << ": " << fila[9] << ": " << fila[10] << endl;
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
            string actualizar = "UPDATE empleados SET nombres = '" + nombres + "', apellidos = '" + apellidos +
                "', direccion = '" + direccion + "', telefono = '" + telefono + "', DPI = '" + DPI + "', genero = " +
                to_string(genero) + ", fecha_nacimiento = '" + to_string(fecha_nacimiento.tm_year + 1900) + "-" +
                to_string(fecha_nacimiento.tm_mon + 1) + "-" + to_string(fecha_nacimiento.tm_mday) + 
                "', idPuesto = " + to_string(id_puesto) + ", fecha_inicio_labores = '" + to_string(fecha_inicio_labores.tm_year + 1900) +
                "-" + to_string(fecha_inicio_labores.tm_mon + 1) + "-" + to_string(fecha_inicio_labores.tm_mday) +
                "' WHERE idEmpleado = " + ii;
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
			string borrar = "DELETE FROM empleados WHERE idEmpleado = " + ii);
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

