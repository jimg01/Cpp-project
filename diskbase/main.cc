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

void listArticles(DiskDatabase& ddb){
	cout << "\nList articles:" << endl;  	
	int id_NG;
    cout << "Input newsgroup id " << endl;
    cin >> id_NG;

    try{
	   	std::vector<std::pair<int, std::string>> articles = ddb.list_articles(id_NG);

       	cout << "\nPRINTING " << endl;	
	   	for(long unsigned int i = 0; i < articles.size(); i++){
			cout << articles.at(i).first << " " 
				<< articles.at(i).second << endl;
		}

  	}catch (std::runtime_error e){
   		cout << e.what() << endl;
	}
}

void createArticle(DiskDatabase& ddb){
	cout << "\nCreate article:" << endl;
	
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
		ddb.create_article(id_NG, name, author, text);	
		
	}catch (std::runtime_error e){
   		cout << e.what() << endl;
   	}
 
}

void deleteArticle(DiskDatabase& ddb){
	cout << "\nDelete article:" << endl;

	int id_NG, id_article;
	cout << "Input newsgroup id and article id " << endl;
	cin >> id_NG;
	cin >> id_article;

	try{
   		ddb.delete_article(id_NG, id_article);
   		
  	}catch (std::runtime_error e){
		cout << e.what() << endl;
	}
 
}


void getArticle(DiskDatabase& ddb){
	cout << "\nGet article:" << endl;
    int id_NG, id_article;
    cout << "Input newsgroup id and article id " << endl;
    cin >> id_NG;
    cin >> id_article;

    try{
      	std::vector<std::string> article = ddb.get_article(id_NG, id_article);
      	
		for(int i = 0; i < 3; i++){
			cout << article.at(i) << endl;
		}
		
     } catch (std::runtime_error e){
      	cout << e.what() << endl;
     }    			

}


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
            listArticles(ddb);
            break;
        
        case 5:
            createArticle(ddb);
            break;
        
        case 6:
            deleteArticle(ddb);
            break;
        
        case 7:
            getArticle(ddb);
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
