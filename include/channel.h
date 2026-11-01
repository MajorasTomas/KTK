#pragma once
#include <vector>
#include <random>

class Channel {
    private:
        double ep;
        std::mt19937 mt;

    public:
        Channel(double ep);
        double getEp();
        std::vector<int> sendCode(const std::vector<int>& inputVector);
};