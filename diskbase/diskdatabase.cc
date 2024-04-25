#include "diskdatabase.h"
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <exception>

using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
namespace fs = std::filesystem;

const fs::path basePath = fs::current_path() / "testdirs";	

DiskDatabase::DiskDatabase(){
}

DiskDatabase::~DiskDatabase() = default;

std::vector<std::pair<int, std::string>> DiskDatabase::list_NG(){
	
}

bool DiskDatabase::create_NG(std::string name){
	return false;
}

bool DiskDatabase::delete_NG(int id_NG){
	
	return false;
}

std::vector<std::pair<int, std::string>> DiskDatabase::list_articles(int id_NG){
	
}

bool DiskDatabase::create_article(int id_NG, std::string name, std::string author, std::string text){
    //creation of file

    std::fstream infoStream;
    infoStream.open(fs::current_path() / database.infoFile);
    
	int n = -1;
	infoStream >> n;
	infoStream.close();
	cout << "number of articles: " << n << endl;
	n += 1;
	
    const fs::path filePath = fs::current_path();
    const string filename = std::to_string(id_NG) + ".txt";
    if(fs::exists(filePath/filename)){	//will not happen probably
    	return false;
    }
   
    cout << "\nThe follwing file was created: " << endl 
  		<< filePath/filename << endl;    

   	std::ofstream{filePath/filename}; // create regular file
   		
	std::ofstream os(filePath/filename);
	os << name << endl;
	os << author << endl;
	os << text << endl;
    os.close();	
   
	return true;	
}

bool DiskDatabase::delete_article(int id_NG, int id_article){
	string filename;
	string ng = std::to_string(id_NG);
	
	//go into correct newsgroup!
	if(!fs::exists(fs::current_path() / ng) || 
		!fs::exists(fs::current_path() / ng / to_string(id_article)) ){ // or should throw?
		return false;
	}
 	
  	fs::current_path(fs::current_path() / ng);
	
	filename = std::to_string(id_article) + ".txt";	

	cout << "Checks file: \n" << fs::current_path() / filename << endl;
/*
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
*/
	fs::remove(fs::current_path() / filename);
	cout << "\nleave newsgroup: " << id_NG << endl;
	//cout << fs::current_path() << endl;
	fs::current_path(fs::current_path().parent_path());
	cout << "Currently at \n" << fs::current_path() << endl;
	
	return true;
}

std::vector<std::string> DiskDatabase::get_article(int id_NG, int id_article){

/*
	try{
		auto NG = news_groups.at(id_NG);
		try{
			Article art = NG.get_article(id_article);
			std::vector<std::string> article{art.get_name(), art.get_author(), art.get_text()};
			return article;
		}
		catch(const std::out_of_range& e){ //catch error thrown by get_article in NewsGroup
			//artcie does not exist
			std::cout << "no such article" << std::endl;
			throw std::runtime_error("no such article");
		}
	}
	catch(const std::out_of_range& e){
		//News group does not exist
		std::cout << "no such news group" << std::endl;
		throw std::runtime_error("no such NG");
	}

	*/
}

