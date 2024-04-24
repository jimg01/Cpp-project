#ifndef MEMORY_H
#define MEMORY_H

#include<iostream>
#include<fstream>
#include<vector>

using std::string;
using std::endl;
using std::vector;

static string memoryPath = "database/memory.txt";
static std::fstream file;

bool makeMemory(){

    file.open("database/memory.txt");
    file << 0 << "\n";
    file.close();

    return 1;
}

int getIndexInMemory(){
    file.open(memoryPath);
    int n;
    file >> n;
    return n;
}

// void increasIndexInMemory(){
//     int n = getIndexInMemory();
//     file.open(memoryPath);
//     file << ++n << endl;
// }

bool addDirectoryToMemory(string path){
    
    vector<string> lines;
    file.open("database/memory.txt");
    string line;
    int n = 0;

    while(getline(file, line)){
        if(n == 0){
            int index = std::stoi(line);
            line.push_back(++index);
        }else{
            lines.push_back(line);
        }
        n++;
    }

    lines.push_back(n + " " + path);

    for(string line : lines){
        file << line << "\n";
    }
    file.close();

    return true;
}

#endif