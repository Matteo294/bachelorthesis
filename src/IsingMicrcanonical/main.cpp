#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include "IsingMicrocanonical.h"
#include <string>

using namespace std;

int main(){

    const int nspins = 1000;
    const int ncycles = 1e6;
    const double B = 1.0;
    const double J = 0;
    vector<double> energies {-50, -20, -5, 0, 5, 20, 50};
    const int nenergies = energies.size();

    int idx;
    double deltaE;
    double old_energy, new_energy;
    double Esum;
    string filename;

    ofstream myfile;

    for(int n=0; n<nenergies; n++){
        myfile.open("data" + to_string(n) + ".csv");
        myfile << "n,Energies" << endl;  
        IsingMicrocanonical S(energies[n], nspins, J, B);
        cout << "Spins up: " << S.nplus << "\t" << "Energy: " << S.Hamiltonian() << "\t" << "Expected: " << energies[n] << endl; 
        old_energy = S.Hamiltonian();
        new_energy = old_energy;
        deltaE = 0.0;
        Esum = 0.0;
        for(int i=0; i<ncycles; i++){
            idx = rand()%nspins; // index of the spin to flip
            S.flip(idx);
            new_energy = S.Hamiltonian();
            deltaE = new_energy - old_energy;
            if (deltaE < 0) S.demon_energy += abs(deltaE);
            else {
                if (S.demon_energy < deltaE) {S.flip(idx);}
                else {
                    S.demon_energy -= deltaE;
                    //cout << "Ehsi: " << S.demon_energy << endl;
                }
            }   
            //cout << deltaE << " " << S.demon_energy << endl;   
            Esum += S.Hamiltonian();
            myfile << i << "," << Esum/(i+1) << endl;
            //energies[i] = (double) Esum/(i+1);   
        }
        cout << "Demon energy: " << S.demon_energy << "\t";
        cout << "N up:\t" << S.nplus  << "\t Energy: " << S.Hamiltonian() << endl << endl;
        myfile.close();
    }
    return 0;
}