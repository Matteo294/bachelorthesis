#pragma once 
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class IsingMicrocanonical{
    public:
        IsingMicrocanonical(double E, int N, double J, double B);
        double Hamiltonian();
        double Entropy();
        void flip(int idx);
        double E;
        double demon_energy;
        int N;
        double J;
        double B;
        vector<double> states;
        int nplus;
};