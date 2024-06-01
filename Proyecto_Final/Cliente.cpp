#include "Cliente.h"
#include <cstdio>

// Constructor
Cliente::Cliente(string nom, string ape, string n, unsigned int gen, string tel, string correo, tm fi, int i) {
    id = i;
    nombres = nom;
    apellidos = ape;
    nit = n;
    genero = gen;
    telefono = tel;
    correo_electronico = correo;
    fecha_ingreso = fi;
}

// Setters
void Cliente::setId(int i) { id = i; }
void Cliente::setNombres(string nom) { nombres = nom; }
void Cliente::setApellidos(string ape) { apellidos = ape; }
void Cliente::setNit(string n) { nit = n; }
void Cliente::setGenero(unsigned int gen) { genero = gen; }
void Cliente::setTelefono(string tel) { telefono = tel; }
void Cliente::setCorreoElectronico(string correo) { correo_electronico = correo; }
void Cliente::setFechaIngreso(tm fi) { fecha_ingreso = fi; }

// Getters
int Cliente::getId() { return id; }
string Cliente::getNombres() { return nombres; }
string Cliente::getApellidos() { return apellidos; }
string Cliente::getNit() { return nit; }
unsigned int Cliente::getGenero() { return genero; }
string Cliente::getTelefono() { return telefono; }
string Cliente::getCorreoElectronico() { return correo_electronico; }
tm Cliente::getFechaIngreso() { return fecha_ingreso; }

// CRUD Methods
void Cliente::crear() {
    int q_estado;
    ConexionBD cn = ConexionBD();

    if (cn.getConectar()) {
        string insertar = "INSERT INTO clientes(nombres, apellidos, nit, genero, telefono, correo_electronico, fecha_ingreso) VALUES('" +
            nombres + "','" + apellidos + "','" + nit + "','" + to_string(genero) + "','" + telefono + "','" + correo_electronico +
            "', NOW())";
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

void Cliente::leer() {
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

void Cliente::actualizar() {
    int q_estado;
    ConexionBD cn = ConexionBD();

    cn.abrirConexion();
    string ii = to_string(id);
    if (cn.getConectar()) {
        string actualizar = "update clientes set nombres = '" + nombres + "', apellidos ='" + apellidos + "', nit = '"
            + nit + "', genero ='" + to_string(genero) + "', telefono = '" + telefono + "', correo_electronico = '"
            + correo_electronico + "', fecha_ingreso = NOW() where id_cliente = " + ii;
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

void Cliente::borrar() {
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

// Custom Methods
bool Cliente::buscarPorNIT(string n) {
    int q_estado;
    ConexionBD cn = ConexionBD();
    MYSQL_ROW fila;
    MYSQL_RES* resultado;

    cn.abrirConexion();
    if (cn.getConectar()) {
        string consulta = "SELECT * FROM clientes WHERE nit = '" + n + "'";
        const char* c = consulta.c_str();
        q_estado = mysql_query(cn.getConectar(), c);
        if (!q_estado) {
            resultado = mysql_store_result(cn.getConectar());
            if (fila = mysql_fetch_row(resultado)) {
                // Cliente encontrado
                id = stoi(fila[0]);
                nombres = fila[1];
                apellidos = fila[2];
                nit = fila[3];
                genero = stoi(fila[4]);
                telefono = fila[5];
                correo_electronico = fila[6];
                // Parsear fecha_ingreso
                string fecha = fila[7];
                /*sscanf(fecha.c_str(), "%d-%d-%d", &fecha_ingreso.tm_year, &fecha_ingreso.tm_mon, &fecha_ingreso.tm_mday);
                fecha_ingreso.tm_year -= 1900;
                fecha_ingreso.tm_mon -= 1;*/
                if (sscanf_s(fecha.c_str(), "%d-%d-%d", &fecha_ingreso.tm_year, &fecha_ingreso.tm_mon, &fecha_ingreso.tm_mday) == 3) {
                    // Conversion successful
                }
                else {
                    // Conversion failed
                }
                return true;
            }
        }
        else {
            cout << "---*Error al consultar*---" << endl;
        }
    }
    else {
        cout << "---*Error en la conexion*---" << endl;
    }
    cn.cerrar_conexion();
    return false;
}

bool Cliente::validarNIT(string n) {
    // Validar formato de NIT (simplificado) o caso especial "C/F"
    if (n == "C/F") {
        return true;
    }
    // formato NIT como "1234567-8"
    if (n.length() != 9 || n[7] != '-') {
        return false;
    }
    for (int i = 0; i < 7; i++) {
        if (!isdigit(n[i])) {
            return false;
        }
    }
    if (!isdigit(n[8])) {
        return false;
    }
    return true;
}
