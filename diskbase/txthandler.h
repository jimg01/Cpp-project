#ifndef TXTHANDLER_H
#define TXTHANDLER_H

#include<iostream>
#include<fstream>
#include<vector>

using std::string;
using std::endl;
using std::vector;
using std::cout;

static string memoryPath = "database/memory.txt";
static std::ofstream fileOut;
static std::ifstream fileIn;

class TxTHandler{
    public:

    TxTHandler() = default;
    void setIndex(int i){dirSize = i;};
    bool makeMemory();

    int getIndexInMemory();

    string getDirectoryFromIndex(int index);

    bool addDirectoryToMemory(string path);

    private:
    int dirSize;
    vector<string,string> dirVecor;
    

};
#endif