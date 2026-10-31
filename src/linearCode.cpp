#include "../include/linearCode.h"

using namespace std;

LinearCode::LinearCode(int k, int n, int q, vector<vector<int>> A) : k(k), n(n), q(q), G(k, vector<int>(n, 0)) {
    for(int i=0; i<k; i++) {
        for(int j=0; j<k; j++) {
            if(i==j) {
                updateGenerationMatrixEntry(i, j, 1);
            } else {
                updateGenerationMatrixEntry(i, j, 0);
            }
        }
    }

    for(int i=0; i<k; i++) {
        for(int j=k; j<n; j++) {
            updateGenerationMatrixEntry(i, j, A[i][j-k]);
        }
    }
}

void LinearCode::updateGenerationMatrixEntry(int i, int j, int val) {
        G[i][j] = val;
}

int LinearCode::getGenerationMatrixEntry(int i, int j) {
    return G[i][j];
}