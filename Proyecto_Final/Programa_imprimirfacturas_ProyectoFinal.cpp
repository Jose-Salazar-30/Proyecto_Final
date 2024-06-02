#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;
// Definicion de la clase de Producto
class Producto {
public:
	string codigo;
	string nombre;
	double precio;
	
	Producto(string c, string n, double p) : codigo(c), nombre(n), precio (p) {}
};

// Funcion para imprimir la factura
void imprimirFactura(int noFactura, string fecha, string nit, string cliente, vector<Producto>& productos, double total) {
	cout << "No Factura: "<< noFactura << "Fecha: " << fecha << endl;
	cout << "Nit: "<< nit << endl;
	cout << "Cliente: "<< cliente << endl;
	cout << "Direccion: Ciudad" << endl;
	cout << "PRODUCTOS: "<< endl;
	for (const auto& producto : productos) {
		cout << producto.codigo << "-" << producto.nombre << " Q " << producto.precio << endl;
	}
	cout << "Total : Q " << total << endl;
	cout << "Gracias por su compra. " << endl;
}

int main() {
	// Creacion de algunos productos
	Producto producto1("101", "Sopa Instantanea marca Laky", 2.5);
	Producto producto2("122", "Corn flakes marca Kellogg's" 25.0);

	// Lista de productos en el carrito
	int vector<Procucto> carrito;
	int carrito.push_back(producto1);
	int carrito.push_back(producto2);
	int carrito.push_back(producto3);
	
	// Calculo del Total
	double total = 0;
	for (const auto& producto : carrito) {
		total += producto.precio;
	}
	
	// Obtencion de la fecha actual
	time_t now = time(0);
	tm *ltm = localtime(&now);
	string fecha = to_string(1 + ltm->tm_mon) + to_string(ltm->)tm_mday) + "/" + to_string(1900 + ltm-tm_year);
	
	// Impresion de la factura
	imprimirFactura(1, fecha, "42124840"), "Brayner Garcia", carrito, total);	

	return 0;
}
