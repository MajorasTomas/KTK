#include "../include/linearCode.h"

using namespace std;

LinearCode::LinearCode(int k, int n, int q, vector<vector<int>> A) : k(k), n(n), q(q), G(k, vector<int>(n, 0)), H(n-k, vector<int>(n, 0)) {
    createGenerationMatrix(A);
    createControlMatrix();
    createSyndromeTable();
}

void LinearCode::createGenerationMatrix(vector<vector<int>> A) {
    for(int i=0; i<k; i++) {
        for(int j=0; j<k; j++) {
            if(i==j) {
                G[i][j] = 1;
            } else {
                G[i][j] = 0;
            }
        }
    }

    for(int i=0; i<k; i++) {
        for(int j=k; j<n; j++) {
            G[i][j] = A[i][j-k];
        }
    }
}

void LinearCode::createControlMatrix() {
    for(int i=0; i<k; i++) {
        for(int j=0; j<n-k; j++) {
            H[j][i] = G[i][j+k];
        }
    }

    for(int i=0; i<n-k; i++) {
        for(int j=0; j<n-k; j++) {
            if(i==j) {
                H[i][j+k] = 1;
            } else {
                H[i][j+k] = 0;
            }         
        }
    }
}

vector<int> LinearCode::multiplyControlMatrixByVector(const vector<int>& V) {
    vector<int> output;
    for(int i=0; i<n-k; i++) {
        int sum = 0;
        for(int j=0; j<n; j++) {
            sum += H[i][j] * V[j];
        }
        output.push_back(sum % 2);
    }
    return output;
}

vector<int> LinearCode::multiplyVectorByGenerationMatrix(const vector<int>& V) {
    vector<int> output;
    for(int i=0; i<n; i++) {
        int sum = 0;
        for(int j=0; j<k; j++) {
            sum += V[j] * G[j][i];
        }
        output.push_back(sum % 2);
    }
    return output;
}

void LinearCode::recursionWeightN(vector<int> A, int remaining, int start) {
    if(remaining == 0) {
        vector<int> result = multiplyControlMatrixByVector(A);
        if(syndromeTable.count(result) == 0) {
            syndromeTable[result] = A;
        }
        return;
    }
    for(int i=start; i<=n-remaining; i++) {
        if(syndromeTable.size() == syndromeCount) break;
        vector<int> B = A;
        B[i] = 1;
        recursionWeightN(B, remaining-1, i+1);
    }
}

void LinearCode::createSyndromeTable() {
    syndromeCount = 1;
    for(int i=0; i<n-k; i++) {
        syndromeCount *= q;
    } 

    for(int i=0; i<=n; i++) {
        vector<int> leaderContestant(n, 0);
        recursionWeightN(leaderContestant, i, 0);
        if(syndromeTable.size() == syndromeCount) break;
    }
}

int LinearCode::getGenerationMatrixEntry(int i, int j) {
    return G[i][j];
}

int LinearCode::getControlMatrixEntry(int i, int j) {
    return H[i][j];
}

int LinearCode::getN() {
    return n;
}

int LinearCode::getK() {
    return k;
}

int LinearCode::getSyndromeCount() {
    return syndromeCount;
}

const map<vector<int>, vector<int>>& LinearCode::getSyndromeTable() {
    return syndromeTable;
}