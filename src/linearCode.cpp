#include "../include/linearCode.h"

using namespace std;

LinearCode::LinearCode(int k, int n, int q, vector<vector<int>> A) : k(k), n(n), q(q), G(k, vector<int>(n, 0)), H(n-k, vector<int>(n, 0)) {
    createGenerationMatrix(A);
    createControlMatrix();
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
            H[j][i] = ((-1 * G[i][j+k]) + q) % q;
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

int LinearCode::getGenerationMatrixEntry(int i, int j) {
    return G[i][j];
}

int LinearCode::getControlMatrixEntry(int i, int j) {
    return H[i][j];
}