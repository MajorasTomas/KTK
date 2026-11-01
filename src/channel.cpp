#include "../include/channel.h"

using namespace std;

Channel::Channel(double ep) : ep(ep) {};

double Channel::getEp() {
    return ep;
}