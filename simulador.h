#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <string>
#include <vector>

#include "caja.h"

class Particula;
class Obstaculo;
class RegistroSalida;

class Simulador {
private:
    std::vector<Particula*> particulas;
    std::vector<Obstaculo*> obstaculos;
    Caja caja;
    RegistroSalida* registro;
    double dt;
    double tiempo;
    double e;

    void detectarColisiones();
    void guardarEstado();

    Simulador(const Simulador&) = delete;
    Simulador& operator=(const Simulador&) = delete;

public:

    Simulador(const Caja& caja, double dt, double e, const std::string& archivoSalida);
    ~Simulador();
    void agregarParticula(Particula* p);
    void agregarObstaculo(Obstaculo* o);


    void ejecutar(int pasos);

    void paso();

    double getTiempo() const;
};

#endif