#include "../include/scenarios.h"
#include <iostream>
#include <limits>

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

vector<int> textToBits(const string& text) {
    vector<int> bits;
    for(char c : text) {
        for(int i=7; i>=0; i--) {
            bits.push_back((c >> i) & 1);
        }
    }
    return bits;
}

string bitsToText(const vector<int>& bits) {
    string text;
    for(int i=0; i<bits.size(); i+=8) {
        int byte = 0;
        for(int j=0; j<8; j++) {
            byte = byte * 2 + bits[i+j];
        }
        text += (char)byte;
    }
    return text;
}

vector<vector<int>> splitIntoPieces(const vector<int>& bits, int pieceLength) {
    vector<vector<int>> output;
    int artificalEndingBitsCount = (pieceLength - bits.size() % pieceLength) % pieceLength;
    vector<int> divisbleVector = bits;
    for(int i=0; i<artificalEndingBitsCount; i++) {
        divisbleVector.push_back(0);
    }
    int parts = divisbleVector.size() / pieceLength;
    for(int i=0; i<parts; i++) {
        vector<int> piece;
        for(int j=0; j<pieceLength; j++) {
            piece.push_back(divisbleVector[i*pieceLength + j]);
        }
        output.push_back(piece);
    }
    return output;
}

vector<int> joinPieces(const vector<vector<int>>& pieces, int originalLength) {
    vector<int> output;
    for(int i=0; i<pieces.size(); i++) {
        for(int j=0; j<pieces[i].size(); j++) {
            output.push_back(pieces[i][j]);
            if(output.size() == originalLength) break;
        }
    }
    return output;
}

std::vector<int> Scenarios::sendBitsWithoutCode(const std::vector<int>& bits) {
    vector<vector<int>> pieces = splitIntoPieces(bits, linearCode.getK());
    vector<vector<int>> sentPieces;
    for(const auto& piece : pieces) {
        sentPieces.push_back(channel.sendCode(piece));
    }
    return joinPieces(sentPieces, bits.size());
}

std::vector<int> Scenarios::sendBitsWithCode(const std::vector<int>& bits) {
    vector<vector<int>> pieces = splitIntoPieces(bits, linearCode.getK());
    vector<vector<int>> encodedPieces;
    for(const auto& piece : pieces) {
        encodedPieces.push_back(linearCode.encodeVector(piece));
    }
    vector<vector<int>> sentPieces;
    for(const auto& encodedPiece : encodedPieces) {
        sentPieces.push_back(channel.sendCode(encodedPiece));
    }
    vector<vector<int>> decodedPieces;
    for(const auto& sentPiece : sentPieces) {
        decodedPieces.push_back(linearCode.decodeVector(sentPiece));
    }
    vector<vector<int>> decodedMessages;
    for(const auto& decodedPiece : decodedPieces) {
        decodedMessages.push_back(linearCode.decodeVectorToMessage(decodedPiece));
    }
    return joinPieces(decodedMessages, bits.size());
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

        vector<int> decodedMessage = linearCode.decodeVectorToMessage(decodedVector);
        string decodedMessageText = vectorToString(decodedMessage);
        cout<<"Dekoduotas pranesimas: "<<decodedMessageText<<endl;
        break;
    }    
}

void Scenarios::runTextScenario() {
    string text;
    cout<<"Iveskite teksta: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, text);
    cout<<endl;
    vector<int> textBits = textToBits(text);
    cout<<"Rezultatas, siunciant kanalu nekoduojant: ";
    vector<int> bitsWithoutCode = sendBitsWithoutCode(textBits);
    string textWithoutCode = bitsToText(bitsWithoutCode);
    cout<<textWithoutCode;
    cout<<endl;
    cout<<"Rezultatas, siunciant kanalu koduojant: ";
    vector<int> bitsWithCode = sendBitsWithCode(textBits);
    string textWithCode = bitsToText(bitsWithCode);
    cout<<textWithCode;
    cout<<endl;
}

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