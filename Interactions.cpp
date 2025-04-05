#include "Interactions.h"
#include <iostream>
#include <cmath>

#define PINKRED "\033[38;5;198m"
#define RESET   "\033[0m"

double photoelectricEffect(const Photon& p) {
    return p.energy;
}

void comptonScattering(Photon& p, double angle_deg) {
    double theta = angle_deg * M_PI / 180.0;
    double E = p.energy;
    double me = 511; // keV
    p.energy = E / (1 + (E / me) * (1 - std::cos(theta)));
    std::cout << "After Compton scattering, new photon energy: " << p.energy << " keV\n";
}

std::vector<std::shared_ptr<Electron>> pairProduction(const Photon& p) {
    double me = 511; // keV
    if (p.energy > 2 * me) {
        double e = p.energy / 2;
        auto e1 = std::make_shared<Electron>(e);
        auto e2 = std::make_shared<Electron>(e);
        
        // Add electrons to the photon that created them
        const_cast<Photon&>(p).addElectron(e1);
        const_cast<Photon&>(p).addElectron(e2);

        return { e1, e2 };
    } else {
        std::cout << PINKRED << "ERROR: Insufficient energy for pair production.\n" << RESET;
        return {};
    }
}

