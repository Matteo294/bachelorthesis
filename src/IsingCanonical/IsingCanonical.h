#pragma once 
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class IsingCanonical{
    public:
        IsingCanonical(double T, int N, double J, double B);
        double Hamiltonian();
        void flip(int idx);
        double T;
        int N;
        double J;
        double B;
        vector<double> states;
        int nplus;
};