#pragma once
#include <vector>
#include<map>

class LinearCode {
    private:
        int k, n, q, syndromeCount;
        std::vector<std::vector<int>> G;
        std::vector<std::vector<int>> H;
        std::map<std::vector<int>, std::vector<int>> syndromeTable;
        void recursionWeightN(std::vector<int> A, int remaining, int start);
        void createGenerationMatrix(std::vector<std::vector<int>> A);
        void createControlMatrix();
        void createSyndromeTable();

    public:
        LinearCode(int k, int n, int q, std::vector<std::vector<int>> A);
        int getGenerationMatrixEntry(int i, int j);
        int getControlMatrixEntry(int i, int j);
        int getN();
        int getK();
        int getSyndromeCount();
        const std::map<std::vector<int>, std::vector<int>>& getSyndromeTable();
        std::vector<int> multiplyVectorByGenerationMatrix(const std::vector<int>& V);
        std::vector<int> multiplyControlMatrixByVector(const std::vector<int>& V);
};