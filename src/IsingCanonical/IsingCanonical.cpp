#pragma once
#include "IsingCanonical.h"

using namespace std;

IsingCanonical::IsingCanonical(double T, int N, double J, double B) : states(N){
    this->T = T;
    this->N = N;
    this->J = J;
    this->B = B;
    float rnd_spin;
    for(int i=0; i<N; i++){
        rnd_spin = 0.5 * (rand()%2 - 1); // select 0 or 1 and convert into +-1/2 spin
        this->states[i] = rnd_spin;
        if (rnd_spin > 0) this->nplus++;
    }
}

// remember mu=1
double IsingCanonical::Hamiltonian(){
    double s1 = 0.0;
    double s2 = 0.0;
    for(int i=0; i<this->N-1; i++){
        s1 += this->states[i];
        s2 += this->states[i]*this->states[i+1];
    }
    s1 += this->states[this->N-1];
    return s1*this->B - s2*this->J;
}

void IsingCanonical::flip(int idx){
    this->states[idx] = -this->states[idx];
    if (this->states[idx] > 0) this->nplus++;
    else this->nplus--;
}