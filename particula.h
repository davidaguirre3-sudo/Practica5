#ifndef PARTICULA_H
#define PARTICULA_H

class Particula {
private:
    int id;
    double x, y, vx, vy, masa, radio;
    bool activa;

public:
    Particula(int id, double x, double y, double vx, double vy, double masa, double radio)
        : id(id), x(x), y(y), vx(vx), vy(vy), masa(masa), radio(radio), activa(true) {}

    int getId() const { return id; }
    double getX() const { return x; }
    double getY() const { return y; }
    double getRadio() const { return radio; }
    bool estaActiva() const { return activa; }

    void mover(double dt) { x += vx * dt; y += vy * dt; }
};

#endif