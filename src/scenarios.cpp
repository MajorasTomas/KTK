#include "../include/scenarios.h"
#include <iostream>

using namespace std;

Scenarios::Scenarios(LinearCode& linearCode, Channel& channel) : linearCode(linearCode), channel(channel) {}

string vectorToString(const vector<int>& v) {
    string text = "";
    for(auto symbol : v) {
        text += (symbol == 0) ? '0' : '1';
    }
    return text;
}

vector<int> stringToVector(const string& text) {
    vector<int> result;
    for(auto symbol : text) {
        if(symbol == '0') {
            result.push_back(0);
        } else {
            result.push_back(1);
        }
    }
    return result;
}

vector<int> findMistakesIndexes(const vector<int>& encodedVector, const vector<int>& sentVector) {
    vector<int> result;
    for(int i=0; i<encodedVector.size(); i++) {
        if(encodedVector[i] != sentVector[i]) {
            result.push_back(i);
        }  
    }
    return result;
}

bool checkIsVectorTextCorrectFormat(const string& text, int length) {
    if(text.length() != length) return false;
    for(auto symbol : text) {
        if(symbol != '0' && symbol != '1') return false;
    }
    return true;
}

void Scenarios::runVectorScenario() {
    while(true) {
        string messageText;
        cout<<"Iveskite dvejetaini "<<linearCode.getK()<<" simboliu ilgio pranesima: "<<endl;
        cin>>messageText;
        cout<<endl;
        if(!checkIsVectorTextCorrectFormat(messageText, linearCode.getK())){
            cout<<"Pranesimas turi buti "<<linearCode.getK()<<" simboliu ilgio dvejetainis vektorius"<<endl;
            continue;
        }
        vector<int> message = stringToVector(messageText);
        vector<int> encodedVector = linearCode.encodeVector(message);
        string encodedVectorText = vectorToString(encodedVector);
        vector<int> sentVector = channel.sendCode(encodedVector);
        string sentVectorText = vectorToString(sentVector);

        vector<int> mistakesIndexes = findMistakesIndexes(encodedVector, sentVector);

        cout<<"Pranesimas "<<messageText<<" uzkoduotas vektoriumi "<<encodedVectorText<<endl;
        cout<<"Is kanalo isejo vektorius: "<<sentVectorText<<" , padarytos "<<mistakesIndexes.size()<<" klaidos";

        if(mistakesIndexes.size() > 0) {
            cout<<", pozicijose: ";
            for(auto index : mistakesIndexes) {
                cout<<index+1<<" ";  
            }
        }
        cout<<endl;
        
        string changedVectorText;
        cout<<"Ar norite pakeisti issiusta vektoriu? Jei taip, iveskite "<<linearCode.getN()<<" simboliu ilgio dvejetaini vektoriu. Jei ne, iveskite bet koki kita teksta: "<<endl;
        cin>>changedVectorText;
        cout<<endl;
        if(checkIsVectorTextCorrectFormat(changedVectorText, linearCode.getN())) {
            sentVector = stringToVector(changedVectorText);
            cout<<"Issiustas vektorius pakeistas i: "<<changedVectorText<<endl;
        } else {
            cout<<"Issiustas vektorius nepakeistas"<<endl;
        }

        vector<int> decodedVector = linearCode.decodeVector(sentVector);
        string decodedVectorText = vectorToString(decodedVector);
        cout<<"Dekoduotas vektorius: "<<decodedVectorText<<endl;

        string decodedMessageText = decodedVectorText.substr(0, linearCode.getK());
        cout<<"Dekoduotas pranesimas: "<<decodedMessageText<<endl;
        break;
    }    
}

void Scenarios::runTextScenario() {}

void Scenarios::runImageScenario() {}

void Scenarios::runScenarios() {
    string choice;
    while(true) {
        cout<<"Iveskite kuri scenariju (1, 2 ar 3) vykdyti. Norint nutraukti scenarijus, spauskite bet koki kita simboli: ";
        cin>>choice;
        cout<<endl;

        if(choice == "1") {
            runVectorScenario();
        } else if(choice == "2") {
            runTextScenario();
        } else if (choice == "3") {
            runImageScenario();
        } else {
            break;
        }
    }
}