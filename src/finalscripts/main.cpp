#include "IsingCanonical.h"
#include "IsingMicrocanonical.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int main(){



    srand(time(NULL));



    /************************************************************/
    /********************** Output files ************************/
    /************************************************************/
    ofstream outfile, initconffile, endconffile;
    outfile.open("data.csv");
    outfile << "n,T1,T2,S1,S2,S,E1,E2" << endl;
    initconffile.open("initconf.csv");
    endconffile.open("endconf.csv");
    /************************************************************/



    /************************************************************/
    /*********************** Constants **************************/
    /************************************************************/
    const int nspins = 200;
    const int ncycles = 1e7;
    const double B = 1.0;
    const double J = 0.0;
    const double T1 = 1e-10;
    const double T2 = 1000;
    /************************************************************/



    /************************************************************/
    /************ Useful quantities for the MC cycles ***********/
    /************************************************************/
    int idx1, idx2;
    double new_energy, old_energy;
    double deltaE;
    double temp1, temp2;
    /************************************************************/



    /************************************************************/
    /*********************** Set up systems *********************/
    /************************************************************/
    // Create the two canonical systems to put into contact
    IsingCanonical S1(T1, nspins, J, B);
    IsingCanonical S2(T2, nspins, J, B);
    
    // Thermalization --> bring system to equilibrium
    S1.thermalize(1e6);
    S2.thermalize(1e6);


    // Store energy and entropy of the initial configuration
    double E1 = S1.Hamiltonian();
    double E2 = S2.Hamiltonian();


    // Create microcanonical systems S1+S2 (two body into contact)
    IsingMicrocanonical S(E1+E2, S1.N+S2.N, S1.N, J, B);
    // Copy the states of S1 and S2 into the states of S
    for(int i=0; i<S1.N; i++){
        for(int j=0; j<S1.N; j++){
            S.states[i][j] = S1.states[i][j];
        }
    }
    for(int i=0; i<S2.N; i++){
        for(int j=0; j<S2.N; j++){
            S.states[i+S1.N][j] = S2.states[i][j];
        }
    }
    
    S.countUp();
    // Store S energy of the initial configuration
    old_energy = S.Hamiltonian();
    S.demon_energy = 0.0;
    cout << "After thermalization" << endl;
    cout << "Energies: " << S1.Hamiltonian() << " " << S2.Hamiltonian() << endl;
    cout << "Spin up S1: " << S1.nplus << "\t\t Spin up S2: " << S2.nplus << " " << endl;
    cout << "Spin up total: " << S.nplus << endl;
    /************************************************************/



    /************************************************************/
    /*********** Print initial configuration to file ************/
    /************************************************************/    
    for(int i=0; i<S.Nrows; i++){
        for(int j=0; j<S.Ncols; j++){
            initconffile << S.states[i][j];
            if (j!=S.Ncols-1) initconffile << ",";
        }
        initconffile << endl;
    }
    /************************************************************/
    


    cout << "Starting MC cycles" << endl;
    deltaE = 0.0;
    int n1, n2;
    
    for(int i=0; i<ncycles; i++){


        idx1 = rand()%(S.Nrows); // index of the spin to flip
        idx2 = rand()%(S.Ncols); // index of the spin to flip
        deltaE = S.flip(idx1, idx2);
        if (deltaE < 0){
            S.demon_energy += abs(deltaE);
        } else {
            if (S.demon_energy < deltaE) {
                S.flip(idx1, idx2); 
            } else {
                S.demon_energy -= deltaE;
            }
        } 

    }

    

    /************************************************************/
    /*********** Print initial configuration to file ************/
    /************************************************************/ 
    cout << "Finished MC cycles" << endl;
    for(int i=0; i<S.Nrows; i++){
        for(int j=0; j<S.Ncols; j++){
            endconffile << S.states[i][j];
            if (j!=S.Ncols-1) endconffile << ",";
        }
        endconffile << endl;
    }
    /************************************************************/ 



    /************************************************************/
    /******************** Close output files ********************/
    /************************************************************/ 
    outfile.close();
    initconffile.close();
    endconffile.close();
    /************************************************************/ 



    /************************************************************/
    /************* Copy the states of S into S1 and S2 **********/
    /************************************************************/ 
    for(int i=0; i<S1.N; i++){
        for(int j=0; j<S1.N; j++){
            S1.states[i][j] = S.states[i][j];
        }
    }
    for(int i=0; i<S2.N; i++){
        for(int j=0; j<S2.N; j++){
            //cout << i << " " << j << " " << S.Nrows << " " << S.Ncols << endl;
            S2.states[i][j] = S.states[i+S1.N][j];
        }
    }
    S1.countUp();
    S2.countUp();
    /************************************************************/ 

    cout << "Spin up S1: " << S1.nplus << "\t\t Spin up S2: " << S2.nplus << " " << endl;

    return 0;
}