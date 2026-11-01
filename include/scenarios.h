#pragma once
#include "linearCode.h"
#include "channel.h"
#include <vector>

class Scenarios {
    private:
        LinearCode& linearCode;
        Channel& channel;
        void runVectorScenario();
        void runTextScenario();
        void runImageScenario();
        std::vector<int> sendBitsWithoutCode(const std::vector<int>& bits);
        std::vector<int> sendBitsWithCode(const std::vector<int>& bits);
    public:
        Scenarios(LinearCode& linearCode, Channel& channel);
        void runScenarios();
};