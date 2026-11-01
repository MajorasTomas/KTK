#include "../include/initialization.h"
#include "../include/scenarios.h"

int main() {
    Initialization initialization;
    LinearCode linearCode = initialization.initializeLinearCode();
    Channel channel = initialization.initializeChannel();

    initialization.printLinearCodeInitializationStatus(linearCode);
    initialization.printChannelInitializationStatus(channel);

    Scenarios scenarios(linearCode, channel);
    scenarios.runScenarios();
}
