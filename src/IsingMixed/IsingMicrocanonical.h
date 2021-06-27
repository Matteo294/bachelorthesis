#pragma once 
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class IsingMicrocanonical{
    public:
        IsingMicrocanonical(double E, int Nx, int Ny, double J, double B);
        bool checkAnomaly();
        double Hamiltonian();
        double Entropy(int n=0);
        void countUp();
        void flip(int idx1, int idx2);
        double E;
        double demon_energy;
        int Nrows, Ncols;
        double J;
        double B;
        vector<vector<double>> states;
        int nplus;
};