#include "../include/channel.h"
#include <ctime>

using namespace std;

Channel::Channel(double ep) : ep(ep), mt(time(nullptr)) {};

double Channel::getEp() {
    return ep;
}

vector<int> Channel::sendCode(const std::vector<int>& inputVector) {
    uniform_real_distribution<double> distribution(0.0, 1.0);
    vector<int> outputVector;
    for(auto symbol : inputVector) {
        if(distribution(mt) < ep) {
            outputVector.push_back((symbol + 1) % 2);
        } else {
            outputVector.push_back(symbol);
        }
    }
    return outputVector;
}