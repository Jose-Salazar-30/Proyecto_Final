#include <iostream>
#include <string>

int main() {
	// Codigo para abrir la caja de pago
	std::string codigo_correcto = "1234";
	std::string codigo_ingresado;
	
	std::cout << "Ingrese el codigo para abrir la caja de pago: ";
	std::cin >> codigo_ingresado;
	
	if (codigo_ingresado == codigo_correcto){
		std::<< "Caja de pago abierta. Puede proceder con la compra." << std::endl;
	} else {
		std:: << "Codigo incorrecto. La caja de pago permanece cerrada." << std::endl;
	}
	
	return 0;
}
