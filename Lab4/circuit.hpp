#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP

#include <string>
#include <vector>

struct Connection
 {
    double voltage{0.0}; 
  
 };  



class Component
{
public:
    std::string getName() const;
    virtual double getCurrent() const;
    virtual double simulate(double timeSteps) = 0;
    virtual ~Component() = default;

protected:
    Component(std::string name, Connection &p, Connection &n);
    double voltageDiff() const;
    void updateTerminals(double change) const;

    std::string name;
    double current{};
    Connection &terminal1;
    Connection &terminal2;   
};

class Battery: public Component
{
public:
    Battery(std::string name, double volts, Connection &p, Connection &n);
    double getCurrent() const override;
    double simulate(double timeSteps) override;

private:
    double voltage{};
};

class Capacitor: public Component
{
public:
    Capacitor(std::string name, double farads, Connection &p, Connection &n);
    double getCurrent() const override;
    double simulate(double timeSteps) override;

private:
    double capacitance{};
    double charge{};  //in store
};

class Resistor: public Component
{
public:
    Resistor(std::string name, double ohms, Connection &p, Connection &n);
    double getCurrent() const override;
    double simulate(double timeSteps) override;

private:
    double resistance{};
};

class Circuit
{
public:
    void simulation(std::vector<Component*> const& net, int const iterations, int const lines, double const timeSteps) const;

private:
    std::vector<Component*> components;
};


#endif
