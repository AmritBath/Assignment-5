// PHYS 30762 Programming in C++
// Assignment 5 - Extended with positron emission, Bremsstrahlung, and UX formatting

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib> // for rand()

// Local headers
#include "Nucleus.h"
#include "Photon.h"
#include "Electron.h"
#include "Interactions.h"
#include "Positron.h"

using std::string;
using std::vector;
using std::make_shared;
using std::shared_ptr;
using std::cout;
using std::endl;

// --- Colour macros ---
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define TEAL    "\033[38;5;30m"
#define BOLD    "\033[1m"

int main() {
    vector<shared_ptr<Nucleus>> nuclei;
    vector<shared_ptr<Photon>> emitted_photons;

    nuclei.push_back(make_shared<RadioactiveNucleus>("Na", 23, 11, 15.0, vector<double>{1274.5}));
    nuclei.push_back(make_shared<RadioactiveNucleus>("Cs", 137, 55, 30.0, vector<double>{611.0}));
    nuclei.push_back(make_shared<RadioactiveNucleus>("Co", 60, 27, 5.27, vector<double>{1173.0, 1333.0}));
    nuclei.push_back(make_shared<StableNucleus>("Fe", 56, 26));

    // --- NUCLEI DATA SUMMARY ---
    cout << TEAL << BOLD << "--- Nuclei Data ---\n" << RESET;
    for (const auto& nucleus : nuclei) {
        nucleus->printData();
        cout << RESET;
        if (auto r = std::dynamic_pointer_cast<RadioactiveNucleus>(nucleus)) {
            cout << "  Half-life: " << r->getHalfLife() << " years\n";
            const auto& energies = r->getDecayEnergies();
            for (const auto& e : energies) {
                cout << "  Decay photon: " << e << " keV\n";
            }
        }
        cout << "\n";
    }

    // --- NUCLEUS DECAY ---
    cout << TEAL << BOLD << "\n--- Nucleus Decay ---\n" << RESET;

    for (const auto& nucleus : nuclei) {
        nucleus->decay(emitted_photons);
        cout << RESET;
    }

    // --- PHOTON INTERACTIONS ---
    cout << TEAL << BOLD << "\n--- Photon Interactions ---\n" << RESET;

    std::vector<std::shared_ptr<Electron>> all_electrons;

    for (size_t i = 0; i < emitted_photons.size(); ++i) {
        auto& photon = emitted_photons[i];
        cout << YELLOW << "Photon from decay:\n  ";
        photon->printData();
        cout << RESET;

        int interaction_type = i % 3;

        if (interaction_type == 0) {
            double energy = photoelectricEffect(*photon);
            cout << GREEN << "[Photoelectric] Photon energy: " << energy << " keV\n" << RESET;
        } else if (interaction_type == 1) {
            comptonScattering(*photon, 60.0);
        } else {
            auto electrons = pairProduction(*photon);
            if (!electrons.empty()) {
                cout << GREEN << "[Pair Production] Photon energy = " << photon->getEnergy()
                     << " keV\nProduced 2 electrons\n" << RESET;
                all_electrons.insert(all_electrons.end(), electrons.begin(), electrons.end());
            }
        }
    }

    // --- ELECTRON RADIATION ---
    cout << TEAL << BOLD << "\n--- Electron Radiation ---\n" << RESET;

    int radiated_photon_count = 0;

    for (auto& electron : all_electrons) {
        int max_photons = 1 + rand() % 3;
        double total_energy = electron->getEnergy();

        for (int i = 0; i < max_photons; ++i) {
            double remaining = total_energy / (max_photons - i);
            double energy = 10 + (rand() % static_cast<int>(remaining));
            auto p = std::make_shared<Photon>(energy);
            electron->addPhoton(p);
            total_energy -= energy;
        }

        cout << BLUE << "Electron before radiation:\n";
        electron->printData();
        cout << RESET;

        while (auto emitted = electron->radiate()) {
            cout << YELLOW << "Radiated photon:\n  ";
            emitted->printData();
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
    cout << "Positrons emitted: 1 (from Na)\n" << RESET;

    return 0;
}
