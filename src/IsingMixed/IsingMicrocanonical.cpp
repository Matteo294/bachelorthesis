#include "IsingMicrocanonical.h"

IsingMicrocanonical::IsingMicrocanonical(double E, int Nrows, int Ncols, double J, double B) : states(Nrows, vector<double>(Ncols, -0.5)){
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
    double energy = -0.5*(this->Nrows + this->Ncols); // All spins down at the beginning
    int flag = 1;
    while (flag){      
        idx1 = rand()%Ncols;
        idx2 = rand()%Nrows;
        if (this->states[idx1][idx2] < 0) {
            //this->flip(idx1, idx2);
            energy += (double) 1;
            if (energy >= this->E) flag = 0;
        }
    }
    
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
        s1 += this->states[i][this->Ncols-1];
    }
    for (int j=0; j<this->Ncols; j++) s1 += this->states[this->Nrows-1][j];
    this->E = s1*this->B - s2*this->J;
    return this->E;
}

void IsingMicrocanonical::countUp(){
    int count = 0;
    for(int i=0; i<this->Nrows; i++){
        for(int j=0; j<this->Ncols; j++){
            if (this->states[i][j] > 0) count++;
        }
    }
    this->nplus = count;
}


void IsingMicrocanonical::flip(int idx1, int idx2){
    this->states[idx1][idx2] = (double) -1*this->states[idx1][idx2];
    if (this->states[idx1][idx2] > 0) this->nplus++;
    else this->nplus--;
}