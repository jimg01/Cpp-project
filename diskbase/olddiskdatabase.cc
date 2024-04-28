#include<iostream>

#include<cstdlib>
#include<filesystem>
#include<fstream>

#include "txthandler.h"

using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::move;
namespace fs = std::filesystem;

void showOptions(){
    cout << endl;
    cout << "(0) Close" << endl;
    cout << "(1) Make dir" << endl;
    cout << "(2) Show database" << endl;
    cout << "(9) Delete database" << endl;
    cout << "Insert input: ";
}

void makeDir(TxTHandler& th){

    std::ofstream str;


    cout << "Insert name of new dir: ";
    string userInput;
    getline(cin, userInput);
    //fs::path currPath = fs::current_path();
    //fs::path basePath = currPath.append("/database");
    fs::path basePath = "database";
    string memoryFile = string(basePath) + "/memory.txt";
    //cout << currPath << endl;
    //cout << basePath << endl;
    if(!fs::exists(basePath)){
        fs::create_directory(basePath);
        th.makeMemory();
    }
    fs::path newDir = basePath.append(userInput);
    //cout << string(newDir) << endl;

    if(!fs::exists(newDir)){
        fs::create_directory(newDir);
        th.addDirectoryToMemory(string(newDir));
        cout << "New Directory created" << endl;
    }else{
        cout << "Directory allready exists" << endl;
    }
            
}

void showDir(TxTHandler& th){
    if(fs::exists("database")){
        int index = th.getIndexInMemory();
        cout << "Id : Directory" << endl;
        for(int i = 0; i < index; i++){
            cout << th.getDirectoryFromIndex(i+1) << endl;
        }
        
        // for(auto entry : fs::recursive_directory_iterator("database")){
        //     cout << n << " : "<< entry.path() << endl;
        //     n++;
        // }
    }else{
        cout << "No database initulaized" << endl;
    }
}

void deleteDatabase(){
    fs::remove_all("database");
    cout << "Database removed" << endl;
}

void makeFile(TxTHandler& th){


    cout << "Insert name of new file: ";
    string nameOfDir;
    getline(cin, nameOfDir);

    cout << "Insert name of new file: ";
    string userInput;
    getline(cin, userInput);
}

int main(){
    bool whileCheck = true;
    int userInput = -1;

    TxTHandler th;

    while(whileCheck){

        showOptions();

        if(cin >> userInput && cin.peek() == '\n'){
            cin.ignore();
            
            switch (userInput) 
            {
                case 0:
                    cout << "Goodbye!" << endl;
                    whileCheck = false;
                    break;
                
                case 1:
                    makeDir(th);
                    break;
                
                case 2:
                    showDir(th);
                    break;
                
                case 3:
                    makeFile(th);
                    break;

                case 4:
                    
                    break;
                
                case 5:
                    
                    break;
                
                case 6:
                    
                    break;
                
                case 7:
                    
                    break;

                case 8:

                    break;
                
                case 9:
                    deleteDatabase();
                    break;
                
                default:
                    cout << "Invalid Input!" << endl;
                    break;
            }
//            cout << "In connected? " << mess.isConnected();
        }else {
            cout << "Invalid Input!" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if(cin.eof()){
            break;
        }

    }
}
