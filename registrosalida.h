#ifndef REGISTROSALIDA_H
#define REGISTROSALIDA_H

#include <fstream>
#include <string>

class Particula;


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
    void guardarPosicion(double t, Particula* p);
    void guardarColision(double t, short tipo, int idA, int idB);
};

#endif