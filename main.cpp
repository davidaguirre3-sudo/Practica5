#include <iostream>
#include "registrosalida.h"
#include "particula.h"

int main()
{
    RegistroSalida registro("salida.txt");
    if (!registro.estaAbierto()) {
        std::cout << "No se pudo abrir el archivo" << std::endl;
        return 1;
    }

    // id, x, y, vx, vy, masa, radio
    Particula p0(0, 10.0, 10.0, 8.0, 5.0, 1.0, 1.5);
    Particula p1(1, 90.0, 20.0, -6.0, 3.0, 2.0, 2.0);

    registro.guardarPosicion(0.0, &p0);
    registro.guardarPosicion(0.0, &p1);

    p0.mover(0.01);
    p1.mover(0.01);

    registro.guardarPosicion(0.01, &p0);
    registro.guardarPosicion(0.01, &p1);
    registro.guardarColision(1.2345, COLISION_PARED, 0, -1);

    std::cout << "Posiciones guardadas" << std::endl;
    return 0;
}