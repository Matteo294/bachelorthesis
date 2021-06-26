#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include "IsingCanonical.h"

using namespace std;

int main(){

    srand(time(NULL));

    const int nspins = 100;
    const int ncycles = 1e7;
    const double B = 1.0;
    const double J = 0.5;
    const double Temp = 0.1;
    vector<double> temps {-20, -10, -7, -4, -2, -1, -0.5, -0.1, -0.01, 0.01, 0.1, 0.5, 1, 2, 4, 7, 10, 20};
    int ntemp = temps.size();
    ofstream myfile;
    myfile.open("data.csv");
    myfile << "Temperatures,Energies" << endl;

    IsingCanonical S(Temp, nspins, J, B);
    int idx;
    double old_energy = S.Hamiltonian();
    double new_energy = 0.0;
    long double Energy_sum = 0.0;

    for(int n=0; n<ntemp; n++){
        S.T = temps[n];
        cout << "T: " << S.T << endl;
        old_energy = S.Hamiltonian();
        new_energy = 0.0;
        Energy_sum = 0.0;
        for(int i=0; i<ncycles; i++){
            idx = rand()%nspins; // index of the spin to flip
            S.flip(idx);
            new_energy = S.Hamiltonian();
            if (S.T < 0){
                if ( (new_energy > old_energy) || (exp((old_energy - new_energy)/S.T) > (double)rand()/RAND_MAX)){
                    old_energy = new_energy;
                }
                else S.flip(idx);
                Energy_sum += old_energy;
            } else{
                if ( (new_energy < old_energy) || (exp((old_energy - new_energy)/S.T) > (double)rand()/RAND_MAX)){
                    old_energy = new_energy;
                }
                else S.flip(idx);
                Energy_sum += old_energy;
            }
        }
        myfile << temps[n] << "," << Energy_sum/ncycles << endl;
    }
    myfile.close();

    return 0;
}
