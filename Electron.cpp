#include "Electron.h"
#include "Photon.h"
#include <iostream>

#define PINKRED "\033[38;5;198m"
#define RESET   "\033[0m"

Electron::Electron(double e) : Particle(0.511, e) {}

void Electron::addPhoton(std::shared_ptr<Photon> p) {
    photons.push_back(p);
}

std::shared_ptr<Photon> Electron::radiate() {
    if (photons.empty()) {
        std::cout << PINKRED << "Electron has no photons to radiate.\n" << RESET;
        return nullptr;
    }

    auto p = photons.back();
    photons.pop_back();
    return p;
}


void Electron::printData() const {
    std::cout << "Electron | Energy: " << energy << " keV"
              << ", Photons: " << photons.size() << "\n";
}
