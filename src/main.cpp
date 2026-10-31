#include "../include/initialization.h"

int main() {
    Initialization initialization;
    LinearCode linearCode = initialization.initializeLinearCode();
    Channel channel = initialization.initializeChannel();

    initialization.printLinearCodeInitializationStatus(linearCode);
    initialization.printChannelInitializationStatus(channel);
}
