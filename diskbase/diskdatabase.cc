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
	
	//go into correct newsgroup
	string ng = std::to_string(id_NG);
	if(!fs::exists(fs::current_path() / ng)){	//throw instead?
		return false;
		cout << "there is NO newsgroup " << ng << endl;
	}
    fs::current_path(fs::current_path() / ng);

	
    //Get index from NG info-file
	int n = -1;
    std::fstream infoStream;
    infoStream.open(fs::current_path() / infoFile);    
	infoStream >> n;
	infoStream.close();
//	cout << "number of articles: " << n << endl;
	n += 1;

	//make path for article
    const fs::path filePath = fs::current_path();
    const string filename = std::to_string(n) + ".txt";
    if(fs::exists(filePath/filename)){	//will not happen probably
    	cout << "this file id already exists " << filename << endl;
    	return false;	//throw instead?
    }

	//create and write to article
   	std::ofstream{filePath/filename}; // create regular file
	std::ofstream os(filePath/filename);
	os << name << endl;
	os << author << endl;
	os << text << endl;
    os.close();	

    cout << "\nThe follwing file was created: " << endl 
      		<< filePath/filename << endl;    

	//update infoFile in newsgroup
    cout << fs::current_path() << endl;
    infoStream.open(fs::current_path() / infoFile);
    infoStream << std::to_string(n); // standard is overwrite mode
    infoStream.close();

	//exit newsgroup
   	cout << "leaving newsgroup: " << ng << endl;
   	cout << fs::current_path() << endl;
   	fs::current_path(fs::current_path().parent_path());
  	cout << "Currently at \n" << fs::current_path() << endl;
   
	return true;	
}

bool DiskDatabase::delete_article(int id_NG, int id_article){
	string filename;
	string ng = std::to_string(id_NG);
	filename = std::to_string(id_article) + ".txt";	
	
	//check is file exists
	if(!fs::exists(fs::current_path() / ng)){
		cout << "invalid newsgroup id!" << endl;
		return false;	//throw instead?
	} else if(!fs::exists(fs::current_path() / ng / filename) ){ 
		cout << "invalid article id!" << endl;
		return false;	//throw instead?
	}

	//go into corect newsgroup
  	fs::current_path(fs::current_path() / ng);

	//remove article
	cout << "Remove file: \n" << fs::current_path() / filename << endl;
	fs::remove(fs::current_path() / filename);

	//exit newsgroup
	cout << "\nleave newsgroup: " << id_NG << endl;
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

