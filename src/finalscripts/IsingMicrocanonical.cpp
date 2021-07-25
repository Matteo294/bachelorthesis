#include "IsingMicrocanonical.h"

IsingMicrocanonical::IsingMicrocanonical(double E, int Nrows, int Ncols, double J, double B) : states(Nrows, vector<double>(Ncols, -1)){
    srand(time(NULL));
    this->E = E;
    this->Ncols = Ncols;
    this->Nrows = Nrows;
    //this->N = Ncols + Nrows;
    this->J = J;
    this->B = B;
    this->demon_energy = 0.0;
    float rnd_spin;
    this->nplus = 0;

    int idx1, idx2;
    double energy = this->Hamiltonian(); // All spins down
    int flag = 1;
    // Flip spins untill reach the desired energy
    while (flag){      
        idx1 = rand()%Ncols;
        idx2 = rand()%Nrows;
        if (this->states[idx1][idx2] < 0) {
            this->flip(idx1, idx2);
            energy = this->Hamiltonian();
            if (energy >= this->E) {flag = 0; this->flip(idx1, idx2);}
        }
    }
    this->E = this->Hamiltonian();
    
    cout << "initialized" << endl;
}

double IsingMicrocanonical::Entropy(int n){
    int N = this->Ncols + this->Nrows;
    double nmin;
    if (n==0) n=this->nplus;
    nmin = N - n;
    return N*log(N) - n*log(n) - nmin*log(nmin);
}

// remember mu=1
double IsingMicrocanonical::Hamiltonian(){
    double s1 = 0.0;
    double s2 = 0.0;
    for(int i=0; i<this->Nrows-1; i++){
        for(int j=0; j<this->Ncols-1; j++){
            s1 += this->states[i][j];
            s2 += this->states[i][j]*this->states[i][j+1];
            s2 += this->states[i][j]*this->states[i+1][j];
        }
        s1 += this->states[i][this->Nrows-1];
        s2 += this->states[i][this->Ncols-1]*this->states[i+1][this->Ncols-1];
    }
    for (int j=0; j<this->Nrows; j++){
        s1 += this->states[this->Nrows-1][j];
        s2 += this->states[this->Ncols-1][j]*this->states[this->Nrows-1][j+1];
    }
    this->E = -s1*this->B - s2*this->J;
    return this->E;
}

void IsingMicrocanonical::countUp(){
    int count = 0;
    for(int i=0; i<this->Nrows; i++){
        for(int j=0; j<this->Ncols; j++){
            if (this->states[i][j] < 0) count++;
        }
    }
    this->nplus = count;
}


double IsingMicrocanonical::flip(int idx1, int idx2){
    double delta = 0.0;

    if(idx1<this->Nrows-1) delta += this->states[idx1+1][idx2];
    if(idx2<this->Ncols-1) delta += this->states[idx1][idx2+1];
    if(idx1>0) delta += this->states[idx1-1][idx2];
    if(idx2>0) delta += this->states[idx1][idx2-1];

    delta = +2*this->states[idx1][idx2]*delta*J +2*this->states[idx1][idx2]*this->B;

    this->E += delta;

    this->states[idx1][idx2] = (double) -1*this->states[idx1][idx2];
    if (this->states[idx1][idx2] < 0) this->nplus++;
    else this->nplus--;

    return delta; // returns Enew - Eold
}