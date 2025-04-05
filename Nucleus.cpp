#include "Nucleus.h"
#include <iostream>
// --- Colour macros ---
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define TEAL    "\033[30m"
#define SOFTPINK "\033[38;5;217m" 
#define SOFTPURPLE "\033[38;5;104m"

Nucleus::Nucleus(std::string t, int am, int an)
    : type(t), atomic_mass(am), atomic_number(an), decayed(false), emitted_photon(nullptr) {}

// Rule of Five implementations
Nucleus::~Nucleus() = default;

Nucleus::Nucleus(const Nucleus& other)
    : type(other.type), atomic_mass(other.atomic_mass), atomic_number(other.atomic_number),
      decayed(other.decayed), emitted_photon(other.emitted_photon) {}

Nucleus& Nucleus::operator=(const Nucleus& other) {
    if (this != &other) {
        type = other.type;
        atomic_mass = other.atomic_mass;
        atomic_number = other.atomic_number;
        decayed = other.decayed;
        emitted_photon = other.emitted_photon;
    }
    return *this;
}

Nucleus::Nucleus(Nucleus&& other) noexcept
    : type(std::move(other.type)), atomic_mass(other.atomic_mass), atomic_number(other.atomic_number),
      decayed(other.decayed), emitted_photon(std::move(other.emitted_photon)) {}

Nucleus& Nucleus::operator=(Nucleus&& other) noexcept {
    if (this != &other) {
        type = std::move(other.type);
        atomic_mass = other.atomic_mass;
        atomic_number = other.atomic_number;
        decayed = other.decayed;
        emitted_photon = std::move(other.emitted_photon);
    }
    return *this;
}

void Nucleus::printData() const {
    std::cout << "Nucleus (" << type << ") | A: " << atomic_mass << ", Z: " << atomic_number;
    if (decayed) std::cout << " | Status: Decayed\n";
    else std::cout << " | Status: Stable\n";
}

StableNucleus::StableNucleus(std::string t, int am, int an)
    : Nucleus(t, am, an) {}
void StableNucleus::decay(std::vector<std::shared_ptr<Photon>>& photon_log) {
    std::cout << CYAN << "Stable nucleus (" << type << ") cannot decay.\n";
}

RadioactiveNucleus::RadioactiveNucleus(std::string t, int am, int an, double hl, std::vector<double> de)
    : Nucleus(t, am, an), half_life(hl), decay_energies(std::move(de)) {}

    void RadioactiveNucleus::decay(std::vector<std::shared_ptr<Photon>>& photon_log) {
        if (decayed) {
            std::cout << CYAN << "Nucleus (" << type << ") has already decayed.\n" << RESET;
            return;
        }
    
        std::cout << CYAN << "Decay of " << type << ":\n" << SOFTPURPLE;
    
        for (double e : decay_energies) {
            emitted_photon = std::make_shared<Photon>(e);
            std::cout << "  ";
            emitted_photon->printData();
            photon_log.push_back(emitted_photon);
        }
    
        if (type == "Na") {
            auto positron = std::make_shared<Positron>(511.0);
            std::cout << SOFTPINK << "  Positron emission from Na detected.\n";
            std::cout << "  ";
            positron->printData();
    
            auto annihilation_photon1 = std::make_shared<Photon>(511.0);
            auto annihilation_photon2 = std::make_shared<Photon>(511.0);
            std::cout << "  Positron annihilated with electron:\n" << SOFTPURPLE;
            std::cout << "    ";
            annihilation_photon1->printData();
            std::cout << "    ";
            annihilation_photon2->printData();
            std::cout << RESET;
    
            photon_log.push_back(annihilation_photon1);
            photon_log.push_back(annihilation_photon2);
        }
    
        decayed = true;
    }
    