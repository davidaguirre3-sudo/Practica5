#include "registrosalida.h"

#include <iomanip>

RegistroSalida::RegistroSalida(const std::string& nombreArchivo)
    : archivo(nombreArchivo.c_str())
{
    if (archivo.is_open()) {
        archivo << std::fixed << std::setprecision(4);
        archivo << "# P,t,id,x,y,radio\n";
        archivo << "# C,t,tipo,idA,idB   (tipo: 0=pared, 1=obstaculo, 2=particula)\n";
    }
}

RegistroSalida::~RegistroSalida()
{
    if (archivo.is_open())
        archivo.close();
}

bool RegistroSalida::estaAbierto() const
{
    return archivo.is_open();
}

void RegistroSalida::guardarColision(double t, short tipo, int idA, int idB)
{
    if (!archivo.is_open())
        return;
    archivo << "C," << t << ',' << tipo << ',' << idA << ',' << idB << '\n';
}