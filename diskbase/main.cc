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
						cout << "\nCreate article:" << endl;
	                	//go into correct newsgroup
	           			string name, author, text;
	           			int id_NG;
	           			cout << "Input newsgroup id " << endl;
	           			cin >> id_NG;
						cout << "Input article name " << endl;
						cin >> name;
						cout << "Input author " << endl;
						cin >> author;
						cout << "Input text " << endl;	//fix so okay with multiline
						cin >> text;	//multiword and line be fixed in server
			
						try{
							database.create_article(id_NG, name, author, text);	
						}catch (std::runtime_error e){
	                		cout << e.what() << endl;
	                	}
	               	
	                    break;
	                    
					 }       
					 
                case 4:
                	{
                		cout << "\nDelete article:" << endl;
                		int id_NG, id_article;
           	     		cout << "Input newsgroup id and article id " << endl;
       	     			cin >> id_NG;
       	     			cin >> id_article;

       	     			try{
                      		database.delete_article(id_NG, id_article);
                   	  	}catch (std::runtime_error e){
	                		cout << e.what() << endl;
	                	}
	              
                    break;
                	}
                case 5:
					{
                		cout << "\nGet article:" << endl;
	                    int id_NG, id_article;
	                    cout << "Input newsgroup id and article id " << endl;
	                    cin >> id_NG;
	                    cin >> id_article;

	                try{
	                	std::vector<std::string> article = database.get_article(id_NG, id_article);
	                	
				    	for(int i = 0; i < 3; i++){
						cout << article.at(i) << endl;
						}
	                }catch (std::runtime_error e){
	                	cout << e.what() << endl;
	                }    			
	                    
                      
                    	break;
               		}
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
