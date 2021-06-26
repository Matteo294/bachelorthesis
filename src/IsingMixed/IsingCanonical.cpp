#include "IsingCanonical.h"

using namespace std;

IsingCanonical::IsingCanonical(double T, int N, double J, double B) : states(N){
    this->T = T;
    this->N = N;
    this->J = J;
    this->B = B;
    float rnd_spin;
    for(int i=0; i<N; i++){
        rnd_spin = (rand()%2 - 0.5); // select 0 or 1 and convert into +-1/2 spin
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

void IsingCanonical::countUp(){
    int count = 0;
    for(int i=0; i<this->N; i++){
        if (this->states[i] > 0) count++;
    }
    this->nplus = count;
}

double IsingCanonical::Entropy(int n){
    double nmin;
    if (n==0) n=this->nplus;
    nmin = this->N - n;
    return this->N*log(this->N) - n*log(n) - nmin*log(nmin);
}

void IsingCanonical::thermalize(int ncycles){
    double old_energy, new_energy, deltaE, Esum;
    int idx;
    old_energy = this->Hamiltonian();
    new_energy = old_energy;
    deltaE = 0.0;
    Esum = 0.0;
    for(int i=0; i<ncycles; i++){
            idx = rand()%this->N; // index of the spin to flip
            this->flip(idx);
            new_energy = this->Hamiltonian();
            if (this->T < 0){
                if ( (new_energy > old_energy) || (exp((old_energy - new_energy)/this->T) > (double)rand()/RAND_MAX)){
                    old_energy = new_energy;
                }
                else this->flip(idx);
            } else{
                if ( (new_energy < old_energy) || (exp((old_energy - new_energy)/this->T) > (double)rand()/RAND_MAX)){
                    old_energy = new_energy;
                }
                else this->flip(idx);
            }
        }
}