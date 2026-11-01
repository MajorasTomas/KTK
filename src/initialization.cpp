#include "../include/initialization.h"
#include "../include/channel.h"
#include <iostream>
#include <ctime>
#include <random>

using namespace std;

void Initialization::inputK() {
    while(true){
        cout<<"Iveskite tiesinio kodo dimensija k (k > 0): ";
        cin>>k;
        cout<<endl;
        if(k > 0) break;
    }
}

void Initialization::inputN() {
    while(true){
        cout<<"Iveskite tiesinio kodo ilgi n (n >= k): ";
        cin>>n;
        cout<<endl;
        if(n >= k) break;
    }
}

void Initialization::inputA() {
    if(n > k) {
        string check;
        cout<<"Jei norite patys ivesti standartinio pavidalo generuojancios matricos narius, spauskite 1. Jei norite ja sugeneruoti automatiskai spauskite bet koki kita simboli: ";
        cin>>check;
        if(check == "1") {
            cout<<"Iveskite standartinio pavidalo generuojancios matricos " << k << " eiluciu, likusiu " << n-k << " stulpeliu narius (bus imamos ivestu skaiciu mod 2 reiksmes)" << endl;
            for(int i=0; i<k; i++) {
                vector<int> row;
                for(int j=k; j<n; j++) {
                    int val;
                    cout<<"Iveskite " << i+1 << "-osios eilutes " << j+1 << "-aji nari: ";
                    cin>>val;
                    cout<<endl;
                    val = abs(val % q);
                    row.push_back(val);
                }
                A.push_back(row);
            }
        } else {
            mt19937 mt(time(nullptr));
            uniform_int_distribution<> distribution(0, q - 1);
            for(int i=0; i<k; i++) {
                vector<int> row;
                for(int j=k; j<n; j++) {
                    int val = distribution(mt);
                    row.push_back(val);
                }
                A.push_back(row);
            }
        }
    }
}

void Initialization::inputEp() {
    while(true){
        cout<<"Iveskite simbolio iskraipymo kanalu tikimybe ep (0 <= ep <= 1): ";
        cin>>ep;
        cout<<endl;
        if(ep >= 0 && ep <= 1) break;
    }
}

void Initialization::printLinearCodeInitializationStatus(LinearCode& linearCode) {
    cout<<"Jusu (" << linearCode.getK() << ", " << linearCode.getN() << ") generuojanti standartinio pavidalo matrica: "<<endl;

    for(int i=0; i<linearCode.getK(); i++) {
        for(int j=0; j<linearCode.getN(); j++) {
            cout << linearCode.getGenerationMatrixEntry(i, j) << " ";
        }
        cout<<endl;
    }

    cout<<"Jusu (" << linearCode.getN() - linearCode.getK() << ", " << linearCode.getN() << ") kontroline matrica: "<<endl;
     
    for(int i=0; i<n-k; i++) {
        for(int j=0; j<n; j++) {
            cout << linearCode.getControlMatrixEntry(i, j) << " ";
        }
        cout<<endl;
    }

    cout<<"Jusu kodo (sindromas, svoris) lentele: " << endl;
    for(const auto& [syndrome, weight] : linearCode.getSyndromeTable()) {
        for(auto symbol : syndrome) {
            cout<<symbol;
        }
        cout<<", ";
        cout<<weight;
        cout<<endl;
    }
}

void Initialization::printChannelInitializationStatus(Channel& channel) {
    cout<<"Tikimybe, jog is jusu kanalo iseis klaidingas simbolis yra: "<< channel.getEp() <<endl;
}

LinearCode Initialization::initializeLinearCode() {
    inputK();
    inputN();
    inputA();
    LinearCode linearCode(k, n, q, A);
    return linearCode;
}

Channel Initialization::initializeChannel() {
    inputEp();
    Channel channel(ep);
    return channel;
}
