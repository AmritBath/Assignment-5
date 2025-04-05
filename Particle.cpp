#include "Particle.h"

Particle::Particle(double rm, double e) : rest_mass(rm), energy(e) {}

double Particle::getRestMass() const { return rest_mass; }
double Particle::getEnergy() const { return energy; }
void Particle::setEnergy(double e) { energy = e; }
