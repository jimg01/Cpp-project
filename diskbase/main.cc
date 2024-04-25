#include<iostream>

#include<cstdlib>
#include<filesystem>
#include<fstream>

#include "diskdatabase.h"

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

void makeDir(){

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
 //       th.makeMemory();
    }
    fs::path newDir = basePath.append(userInput);
    //cout << string(newDir) << endl;

    if(!fs::exists(newDir)){
        fs::create_directory(newDir);
   //     th.addDirectoryToMemory(string(newDir));
        cout << "New Directory created" << endl;
    }else{
        cout << "Directory allready exists" << endl;
    }
            
}



int main(){
    bool whileCheck = true;
    int userInput = -1;

    DiskDatabase database;
    fs::current_path(fs::current_path() / "testdirs");

    while(whileCheck){

        showOptions();

        if(cin >> userInput && cin.peek() == '\n'){
            cin.ignore();
            
            switch (userInput) 
            {
                case 0:
                	{
                    cout << "\nGoodbye!" << endl;
                    whileCheck = false;
                    break;
                	}
                case 1:
                    //makeDir(th);
                    break;
                
                case 2:
                    //showDir(th);
                    break;
                
                case 3:
					{
                	//go into correct newsgroup
           			string name, author, text;
           			int id_NG;
           			cout << "Input newsgroup id " << endl;
					cout << "Input article name " << endl;
					cin >> name;
					cout << "Input author " << endl;
					cin >> author;
					cout << "Input text " << endl;	//fix so okay with multiline
					cin >> text;
			
                	string ng = std::to_string(id_NG);
                	fs::current_path(fs::current_path() / ng);
                	

                	if(database.create_article(n, name, author, text)){
                		cout << "Article was created!" << endl;
                		cout << fs::current_path() << endl;
                		infoStream.open(fs::current_path() / database.infoFile);
                		infoStream << std::to_string(n);
                		infoStream.close();
                	} else{
                		cout << "Article was NOT created!" << endl;
                	}

               		cout << "leaving newsgroup: " << ng << endl;
					cout << fs::current_path() << endl;
					fs::current_path(fs::current_path().parent_path());
					cout << "Currently at \n" << fs::current_path() << endl;

                    break;
					 }       
					 
                case 4:
                		int id_NG, id_article;
           	     		cout << "Input newsgroup id and article id " << endl;
       	     			cin >> id_NG;
       	     			cin >> id_article;
       	     			
                      database.delete_article(id_NG, id_article);
                    break;
                
                case 5:
                      //makeDir(th);
                    break;
                
                case 6:
                      //makeDir(th);
                    break;
                
                case 7:
                      //makeDir(th);
                    break;

                case 8:
						  //makeDir(th);
                    break;
                
                case 9:
       //             deleteDatabase();
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
