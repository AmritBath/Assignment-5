// PHYS30762 Programming in C++
// Author: 10899510
// Date: April 5th 2024
// Electron class implementation
// This file contains the implementation of the Electron class, which represents an electron
// in the simulation. The Electron class is responsible for managing the energy of the electron
// and the photons it can emit. It also provides methods to add photons, radiate them, and print
// the electron's data.

#include "Electron.h"
#include "Photon.h"
#include <iostream>

#define PINKRED "\033[38;5;198m"
#define RESET   "\033[0m"

// Initialises an electron with a fixed rest mass (0.511 MeV) and given kinetic energy.
Electron::Electron(double e)
  : Particle(0.511, e)
{
}

// Adds a photon to the electron's list of radiatable photons.
void Electron::add_photon(std::shared_ptr<Photon> p)
{
  photons.push_back(p);
}

// Radiates a photon from the electron, if available.
// Returns the last photon in the list and removes it from storage.
// If no photons are available, prints a warning and returns nullptr.
std::shared_ptr<Photon> Electron::radiate()
{
  if(photons.empty())
  {
    std::cout << PINKRED << "Electron has no photons to radiate.\n" << RESET;
    return nullptr;
  }

  auto p = photons.back();
  photons.pop_back();
  return p;
}

// Prints the current energy of the electron and the number of photons it holds.
void Electron::print_data() const
{
  std::cout << "Electron | Energy: " << energy << " keV"
            << ", Photons: " << photons.size() << "\n";
}
