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

	std::vector<std::pair<int, std::string>> list;
	try{
		for (auto const& dir_entry : fs::directory_iterator(std::to_string(id_NG))){
			string id = dir_entry.path().filename();
			id = id.substr(0, id.length()-4);	//remove ".txt"
			
			string name;
			std::ifstream is(dir_entry.path());
			getline(is,name);
			is.close();

			//handle invalid files like "info.txt"
			try{
				std::pair<int, std::string> p(std::stoi(id), name);
				list.push_back(p);	
			} catch (std::invalid_argument e){
				//just skip file
			}
			
				
		}		
	} catch (fs::filesystem_error e){
		throw std::runtime_error("no such newsgroup");
	}

	return list;
	
}


bool DiskDatabase::goto_NG(int id_NG){ // assuming same level as NGs!
	//go into correct newsgroup
	string ng = std::to_string(id_NG);
	
	if(!fs::exists(fs::current_path() / ng)){
		return false;
	}
	
    fs::current_path(fs::current_path() / ng);
    return true;
}

bool DiskDatabase::create_article(int id_NG, std::string name, std::string author, std::string text){
	
	//check and go into correct newsgroup
	if(!goto_NG(id_NG)){
		throw std::runtime_error("no such newsgroup");
	}

	
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
   	fs::current_path(fs::current_path().parent_path());
  	
   
	return true;	
}

bool DiskDatabase::delete_article(int id_NG, int id_article){
	string ng = std::to_string(id_NG);
	string filename = std::to_string(id_article) + ".txt";	
	
	
	//check and go into correct newsgroup
	if(!goto_NG(id_NG)){
		throw std::runtime_error("no such newsgroup");
	}
	
	//check is file exists
	if(!fs::exists(fs::current_path() / filename) ){ 
		throw std::runtime_error("no such newsgroup");
		//cout << "invalid article id!" << endl;
		//return false;	//throw instead?
	}

	//go into corect newsgroup
  	fs::current_path(fs::current_path() / ng);

	//remove article
	cout << "Remove file: \n" << fs::current_path() / filename << endl;
	fs::remove(fs::current_path() / filename);

	//exit newsgroup
   	fs::current_path(fs::current_path().parent_path());
	
	return true;
}

std::vector<std::string> DiskDatabase::get_article(int id_NG, int id_article){
	string ng = std::to_string(id_NG);
	string filename = std::to_string(id_article) + ".txt";	
	
	//check and go into correct newsgroup
	if(!goto_NG(id_NG)){
		throw std::runtime_error("no such newsgroup");
	}
	
	//check if file exists
	 if(!fs::exists(fs::current_path() / filename) ){ 
		throw std::runtime_error("no such article");
	//	cout << "invalid article id!" << endl;
	//	return false;	//throw instead?
	}

	//go into corect newsgroup
  	fs::current_path(fs::current_path() / ng);

	//remove article
	string name, author, line, text;
	text = "";
	cout << "Found file: \n" << fs::current_path() / filename << endl;
	std::ifstream is(fs::current_path() / filename);
	//is.open(fs::current_path() / filename);
	getline(is, name);
	getline(is, author);
	do{
		getline(is, line);	
		cout << "Line \n" << line << endl;
		text.append(line + "\n");
	} while(!is.eof());

	cout << "TEXT \n" << text << endl;
	
	std::vector<std::string> article{name, author, text};

	//exit newsgroup
   	fs::current_path(fs::current_path().parent_path());

	return article;
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

