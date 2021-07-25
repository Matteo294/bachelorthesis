#include "IsingCanonical.h"
#include <fstream>
#include <cmath>
#include <random>

using namespace std;

IsingCanonical::IsingCanonical(double T, int N, double J, double B) : states(N, vector<double>(N, 1)){
    srand(time(NULL));
    this->T = T;
    this->N = N;
    this->J = J;
    this->B = B;
    float rnd_spin;
    this->nplus = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            rnd_spin = (rand()%2)*2 - 1; // select 0 or 1 and convert into +-1 spin
            this->states[i][j] = rnd_spin;
            if (rnd_spin < 0) this->nplus++;
        }
    }
    this->E = this->Hamiltonian();
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
        s2 += this->states[i][this->N-1]*this->states[i+1][this->N-1];
    }
    for (int j=0; j<this->N; j++){
        s1 += this->states[this->N-1][j];
        s2 += this->states[this->N-1][j]*this->states[this->N-1][j+1];
    }
    return -s1*this->B - s2*this->J;
}

double IsingCanonical::flip(int idx1, int idx2){
    double delta = 0.0;

    if(idx1<this->N-1) delta += this->states[idx1+1][idx2];
    if(idx2<this->N-1) delta += this->states[idx1][idx2+1];
    if(idx1>0) delta += this->states[idx1-1][idx2];
    if(idx2>0) delta += this->states[idx1][idx2-1];

    delta = +2*this->states[idx1][idx2]*delta*this->J +2*this->states[idx1][idx2]*this->B;

    this->E += delta;

    this->states[idx1][idx2] = (double) -1*this->states[idx1][idx2];
    if (this->states[idx1][idx2] > 0) this->nplus--;
    else this->nplus++;

    return delta; // returns Enew - Eold
}

void IsingCanonical::countUp(){
    int count = 0;
    for(int i=0; i<this->N; i++){
        for(int j=0; j<this->N; j++){
            if (this->states[i][j] < 0) count++;
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
    uniform_int_distribution<> uniform(0.0, this->N-1);
    random_device rd1, rd2;
    mt19937_64 gen1(rd1()), gen2(rd2());
    int idx1, idx2;
    double deltaE;
    double r;
    int accepted = 0;
    cout << "Temp " << this->T << endl;
    this->avgE = 0.0;
    int ntherm = (int) ncycles/10;
    this->E = this->Hamiltonian();
    for(int i=0; i<ncycles; i++){
        idx1 = uniform(gen1);
        idx2 = uniform(gen2);
        deltaE = this->flip(idx1, idx2);
        r = (double)rand()/RAND_MAX;
        if ( ((deltaE/this->T) < 0) || (exp(-deltaE/this->T) > r)){
            accepted++;
            this->E += deltaE;
        }
        else this->flip(idx1, idx2);
        if (i>=ntherm){
            this->avgE += this->E;
        }
    }
    this->avgE /= (ncycles-ntherm);
}