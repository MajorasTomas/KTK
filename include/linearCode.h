#pragma once
#include <vector>

class LinearCode {
    private:
        int k, n, q;
        std::vector<std::vector<int>> G;
        std::vector<std::vector<int>> H;
        void createGenerationMatrix(std::vector<std::vector<int>> A);
        void createControlMatrix();

    public:
        LinearCode(int k, int n, int q, std::vector<std::vector<int>> A);
        int getGenerationMatrixEntry(int i, int j);
        int getControlMatrixEntry(int i, int j);
};