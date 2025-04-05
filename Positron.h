#ifndef POSITRON_H
#define POSITRON_H

#include "Particle.h"
#include <iostream>

class Positron : public Particle {
public:
    Positron(double e) : Particle(0.511, e) {}

    void printData() const override {
        std::cout << "Positron | Energy: " << energy << " keV\n";
    }
};

#endif