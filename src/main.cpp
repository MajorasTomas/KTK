#include "../include/initialization.h"

int main() {
    Initialization initialization;
    LinearCode linearCode = initialization.initializeLinearCode();
    Channel channel = initialization.initializeChannel();
    return 0;
}
