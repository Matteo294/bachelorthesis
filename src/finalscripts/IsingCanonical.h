
#pragma once 
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class IsingCanonical{
    public:
        IsingCanonical(double T, int N, double J, double B);
        double Hamiltonian();
        void thermalize(int ncycles);
        void countUp();
        double Entropy(int n=0);
        double flip(int idx1, int idx2);
        double T;
        int N;
        double J;
        double B;
        double E;
        double avgE;
        vector<vector<double>> states;
        int nplus;
};