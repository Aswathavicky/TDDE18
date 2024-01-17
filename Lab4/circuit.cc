#include "circuit.hpp"
#include <iostream>
#include <iomanip>


Component::Component(std::string name, Connection &p, Connection &n):
    name{name}, terminal1{p}, terminal2{n} {}

double Component::voltageDiff() const
{   
    double max = std::max(terminal1.voltage, terminal2.voltage);
    double min = std::min(terminal1.voltage, terminal2.voltage);
    return (max - min);
}

void Component::updateTerminals(double change) const
{
    if (terminal1.voltage > terminal2.voltage)
    {
        terminal1.voltage -= change;
        terminal2.voltage += change;
    }
    else
    {
        terminal1.voltage += change;
        terminal2.voltage -= change;
    }
}

std::string Component::getName() const
{ 
    return name; 
}

double Component::getCurrent() const
{ 
    return current; 
}


Battery::Battery(std::string name, double volts, Connection &p, Connection &n):
    Component(name, p, n), voltage(volts) 
    {
        p.voltage = voltage;
        n.voltage = 0;

    }

double Battery::simulate(double /*timeSteps*/)
{   
    terminal1.voltage = voltage;
    terminal2.voltage = 0.0;
    return voltage;
}

double Battery::getCurrent() const
{  
    return current;
}


Capacitor::Capacitor(std::string name, double farads, Connection &p, Connection &n):
    Component(name, p, n), capacitance{farads}, charge{0} {}

double Capacitor::simulate(double timeSteps)
{
    double chargeMoved{0.0};
    double voltageDifference{0.0};
    voltageDifference = voltageDiff();
    chargeMoved = capacitance * (voltageDifference - charge) * timeSteps; 
    charge = charge + chargeMoved;                          
    updateTerminals(chargeMoved);                          
    return voltageDiff();
}

double Capacitor::getCurrent() const
{
    double curr{0.0};
    double voltageDifference{0.0};
    voltageDifference = voltageDiff();
    curr = capacitance * (voltageDifference - charge);
    return curr;
}


Resistor::Resistor(std::string name, double ohms, Connection &p, Connection &n):
    Component(name, p, n), resistance(ohms) {}

double Resistor::simulate(double timeSteps)
{    
    double voltageDifference{0.0};
    voltageDifference = voltageDiff();
    double charge = (voltageDifference / resistance * timeSteps);
    updateTerminals(charge);
    return voltageDiff(); // return updated feed(diff.)
}

double Resistor::getCurrent() const
{
    double curr{0.0};
    double voltageDifference{0.0};
    voltageDifference = voltageDiff();
    curr = voltageDifference / resistance;
    return curr;
}


void Circuit::simulation(std::vector<Component*> const& net, int const iterations, int const lines, double const timeSteps) const
{
    int size{0};
    for (auto const &comp : net)
    {
        std::cout << std::setw(12) << comp->getName();
    }
    std::cout << std::endl;

    size = net.size();

    for (int i{0}; i < size; ++i)
    {
        std::cout << std::setw(6) << "volt";
        std::cout << std::setw(6) << "curr";  
    }      
    std::cout << std::endl;

    int interval = iterations / lines;
    //double volt{0.0};
    //double curr{0.0};

    for (int i{1}; i <= iterations; i++)
    {
            double volt{0.0};
            double curr{0.0};
        for (auto const &comp: net)
        {
            volt = comp->simulate(timeSteps);
            curr = comp->getCurrent();

            if (i % interval == 0)
            {
                std::cout << std::setw(6) << std::fixed << std::setprecision(2) << volt; 
                std::cout << std::setw(6) << std::fixed << std::setprecision(2) << curr;
            }
        }  
        if (i % interval == 0)
        {
            std::cout << std::endl;
        }
    }
}
