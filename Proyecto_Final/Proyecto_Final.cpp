#include <iostream>
#include <ctime>
#include "Cliente.h"

using namespace std;

void mostrarMenu() {
    cout << "1. Crear Cliente" << endl;
    cout << "2. Leer Clientes" << endl;
    cout << "3. Actualizar Cliente" << endl;
    cout << "4. Borrar Cliente" << endl;
    cout << "5. Buscar Cliente por NIT" << endl;
    cout << "6. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    Cliente cliente;
    int opcion;
    string nombres, apellidos, nit, telefono, correo;
    unsigned int genero;
    tm fecha_ingreso = {};
    int id;

    // Declare and initialize 't' outside the switch statement
    time_t t;

    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(); // Para limpiar el buffer de entrada

        switch (opcion) {
        case 1:
            cout << "Ingrese nombres: ";
            getline(cin, nombres);
            cout << "Ingrese apellidos: ";
            getline(cin, apellidos);
            cout << "Ingrese NIT: ";
            getline(cin, nit);
            cout << "Ingrese genero (0: Femenino, 1: Masculino): ";
            cin >> genero;
            cin.ignore();
            cout << "Ingrese telefono: ";
            getline(cin, telefono);
            cout << "Ingrese correo electronico: ";
            getline(cin, correo);

            // Obtener fecha actual para fecha_ingreso
            t = time(0);
            localtime_s(&fecha_ingreso, &t);

            cliente = Cliente(nombres, apellidos, nit, genero, telefono, correo, fecha_ingreso, 0);
            cliente.crear();
            break;

        case 2:
            cliente.leer();
            break;

        case 3:
            cout << "Ingrese ID del cliente a actualizar: ";
            cin >> id;
            cin.ignore();
            cliente.setId(id);
            cout << "Ingrese nuevos nombres: ";
            getline(cin, nombres);
            cliente.setNombres(nombres);
            cout << "Ingrese nuevos apellidos: ";
            getline(cin, apellidos);
            cliente.setApellidos(apellidos);
            cout << "Ingrese nuevo NIT: ";
            getline(cin, nit);
            cliente.setNit(nit);
            cout << "Ingrese nuevo genero (0: Femenino, 1: Masculino): ";
            cin >> genero;
            cin.ignore();
            cliente.setGenero(genero);
            cout << "Ingrese nuevo telefono: ";
            getline(cin, telefono);
            cliente.setTelefono(telefono);
            cout << "Ingrese nuevo correo electronico: ";
            getline(cin, correo);
            cliente.setCorreoElectronico(correo);
            // Obtener fecha actual para fecha_ingreso
            t = time(0);
            localtime_s(&fecha_ingreso, &t);
            cliente.setFechaIngreso(fecha_ingreso);
            cliente.actualizar();
            break;

        case 4:
            cout << "Ingrese ID del cliente a borrar: ";
            cin >> id;
            cliente.setId(id);
            cliente.borrar();
            break;

        case 5:
            cout << "Ingrese NIT del cliente a buscar: ";
            getline(cin, nit);
            if (cliente.buscarPorNIT(nit)) {
                cout << "Cliente encontrado: " << endl;
                cout << "ID: " << cliente.getId() << endl;
                cout << "Nombres: " << cliente.getNombres() << endl;
                cout << "Apellidos: " << cliente.getApellidos() << endl;
                cout << "NIT: " << cliente.getNit() << endl;
                cout << "Genero: " << (cliente.getGenero() ? "Masculino" : "Femenino") << endl;
                cout << "Telefono: " << cliente.getTelefono() << endl;
                cout << "Correo Electronico: " << cliente.getCorreoElectronico() << endl;
                cout << "Fecha Ingreso: " << cliente.getFechaIngreso().tm_year + 1900 << "-"
                    << cliente.getFechaIngreso().tm_mon + 1 << "-"
                    << cliente.getFechaIngreso().tm_mday << endl;
            }
            else {
                cout << "Cliente no encontrado." << endl;
            }
            break;

        case 6:
            cout << "Saliendo..." << endl;
            break;

        default:
            cout << "Opción no valida." << endl;
        }
    } while (opcion != 6);

    return 0;
}




/*#include <iostream>
#include <mysql.h>

using namespace std;

int main()
{

	cout << "Hola Mundo!!!!" << endl;

	system("pause");
    return 0;
}*/