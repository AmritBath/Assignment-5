// PHYS30762 Programming in C++
// Author: 10899510
// Date: April 5th 2024
// Nucleus class implementation
// Defines the behaviour for radioactive and stable nuclei, including decay logic,
// Rule of Five semantics, and tracking of photon emission during decay processes.

#include "Nucleus.h"
#include <iostream>

#define RESET       "\033[0m"
#define CYAN        "\033[36m"
#define SOFTPINK    "\033[38;5;217m"
#define SOFTPURPLE  "\033[38;5;104m"

// --- Base class: Nucleus ---

// Constructor
Nucleus::Nucleus(std::string t, int am, int an)
  : type(t), atomic_mass(am), atomic_number(an), decayed(false), emitted_photon(nullptr)
{
}

// Virtual destructor
Nucleus::~Nucleus() = default;

// Copy constructor
Nucleus::Nucleus(const Nucleus& other)
  : type(other.type),
    atomic_mass(other.atomic_mass),
    atomic_number(other.atomic_number),
    decayed(other.decayed),
    emitted_photon(other.emitted_photon)
{
}

// Copy assignment operator
Nucleus& Nucleus::operator=(const Nucleus& other)
{
  if(this != &other)
  {
    type = other.type;
    atomic_mass = other.atomic_mass;
    atomic_number = other.atomic_number;
    decayed = other.decayed;
    emitted_photon = other.emitted_photon;
  }
  return *this;
}

// Move constructor
Nucleus::Nucleus(Nucleus&& other) noexcept
  : type(std::move(other.type)),
    atomic_mass(other.atomic_mass),
    atomic_number(other.atomic_number),
    decayed(other.decayed),
    emitted_photon(std::move(other.emitted_photon))
{
}

// Move assignment operator
Nucleus& Nucleus::operator=(Nucleus&& other) noexcept
{
  if(this != &other)
  {
    type = std::move(other.type);
    atomic_mass = other.atomic_mass;
    atomic_number = other.atomic_number;
    decayed = other.decayed;
    emitted_photon = std::move(other.emitted_photon);
  }
  return *this;
}

// Prints nucleus data
void Nucleus::print_data() const
{
  std::cout << "Nucleus (" << type << ") | A: " << atomic_mass << ", Z: " << atomic_number;
  if(decayed)
  {
    std::cout << " | Status: Decayed\n";
  }
  else
  {
    std::cout << " | Status: Stable\n";
  }
}

// --- Derived class: StableNucleus ---

// Constructor
StableNucleus::StableNucleus(std::string t, int am, int an)
  : Nucleus(t, am, an)
{
}

// Override decay
void StableNucleus::decay(std::vector<std::shared_ptr<Photon>>& photon_log, int& annihilation_photon_count)
{
  (void)photon_log;
  (void)annihilation_photon_count;
  std::cout << CYAN << "Stable nucleus (" << type << ") cannot decay.\n" << RESET;
}

// --- Derived class: RadioactiveNucleus ---

// Constructor
RadioactiveNucleus::RadioactiveNucleus(std::string t, int am, int an, double hl, std::vector<double> de)
  : Nucleus(t, am, an), half_life(hl), decay_energies(std::move(de))
{
}

// Override decay
void RadioactiveNucleus::decay(std::vector<std::shared_ptr<Photon>>& photon_log, int& annihilation_photon_count)
{
  if(decayed)
  {
    std::cout << CYAN << "Nucleus (" << type << ") has already decayed.\n" << RESET;
    return;
  }

  std::cout << CYAN << "Decay of " << type << ":\n" << SOFTPURPLE;

  for(double e : decay_energies)
  {
    emitted_photon = std::make_shared<Photon>(e);
    std::cout << "  ";
    emitted_photon->print_data();
    photon_log.push_back(emitted_photon);
  }

  if(type == "Na")
  {
    auto positron = std::make_shared<Positron>(511.0);
    std::cout << SOFTPINK << "  Positron emission from Na detected.\n";
    std::cout << "  ";
    positron->print_data();

    auto annihilation_photon1 = std::make_shared<Photon>(511.0);
    auto annihilation_photon2 = std::make_shared<Photon>(511.0);
    std::cout << "  Positron annihilated with electron:\n" << SOFTPURPLE;
    std::cout << "    ";
    annihilation_photon1->print_data();
    std::cout << "    ";
    annihilation_photon2->print_data();
    std::cout << RESET;

    photon_log.push_back(annihilation_photon1);
    photon_log.push_back(annihilation_photon2);
    annihilation_photon_count += 2;
  }

  decayed = true;
}
