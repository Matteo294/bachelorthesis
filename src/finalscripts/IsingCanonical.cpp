#include "IsingCanonical.h"

using namespace std;

IsingCanonical::IsingCanonical(double T, int N, double J, double B) : states(N, vector<double>(N, -1)){
    srand(time(NULL));
    this->T = T;
    this->N = N;
    this->J = J;
    this->B = B;
    float rnd_spin;
    /*for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            rnd_spin = (rand()%2 - 0.5); // select 0 or 1 and convert into +-1/2 spin
            this->states[i][j] = rnd_spin;
            if (rnd_spin > 0) this->nplus++;
        }
    }*/
    this->nplus = 0.0;
}

// remember mu=1
double IsingCanonical::Hamiltonian(){
    double s1 = 0.0;
    double s2 = 0.0;
    for(int i=0; i<this->N-1; i++){
        for(int j=0; j<this->N-1; j++){
            s1 += this->states[i][j];
            s2 += this->states[i][j]*this->states[i][j+1];
            s2 += this->states[i][j]*this->states[i+1][j];
        }
        s1 += this->states[i][this->N-1];
    }
    for (int j=0; j<this->N; j++) s1 += this->states[this->N-1][j];
    return s1*this->B - s2*this->J;
}

void IsingCanonical::flip(int idx1, int idx2){
    this->states[idx1][idx2] = -this->states[idx1][idx2];
    if (this->states[idx1][idx2] > 0) this->nplus++;
    else this->nplus--;
}

void IsingCanonical::countUp(){
    int count = 0;
    for(int i=0; i<this->N; i++){
        for(int j=0; j<this->N; j++){
            if (this->states[i][j] > 0) count++;
        }
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
    int idx1, idx2;
    old_energy = this->Hamiltonian();
    new_energy = old_energy;
    deltaE = 0.0;
    Esum = 0.0;
    for(int i=0; i<ncycles; i++){
            idx1 = rand()%this->N; // index of the spin to flip
            idx2 = rand()%this->N; // index of the spin to flip
            this->flip(idx1, idx2);
            new_energy = this->Hamiltonian();
            if ( (((new_energy - old_energy) / T) < 0) || (exp((new_energy - old_energy)/this->T) < (double)rand()/RAND_MAX)){
                old_energy = new_energy;
            }
            else this->flip(idx1, idx2);
        }
}