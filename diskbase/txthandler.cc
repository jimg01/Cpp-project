#include<iostream>
#include<fstream>
#include<vector>

#include"txthandler.h"

using std::string;
using std::endl;
using std::vector;
using std::cout;


bool TxTHandler::makeMemory(){
    //cout << "makeMemory" << endl;
    fileOut.open(memoryPath);
    fileOut << 0 << "\n";
    fileOut.close();

    return 1;
}

int TxTHandler::getIndexInMemory(){
    fileIn.open(memoryPath);
    int n;
    fileIn >> n;
    fileIn.close();
    return n;
}

string TxTHandler::getDirectoryFromIndex(int index){
    fileIn.open(memoryPath);
    string line;
    int n = 0;

    while(getline(fileIn,line)){
        if(n == index){
            fileIn.close();
            return line;
        }
        n++;
    }
    fileIn.close();
    return "-1";
}

// void increasIndexInMemory(){
//     int n = getIndexInMemory();
//     file.open(memoryPath);
//     file << ++n << endl;
// }

bool TxTHandler::addDirectoryToMemory(string path){
    
    vector<string> lines;
    fileIn.open(memoryPath);
    string line;
    int n = 0;

    while(getline(fileIn, line)){
        if(n == 0){
            int index = std::stoi(line);
            index++;
            //cout << line << endl;
            lines.push_back(std::to_string(index));
        }else{
            lines.push_back(line);
        }
        n++;
    }
    fileIn.close();

    lines.push_back(std::to_string(n) + " " + path);

    fileOut.open(memoryPath);
    for(string line : lines){
        fileOut << line << "\n";
    }
    fileOut.close();

    return true;
}