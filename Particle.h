#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
protected:
    double rest_mass;
    double energy;
public:
    Particle(double rm, double e);
    virtual ~Particle() = default;

    double getRestMass() const;
    double getEnergy() const;
    void setEnergy(double e);
    virtual void printData() const = 0;
};

#endif
