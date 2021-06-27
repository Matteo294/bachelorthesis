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
    outfile << "n,S1,S2,S,E1,E2" << endl;
    initconffile.open("initconf.csv");
    endconffile.open("endconf.csv");
    /************************************************************/


    /************************************************************/
    /*********************** Constants **************************/
    /************************************************************/
    const int nspins = 20;
    const int ncycles = 1e6;
    const double B = 1.0;
    const double J = 0;
    const double T1 = -1e-8;
    const double T2 = 1e-8;
    /************************************************************/



    /************************************************************/
    /************ Useful quantities for the MC cycles ***********/
    /************************************************************/
    int idx1, idx2;
    double new_energy, old_energy;
    double deltaE;
    double E1_old, E1_new, S1_old, S1_new;
    double E2_old, E2_new, S2_old, S2_new;
    /************************************************************/



    /************************************************************/
    /*********************** Set up systems *********************/
    /************************************************************/
    // Create the two canonical systems to put into contact
    IsingCanonical S1(T1, nspins, J, B);
    IsingCanonical S2(T2, nspins, J, B);
    // Thermalization --> bring system to equilibrium
    S1.thermalize(10000);
    S2.thermalize(10000);
    // Count number of spins up
    S1.countUp();
    S2.countUp();
    // Store energy and entropy of the initial configuration
    double E1 = S1.Hamiltonian();
    double E2 = S2.Hamiltonian();
    S1_new = S1.Entropy();
    S2_new = S2.Entropy();
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
    cout << "Spin up S1: " << S1.nplus << "\t\t Spin up S2: " << S2.nplus << " " << endl;
    cout << "Spin up total: " << S.nplus << endl;
    new_energy = old_energy;
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
    E1_new = E1;
    E2_new = E2;
    deltaE = 0.0;
    int n1, n2;
    for(int i=0; i<ncycles; i++){

        S1_old = S1_new;
        S2_old = S2_new;
        E1_old = E1_new;
        E2_old = E2_new;

        //S.countUp();
        if (n1 != S.nplus) cout << n1 << " " << S.nplus << endl;

        idx1 = rand()%(2*nspins); // index of the spin to flip
        idx2 = rand()%(2*nspins); // index of the spin to flip
        S.flip(idx1, idx2);
        new_energy = S.Hamiltonian();
        deltaE = new_energy - old_energy;
        if (deltaE < 0) S.demon_energy += abs(deltaE);
        else {
            if (S.demon_energy < deltaE) {S.flip(idx1, idx2);}
            else {
                S.demon_energy -= deltaE;
            }
        } 
        
        for(int j=0; j<S1.N; j++){
            for(int k=0; k<S1.N; k++){
                S1.states[j][k] = S.states[j][k];
            }
        } 
        for(int j=0; j<S2.N; j++){
            for(int k=0; k<S2.N; k++){
                S2.states[j][k] = S.states[j][k];
            }
        }
        S1.countUp();
        S2.countUp();

        E1_new = S1.Hamiltonian();
        E2_new = S2.Hamiltonian();
        S1_new = S1.Entropy();
        S2_new = S2.Entropy();

        //if (S.checkAnomaly()) cout << i << endl;

        cout << "Demon: " << S.demon_energy/S.E*100 << endl; 
    
        outfile << i << "," << S1_new << "," << S2_new << "," << S.Entropy() << "," << E1_new << "," << E2_new << endl; 
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
            cout << i << " " << j << " " << S.Nrows << " " << S.Ncols << endl;
            S2.states[i][j] = S.states[i+S1.N][j];
        }
    }
    S1.countUp();
    S2.countUp();
    /************************************************************/ 



    cout << "Spin up S1: " << S1.nplus << "\t\t Spin up S2: " << S2.nplus << " " << endl;




    return 0;
}