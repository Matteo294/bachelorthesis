#include "IsingMicrocanonical.h"

IsingMicrocanonical::IsingMicrocanonical(double E, int N, double J, double B) : states(N, -0.5){
    this->E = E;
    this->N = N;
    this->J = J;
    this->B = B;
    this->demon_energy = 0.0;
    float rnd_spin;
    this->nplus = 0;

    int idx;
    double energy = -0.5*N; // All spins down at the beginning
    int flag = 1;
    while (flag){      
        idx = rand()%N;
        if (this->states[idx] < 0) {
            this->flip(idx);
            energy += (double) 1;
            if (energy >= this->E) flag = 0;
        }
    }
    /*for(int i=0; i<this->N; i++) this->states[i] = -0.5;
    this->nplus = this->N;
    this->demon_energy = this->E + this->N*0.5;*/
}

double IsingMicrocanonical::Entropy(){
    double nmin = this->N - this->nplus;
    return this->N*log(this->N) - this->nplus*log(this->nplus) - nmin*log(nmin);
}

double IsingMicrocanonical::Hamiltonian(){
    double s1 = 0.0;
    double s2 = 0.0;
    for(int i=0; i<this->N-1; i++){
        s1 += this->states[i];
        s2 += this->states[i]*this->states[i+1];
    }
    s1 += this->states[this->N-1];
    return s1*this->B - s2*this->J + this->demon_energy;
}

void IsingMicrocanonical::flip(int idx){
    this->states[idx] = -this->states[idx];
    if (this->states[idx] > 0) this->nplus++;
    else this->nplus--;
}