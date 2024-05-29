#pragma once

#include <mysql.h>
#include <iostream>

using namespace std;

class ConexionBD
{
private: MYSQL* conectar;
public:
	void abrirConexion() {
		conectar = mysql_init(0);
		conectar = mysql_real_connect(conectar, "localhost", "root", "123456", "db_supermercado", 3306, NULL, 0);
	}
	MYSQL* getConectar() {
		return conectar;
	}
	void cerrar_conexion() {
		mysql_close(conectar);
	}
};

