#include <iostream>
#include "registrosalida.h"

int main()
{
    RegistroSalida registro("salida.txt");
    if (!registro.estaAbierto()) {
        std::cout << "No se pudo abrir el archivo" << std::endl;
        return 1;
    }

    registro.guardarColision(1.2345, COLISION_PARED, 0, -1);
    registro.guardarColision(2.5, COLISION_OBSTACULO, 1, 3);
    registro.guardarColision(3.0, COLISION_PARTICULA, 0, 2);

    std::cout << "Colisiones guardadas" << std::endl;
    return 0;
}