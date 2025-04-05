// PHYS30762 Programming in C++
// Author: 10899510
// Date: April 5th 2024
// Electron header file
// Declares the Electron class, which models an electron capable of emitting photons.
// Inherits from the Particle base class and manages photon emission via smart pointers.

#ifndef ELECTRON_H
#define ELECTRON_H

#include "Particle.h"
#include <vector>
#include <memory>

class Photon;

// Inherits Electron Class from the Particle class and includes photon storage and emission functionality.
class Electron : public Particle
{
private:
  std::vector<std::shared_ptr<Photon>> photons;

public:
  Electron(double e);
  void add_photon(std::shared_ptr<Photon> p);
  std::shared_ptr<Photon> radiate();
  void print_data() const override;
};

#endif
