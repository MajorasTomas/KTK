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
    public:
        Scenarios(LinearCode& linearCode, Channel& channel);
        void runScenarios();
};