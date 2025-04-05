// PHYS30762 Programming in C++
// Author: 10899510
// Date: April 5th 2024
// Particle header file
// Defines the abstract base class for all particles in the simulation.
// Provides access to energy and rest mass, and enforces a print interface.

#ifndef PARTICLE_H
#define PARTICLE_H

class Particle
{
protected:
  double rest_mass;  // Rest mass of the particle in keV
  double energy;     // Kinetic energy of the particle in keV

public:
  // Constructor
  Particle(double rm, double e);

  // Virtual destructor for safe polymorphism
  virtual ~Particle() = default;

  // Accessors
  double get_rest_mass() const;
  double get_energy() const;

  // Mutator
  void set_energy(double e);

  // Pure virtual method for displaying particle information
  virtual void print_data() const = 0;
};

#endif
