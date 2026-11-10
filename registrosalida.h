#ifndef REGISTROSALIDA_H
#define REGISTROSALIDA_H

#include <fstream>
#include <string>

const short COLISION_PARED = 0;
const short COLISION_OBSTACULO = 1;
const short COLISION_PARTICULA = 2;

class RegistroSalida {
private:
    std::ofstream archivo;

public:
    RegistroSalida(const std::string& nombreArchivo);
    ~RegistroSalida();

    bool estaAbierto() const;

    void guardarColision(double t, short tipo, int idA, int idB);
};

#endif