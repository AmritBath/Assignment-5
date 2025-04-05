// PHYS 30762 Programming in C++
// Author: 10899510 - Amrit Bath
// Date: April 5th 2024
// Assignment 5
// Aim: To simulate the decay of radioactive nuclei and their interactions with photons and electrons.
// Extensions: Positron emission, Bremsstrahlung, and intuitive UX design

// --- Standard libraries ---
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>

// --- Local headers ---
#include "Nucleus.h"
#include "Photon.h"
#include "Electron.h"
#include "Interactions.h"
#include "Positron.h"

// --- Namespace usage ---
using std::string;
using std::vector;
using std::make_shared;
using std::shared_ptr;
using std::cout;
using std::endl;

// --- Colour macros for terminal output ---
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define TEAL    "\033[38;5;30m"
#define BOLD    "\033[1m"

int main()
{
  // --- Initialise simulation variables ---
  vector<shared_ptr<Nucleus>> nuclei;
  vector<shared_ptr<Photon>> emitted_photons;
  int annihilation_photon_count = 0;

  // --- NUCLEI INITIALISATION ---
  nuclei.push_back(make_shared<RadioactiveNucleus>("Na", 23, 11, 15.0, vector<double>{1274.5}));
  nuclei.push_back(make_shared<RadioactiveNucleus>("Cs", 137, 55, 30.0, vector<double>{611.0}));
  nuclei.push_back(make_shared<RadioactiveNucleus>("Co", 60, 27, 5.27, vector<double>{1173.0, 1333.0}));
  nuclei.push_back(make_shared<StableNucleus>("Fe", 56, 26));

  // --- NUCLEI DATA SUMMARY ---
  cout << TEAL << BOLD << "--- Nuclei Data ---\n" << RESET;
  for(const auto& nucleus : nuclei)
  {
    nucleus->print_data();
    cout << RESET;

    if(auto r = std::dynamic_pointer_cast<RadioactiveNucleus>(nucleus))
    {
      cout << "  Half-life: " << r->get_half_life() << " years\n";
      const auto& energies = r->get_decay_energies();
      for(const auto& e : energies)
      {
        cout << "  Decay photon: " << e << " keV\n";
      }
    }
    cout << "\n";
  }

  // --- NUCLEUS DECAY ---
  cout << TEAL << BOLD << "--- Nucleus Decay ---\n" << RESET;
  for(const auto& nucleus : nuclei)
  {
    nucleus->decay(emitted_photons, annihilation_photon_count);
    cout << RESET;
  }

  // --- PHOTON INTERACTIONS ---
  cout << TEAL << BOLD << "\n--- Photon Interactions ---\n" << RESET;
  vector<shared_ptr<Electron>> all_electrons;

  for(size_t i = 0; i < emitted_photons.size(); ++i)
  {
    auto& photon = emitted_photons[i];
    cout << YELLOW << "Photon from decay:\n  ";
    photon->print_data();
    cout << RESET;

    int interaction_type = i % 3;

    if(interaction_type == 0)
    {
      double energy = photoelectric_effect(*photon);
      cout << GREEN << "[Photoelectric] Photon energy: " << energy << " keV\n" << RESET;
    }
    else if(interaction_type == 1)
    {
      compton_scattering(*photon, 60.0);
    }
    else
    {
      auto electrons = pair_production(*photon);
      if(!electrons.empty())
      {
        cout << GREEN << "[Pair Production] Photon energy = " << photon->get_energy()
             << " keV\nProduced 2 electrons\n" << RESET;
        all_electrons.insert(all_electrons.end(), electrons.begin(), electrons.end());
      }
    }
  }

  // --- ELECTRON RADIATION ---
  cout << TEAL << BOLD << "\n--- Electron Radiation ---\n" << RESET;
  int radiated_photon_count = 0;

  for(auto& electron : all_electrons)
  {
    int max_photons = 1 + rand() % 3;
    double total_energy = electron->get_energy();

    for(int i = 0; i < max_photons; ++i)
    {
      double remaining = total_energy / (max_photons - i);
      double energy = 10 + (rand() % static_cast<int>(remaining));
      auto p = std::make_shared<Photon>(energy);
      electron->add_photon(p);
      total_energy -= energy;
    }

    cout << BLUE << "Electron before radiation:\n";
    electron->print_data();
    cout << RESET;

    while(auto emitted = electron->radiate())
    {
      cout << YELLOW << "Radiated photon:\n  ";
      emitted->print_data();
      cout << RESET;
      ++radiated_photon_count;
    }
  }

  // --- SIMULATION SUMMARY ---
  cout << TEAL << BOLD << "\n--- Simulation Summary ---\n" << RESET;
  cout << "Nuclei simulated: 4 (3 decayed + 1 stable)\n";
  cout << "Photons emitted: " << emitted_photons.size() << "\n";
  cout << "Electrons created: " << all_electrons.size() << "\n";
  cout << "Photons radiated by electrons: " << radiated_photon_count << "\n";
  cout << "Photons from annihilation: " << annihilation_photon_count << "\n";
  cout << "Positrons emitted: 1 (from Na)\n" << RESET;

  return 0;
}
