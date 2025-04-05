// PHYS30762 Programming in C++
// Author: 10899510
// Date: April 5th 2024
// Particle class implementation
// Implements the base functionality for all particles in the simulation,
// including storing and modifying rest mass and energy values.

#include "Particle.h"

// Constructor: Initialise particle with rest mass and kinetic energy
Particle::Particle(double rm, double e)
  : rest_mass(rm), energy(e)
{
}

// Getter for rest mass
double Particle::get_rest_mass() const
{
  return rest_mass;
}

// Getter for energy
double Particle::get_energy() const
{
  return energy;
}

// Setter for energy
void Particle::set_energy(double e)
{
  energy = e;
}
