// PHYS30762 Programming in C++
// Author: 10899510
// Date: April 5th 2024
// Positron header file
// Defines the Positron class, a derived type of Particle representing
// the antiparticle of the electron. Includes a print method for energy.

#ifndef POSITRON_H
#define POSITRON_H

#include "Particle.h"
#include <iostream>

// Positron class inherits from Particle
class Positron : public Particle
{
public:
  Positron(double e) : Particle(0.511, e) {}

  // Print positron energy
  void print_data() const override
  {
    std::cout << "Positron | Energy: " << energy << " keV\n";
  }
};

#endif
