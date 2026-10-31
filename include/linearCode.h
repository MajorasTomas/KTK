#pragma once
#include <vector>

class LinearCode {
    private:
        int k, n, q;
        std::vector<std::vector<int>> G;

    public:
        LinearCode(int k, int n, int q, std::vector<std::vector<int>> A);
        void updateGenerationMatrixEntry(int i, int j, int val);
        int getGenerationMatrixEntry(int i, int j);
};