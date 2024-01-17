#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include "circuit.hpp"

using namespace std;

void network(int const iterations, int const lines, double const timeSteps, double const voltage);
void deallocate(vector<Component*> &n);

int main(int argc, char *argv[])
{
    int iterations{0};
    int lines{0};
    double timeSteps{0.0};
    double voltage{0.0};

    if (argc < 5 || argc > 5)
        {  
            cerr << "Error: Incorrect Number of Argument(s) Supplied. Program exiting." <<"\n"
                 << "Please Supply 5 Arguments." << endl;
            return 1;
        }
    else 
        {
            try
            {

                iterations = stoi(argv[1]);
            }
            catch(std::invalid_argument& e) 
            { 
                cerr << "Exception in Iteration: Invalid argument. Expected: Interger. Program exiting." << endl;
                return 2;
            }
            catch(std::out_of_range& e)
            {
                cerr << "Exception in Iteration: Argument out of range. Expected: Interger Within 8 Digits. Program exiting." << endl;
                return 3;
            }

            try
            {

                lines = stoi(argv[2]);
            }
            catch(std::invalid_argument& e) 
            { 
                cerr << "Exception in Number of Lines: Invalid argument. Expected: Interger. Program exiting." << endl; 
                return 2;
            }
            catch(std::out_of_range& e)
            {
                cerr << "Exception in Number of Lines: Argument out of range. Expected: Interger Within 8 Digits. Program exiting." << endl; 
                return 3;
            }

            try
            {

                timeSteps = stod(argv[3]);
            }
            catch(std::invalid_argument& e) 
            { 
                cerr << "Exception in TimeSteps: Invalid argument. Expected: Real Number. Program exiting." << endl; 
                return 2;
            }
            catch(std::out_of_range& e)
            {
                cerr << "Exception in TimeSteps: Argument out of range. Expected: Real Number. Program exiting." << endl; 
                return 3;
            }
            try
            {

                voltage = stod(argv[4]);
            }
            catch(std::invalid_argument& e) 
            { 
                cerr << "Exception in Voltage Input: Invalid argument. Expected: Real Number. Program exiting." << endl; 
                return 2;
            }
            catch(std::out_of_range& e)
            {
                cerr << "Exception in Voltage Input: Argument out of range. Expected: Real Number. Program exiting." << endl; 
                return 3;
            }
            
            
            if (iterations < 0 || lines < 0 || timeSteps < 0 || voltage < 0)
            {
                cerr << "Program Accepts Only Postive Number(s)" << endl;
                cerr << "Usage: ./a.out 200000 10 0.01 24" << endl;
            }
            else
            {
                network(iterations, lines, timeSteps, voltage);
            }
        }     
    return 0;
}

void network(int const iterations, int const lines, double const timeSteps, double const voltage)
{
    Circuit circuit;
    Connection p1{}, n1{}, r124{}, r23{};      
    vector<Component*> circuit1;    

    circuit1.push_back(new Battery("Bat", voltage, p1, n1));
    circuit1.push_back(new Resistor("R1", 6.0, p1, r124));
    circuit1.push_back(new Resistor("R2", 4.0, r124, r23));
    circuit1.push_back(new Resistor("R3", 8.0, r23, n1));
    circuit1.push_back(new Resistor("R4", 12.0, r124, n1));
    circuit.simulation(circuit1, iterations, lines, timeSteps);
    deallocate(circuit1);
    
    
    vector<Component*> circuit2;
    Connection p2{}, n2{}, r1{}, r2{};
    circuit2.push_back(new Battery("Bat", voltage, p2, n2));
    circuit2.push_back(new Resistor("R1", 150.0, p2, r1));
    circuit2.push_back(new Resistor("R2", 50.0, p2, r2));
    circuit2.push_back(new Resistor("R3", 100.0, r1, r2));
    circuit2.push_back(new Resistor("R4", 300.0, r1, n2));
    circuit2.push_back(new Resistor("R5", 250.0, r2, n2));
    circuit.simulation(circuit2, iterations, lines, timeSteps);
    deallocate(circuit2);
   
    vector<Component*> circuit3;
    Connection p3{}, n3{}, conn31{}, conn32{};
    circuit3.push_back(new Battery("Bat", voltage, p3, n3));
    circuit3.push_back(new Resistor("R1", 150.0, p3, conn31));
    circuit3.push_back(new Resistor("R2", 50.0, p3, conn32));
    circuit3.push_back(new Capacitor("C3", 1.0, conn31, conn32));
    circuit3.push_back(new Resistor("R4", 300.0, conn31, n3));
    circuit3.push_back(new Capacitor("C5", 0.75, conn32, n3));
    circuit.simulation(circuit3, iterations, lines, timeSteps);
    deallocate(circuit3);
    
}

void deallocate(vector<Component*> &n)
{   
    for(auto const &i : n) 
        {
            delete i;
            n.clear();
        }
}
