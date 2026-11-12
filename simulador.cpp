#include "simulador.h"
#include "particula.h"
#include "obstaculo.h"
#include "colisiones.h"
#include "registrosalida.h"

#include <iostream>

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
    for (size_t i = 0; i < particulas.size(); i++) {
        Particula* p = particulas[i];
        if (p->estaActiva() && choqueConPared(p, caja))
            registro->guardarColision(tiempo, COLISION_PARED, p->getId(), -1);
    }

    for (size_t i = 0; i < particulas.size(); i++) {
        Particula* p = particulas[i];
        if (!p->estaActiva())
            continue;
        for (size_t j = 0; j < obstaculos.size(); j++) {
            if (choqueConObstaculo(p, obstaculos[j], e))
                registro->guardarColision(tiempo, COLISION_OBSTACULO, p->getId(), (int)j);
        }
    }

    for (size_t i = 0; i < particulas.size(); i++) {
        Particula* a = particulas[i];
        if (!a->estaActiva())
            continue;
        for (size_t j = i + 1; j < particulas.size(); j++) {
            Particula* b = particulas[j];
            if (!b->estaActiva())
                continue;
            if (choqueEntreParticulas(a, b))
                registro->guardarColision(tiempo, COLISION_PARTICULA, a->getId(), b->getId());
        }
    }
}