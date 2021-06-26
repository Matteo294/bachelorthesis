#include "IsingCanonical.h"
#include "IsingMicrocanonical.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int main(){

    ofstream outfile, conffile;
    outfile.open("data.csv");
    outfile << "n,S1,S2,S,E1,E2" << endl;
    conffile.open("conf.csv");
    conffile << "spin" << endl;
    

    // Constants
    const int nspins = 500;
    const int ncycles = 1e6;
    const double B = 1.0;
    const double J = 0;
    const double T1 = -100;
    const double T2 = 0.001;

    // Create systems S1, S2
    IsingCanonical S1(T1, nspins, J, B);
    IsingCanonical S2(T2, nspins, J, B);
    S1.thermalize(100000);
    S2.thermalize(100000);
    S1.countUp();
    S2.countUp();
    // Create system S = S1 + S2
    double E1 = S1.Hamiltonian();
    double E2 = S2.Hamiltonian();
    IsingMicrocanonical S(E1 + E2, S1.N + S2.N, J, B);
    double old_energy = S.Hamiltonian();
    cout << E1 << " " << E2 << " " << old_energy << endl;
    // Useful quantities for the MC cycles
    int idx;
    double new_energy = old_energy;
    double deltaE;
    double E1_old, E1_new, S1_old, S1_new;
    double E2_old, E2_new, S2_old, S2_new;

    S1_new = S1.Entropy();
    S2_new = S2.Entropy();

    for(int i=0; i<S.N; i++){
            conffile << S.states[i] << endl;
    }

    E1_new = E1;
    E2_new = E2;
    deltaE = 0.0;
    for(int i=0; i<ncycles; i++){

        S1_old = S1_new;
        S2_old = S2_new;
        E1_old = E1_new;
        E2_old = E2_new;

        idx = rand()%(2*nspins); // index of the spin to flip
        S.flip(idx);
        new_energy = S.Hamiltonian();
        deltaE = new_energy - old_energy;
        if (deltaE < 0) S.demon_energy += abs(deltaE);
        else {
            if (S.demon_energy < deltaE) {S.flip(idx);}
            else {
                S.demon_energy -= deltaE;
            }
        } 
        for(int i=0; i<S1.N; i++) S1.states[i] = S.states[i];
        for(int i=0; i<S2.N; i++) S2.states[i] = S.states[S1.N+i];
        S1.countUp();
        S2.countUp();

        E1_new = S1.Hamiltonian();
        E2_new = S2.Hamiltonian();
        S1_new = S1.Entropy();
        S2_new = S2.Entropy();

        if (i>=10000){
            outfile << i << "," << S1.Entropy() << "," << S2.Entropy() << "," << S.Entropy() << "," << S1.Hamiltonian() << "," << S2.Hamiltonian() << endl; 
        }
    }

    outfile.close();
    conffile.close();
    
    for(int i=0; i<S1.N; i++) S1.states[i] = S.states[i];
    for(int i=0; i<S2.N; i++) S2.states[i] = S.states[S1.N+i];
    S1.countUp();
    S2.countUp();

    cout << "End" << endl << S1.nplus << " " << S2.nplus << endl;
    
    return 0;
}