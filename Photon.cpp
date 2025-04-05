// PHYS30762 Programming in C++
// Author: 10899510
// Date: April 5th 2024
// Photon class implementation
// Implements the Photon class which stores its energy and the electrons
// created from pair production. Inherits from the abstract Particle class.

#include "Photon.h"
#include "Electron.h"
#include <iostream>

// Constructor: Initialise photon with specified energy and zero rest mass
Photon::Photon(double e)
  : Particle(0.0, e)
{
}

// Add an electron produced by pair production
void Photon::add_electron(std::shared_ptr<Electron> e)
{
  electrons.push_back(e);
}

// Return reference to vector of associated electrons
const std::vector<std::shared_ptr<Electron>>& Photon::get_electrons() const
{
  return electrons;
}

// Print energy of photon
void Photon::print_data() const
{
  std::cout << "Photon | Energy: " << energy << " keV\n";
}
