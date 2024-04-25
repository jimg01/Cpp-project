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

//set default basePath - assuming make in database directory
const fs::path basePath = fs::current_path() / "testdirs";	

void showOptions(){
    cout << endl;
    cout << "(0) Close" << endl;
    cout << "(1) Make dir" << endl;
    cout << "(2) Show database" << endl;
    cout << "(9) Delete database" << endl;
    cout << "(4) Create Article" << endl;
    cout << "(5) Print Article" << endl;
    cout << "(6) Delete Article" << endl;
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

	/*
    cout << "Insert name of new file: ";
    string nameOfDir;
    getline(cin, nameOfDir);
	*/
	
    cout << "Insert name of new file: ";
    string userInput;
    getline(cin, userInput);
}

void createArticle(TxTHandler& th){
	//string basePath = fs::current_path() + "/testdirs";	//go down to correct
	string ng = "fakeNG";
	cout << "enter newsgroup: " << ng << endl;
	fs::current_path(basePath / ng);
	cout << "Currently at \n" << fs::current_path() << endl;

	/*
    cout << "Insert name of new file: ";
    string nameOfDir;
    getline(cin, nameOfDir);
	*/
	
    cout << "Insert name of new file: ";
    string userInput;
    getline(cin, userInput);
    std::fstream fstream;

    //creation of file
    const fs::path filePath = fs::current_path();
    const string filename = userInput + ".txt";
    std::ofstream{filePath/filename}; // create regular file
    
    cout << "\nThe follwing file was created: " << endl 
    		<< filePath/filename << endl;    

	cout << "leave newsgroup: " << ng << endl;
	cout << fs::current_path() << endl;
	fs::current_path(fs::current_path().parent_path());
	cout << "Currently at \n" << fs::current_path() << endl;
}


void deleteArticle(TxTHandler& th){

	string ng = "fakeNG";
	cout << "\nenter newsgroup: " << ng << endl;
	fs::current_path(basePath / ng);
	cout << "Currently at \n" << fs::current_path() << endl;

	string filename;
	
	do{
		cout << "Insert name of to be deleted article: " << endl;
	    getline(cin, filename);
		filename = filename + ".txt";	

		cout << "Checks file: \n" << fs::current_path() / filename << endl;
		if(fs::exists(fs::current_path() / filename)){
			cout << "file exists!" << endl;	
			cout << "Delete? (y/n) " << endl;
			char opt;
			cin >> opt;
			if(opt == 'y'){
				fs::remove(fs::current_path() / filename);
				cout << "\nfile was removed!" << endl;	
				break;	
			} else {
				cout << "\nNO file was removed!" << endl;		
			}
			
		} else{
			cout << "file does NOT exist!" << endl;		
		}
	} while (!fs::exists(fs::current_path() / filename));

    
	cout << "\nleave newsgroup: " << ng << endl;
	//cout << fs::current_path() << endl;
	fs::current_path(fs::current_path().parent_path());
	cout << "Currently at \n" << fs::current_path() << endl;
	
	
	/*
    cout << "Insert name of new file: ";
    string userInput;
    getline(cin, userInput);
    std::fstream fstream;
    string filePath = fs::current_path().string() + "/" +  userInput + ".txt";

	string command = "touch " + filePath;
    std::system(command.c_str());
    */
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
                    //create article
                    createArticle(th);
                    break;
                
                case 5:
                    //print article
                    break;
                
                case 6:
                    //delete article
                    deleteArticle(th);
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
