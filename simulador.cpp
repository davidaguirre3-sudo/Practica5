#include "simulador.h"
#include "particula.h"
#include "obstaculo.h"
#include "registrosalida.h"

#include <iostream>

// ---------------- Paso 4: base ----------------

Simulador::Simulador(const Caja& caja, double dt, double e, const std::string& archivoSalida)
    : caja(caja), registro(new RegistroSalida(archivoSalida)), dt(dt), tiempo(0.0), e(e)
{
}

Simulador::~Simulador()
{
    for (size_t i = 0; i < particulas.size(); i++)
        delete particulas[i];
    for (size_t i = 0; i < obstaculos.size(); i++)
        delete obstaculos[i];
    delete registro;
}

void Simulador::agregarParticula(Particula* p)
{
    particulas.push_back(p);
}

void Simulador::agregarObstaculo(Obstaculo* o)
{
    obstaculos.push_back(o);
}

void Simulador::guardarEstado()
{
    for (size_t i = 0; i < particulas.size(); i++) {
        if (particulas[i]->estaActiva())
            registro->guardarPosicion(tiempo, particulas[i]);
    }
}

void Simulador::ejecutar(int pasos)
{
    if (!registro->estaAbierto()) {
        std::cerr << "Simulador: no se pudo abrir el archivo de salida." << std::endl;
        return;
    }
    guardarEstado();
    for (int i = 0; i < pasos; i++)
        paso();
}

void Simulador::paso()
{
    for (size_t i = 0; i < particulas.size(); i++) {
        if (particulas[i]->estaActiva())
            particulas[i]->mover(dt);
    }
    tiempo += dt;
    detectarColisiones();


    guardarEstado();
}

double Simulador::getTiempo() const
{
    return tiempo;
}


void Simulador::detectarColisiones()
{
}