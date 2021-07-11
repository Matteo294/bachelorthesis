#include "IsingCanonical.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(){

    srand(time(NULL));

    ofstream initfile, endfile;
    initfile.open("dataInitCanonical.csv");
    endfile.open("dataFinalCanonical.csv");
    
    const double T = -0.01; // Temperature of the system
    const int N = 200; // Number of sites per each dimension
    const double J =  1.0; // Coupling
    const double B = 0.0; // Magnetic field
    const int nsteps = 1e6; // MonteCarlo steps

    IsingCanonical S(T, N, J, B);

    // Print to file initial configuration
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            initfile << S.states[i][j];
            if (j!=N-1) initfile << ",";
        }
        initfile << endl;
    }

    cout << "Initial energy: " << S.Hamiltonian() << "\t n up: " << S.nplus << endl; 

    // Run MC steps
    S.thermalize(nsteps);

    // Print to file final configuration
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            endfile << S.states[i][j];
            if (j!=N-1) endfile << ",";
        }
        endfile << endl;
    }

    cout << "Final energy: " << S.Hamiltonian() << "\t n up: " << S.nplus << endl; 

    initfile.close();
    endfile.close();
    
    return 0;
}