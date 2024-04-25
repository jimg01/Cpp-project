#include<iostream>

#include<cstdlib>
#include<filesystem>
#include<fstream>

#include"diskdatabase.h"
#include"database_interface.h"

using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::move;
namespace fs = std::filesystem;

void showNewsGroups(DiskDatabase& ddb){
    std::vector<std::pair<int, std::string>> listOfNG = ddb.list_NG();
    if(listOfNG.size() != 0){
        cout << "Id : Directory" << endl;
        for(std::pair<int, std::string> entry : listOfNG){
            cout << entry.first << " : " << entry.second << endl;
        }
    }else{
        cout << "No NewsGroups exists" << endl;
    }
}

void createNewsGroup(DiskDatabase& ddb){

    std::ofstream str;


    cout << "Insert name of new NewsGroup: ";
    string userInput;
    getline(cin, userInput);

    if(ddb.create_NG(userInput)){
        cout << "New NewsGroup was created" << endl;
    }else{
        cout << "Newsgroup already exists" << endl;
    }       
}

void deleteNewsGroup(DiskDatabase& ddb){

    cout << "Enter Id of the NewsGroup you want to delete: ";
    int idOfNewsGroup;
    if(cin >> idOfNewsGroup && cin.peek() == '\n'){
        cin.ignore();

        if(ddb.delete_NG(idOfNewsGroup)){
            cout << "NewsGroup was deleted" << endl;
        }else{
            cout << "No NewsGroup with that Id" << endl;
        }
        
    }else{
        cout << "Invalid Input!" << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// void makeFile(){


//     cout << "Insert name of new file: ";
//     string nameOfDir;
//     getline(cin, nameOfDir);

//     cout << "Insert name of new file: ";
//     string userInput;
//     getline(cin, userInput);
// }

// void createArticle(TxTHandler& th){
// 	//string basePath = fs::current_path() + "/testdirs";	//go down to correct
// 	string ng = "fakeNG";
// 	cout << "enter newsgroup: " << ng << endl;
// 	fs::current_path(basePath / ng);
// 	cout << "Currently at \n" << fs::current_path() << endl;

// 	/*
//     cout << "Insert name of new file: ";
//     string nameOfDir;
//     getline(cin, nameOfDir);
// 	*/
	
//     cout << "Insert name of new file: ";
//     string userInput;
//     getline(cin, userInput);
//     std::fstream fstream;

//     //creation of file
//     const fs::path filePath = fs::current_path();
//     const string filename = userInput + ".txt";
//     std::ofstream{filePath/filename}; // create regular file
    
//     cout << "\nThe follwing file was created: " << endl 
//     		<< filePath/filename << endl;    

// 	cout << "leave newsgroup: " << ng << endl;
// 	cout << fs::current_path() << endl;
// 	fs::current_path(fs::current_path().parent_path());
// 	cout << "Currently at \n" << fs::current_path() << endl;
// }

// void deleteArticle(TxTHandler& th){

// 	string ng = "fakeNG";
// 	cout << "\nenter newsgroup: " << ng << endl;
// 	fs::current_path(basePath / ng);
// 	cout << "Currently at \n" << fs::current_path() << endl;

// 	string filename;
	
// 	do{
// 		cout << "Insert name of to be deleted article: " << endl;
// 	    getline(cin, filename);
// 		filename = filename + ".txt";	

// 		cout << "Checks file: \n" << fs::current_path() / filename << endl;
// 		if(fs::exists(fs::current_path() / filename)){
// 			cout << "file exists!" << endl;	
// 			cout << "Delete? (y/n) " << endl;
// 			char opt;
// 			cin >> opt;
// 			if(opt == 'y'){
// 				fs::remove(fs::current_path() / filename);
// 				cout << "\nfile was removed!" << endl;	
// 				break;	
// 			} else {
// 				cout << "\nNO file was removed!" << endl;		
// 			}
			
// 		} else{
// 			cout << "file does NOT exist!" << endl;		
// 		}
// 	} while (!fs::exists(fs::current_path() / filename));

    
// 	cout << "\nleave newsgroup: " << ng << endl;
// 	//cout << fs::current_path() << endl;
// 	fs::current_path(fs::current_path().parent_path());
// 	cout << "Currently at \n" << fs::current_path() << endl;
	
	
// 	/*
//     cout << "Insert name of new file: ";
//     string userInput;
//     getline(cin, userInput);
//     std::fstream fstream;
//     string filePath = fs::current_path().string() + "/" +  userInput + ".txt";

// 	string command = "touch " + filePath;
//     std::system(command.c_str());
//     */
// }

bool makeDesition(int n, DiskDatabase& ddb){
    switch (n) 
    {
        
        case 1:
            showNewsGroups(ddb);
            break;
        
        case 2:
            createNewsGroup(ddb);
            break;
        
        case 3:
            deleteNewsGroup(ddb);
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
            cout << "Goodbye!" << endl;
            return false;
        
        default:
            cout << "Invalid Input!" << endl;
            break;
    }
    return true;
}

void showOptions(){
    cout << endl;
    cout << "Choose an option:\n";
    cout << "(1) List NewsGroups\n";
    cout << "(2) Create a NewsGroup\n";
    cout << "(3) Delete a NewsGroup\n";
    cout << "(4) List Articles in a NewsGroups\n";
    cout << "(5) Create an Article\n";
    cout << "(6) Delete an Article\n";
    cout << "(7) Show an Article\n";
    cout << "(8) Terminat Client\n";
    cout << "Insert number: ";
}

int main(){
    bool whileCheck = true;
    int userInput = -1;

    DiskDatabase ddb;

    while(whileCheck){

        showOptions();

        if(cin >> userInput && cin.peek() == '\n'){
            cin.ignore();
            whileCheck = makeDesition(userInput, ddb);
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
