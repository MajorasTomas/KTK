#pragma once
#include "linearCode.h"
#include "channel.h"

class Initialization {
    private:
        int k, n, q=2;
        double ep;
        std::vector<std::vector<int>> A;

        void inputK();
        void inputN();
        void inputA();
        void inputEp();

    public:
        LinearCode initializeLinearCode();
        Channel initializeChannel();
        void printLinearCodeInitializationStatus(LinearCode& linearCode);
        void printChannelInitializationStatus(Channel& channel);
};