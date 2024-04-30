#include "diskdatabase.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <exception>

using std::endl;
using std::cout;
using std::cin;
using std::string;
namespace fs = std::filesystem;

DiskDatabase::DiskDatabase(){

    fs::path basePath = databaseDirectory;
    std::ofstream fileOutput;

    if(!fs::exists(basePath)){
        fs::create_directory(basePath);
    }
    fs::path currPath = fs::current_path() / basePath;
    fs::current_path(currPath);
    if(!fs::exists(infoFile)){
        fileOutput.open(infoFile);
        fileOutput << 0 << "\n";
        fileOutput.close();
    }
}

DiskDatabase::~DiskDatabase(){
    fs::current_path(fs::current_path().parent_path());
}

std::vector<std::pair<int, std::string>> DiskDatabase::list_NG(){
	std::vector<std::pair<int, std::string>> listOfNG;

    for(auto entry : fs::directory_iterator(fs::current_path())){
        if(entry.is_directory()){
            fs::current_path(entry.path());
            int NGId = std::stoi(entry.path().filename());
            string NGName = readName();
            listOfNG.push_back(std::make_pair(NGId,NGName));
            fs::current_path(fs::current_path().parent_path());
        }
    }
	std::sort(listOfNG.begin(), listOfNG.end(), [](std::pair<int, std::string> p1, std::pair<int, std::string> p2){return p1.first < p2.first;});
    return listOfNG;
}

bool DiskDatabase::create_NG(std::string name){
    
    std::ofstream fileOutput;
    for(auto entry : fs::directory_iterator(fs::current_path())){
        if(entry.is_directory()){
            fs::current_path(entry.path());
            string testName = readName();
            fs::current_path(fs::current_path().parent_path());
            if(testName.compare(name) == 0){
                return false;
            }
        }
    }
    
    int newNewsGroupId = readSize() + 1;
    fs::create_directory(std::to_string(newNewsGroupId));
    fs::current_path(std::to_string(newNewsGroupId));

    fileOutput.open(infoFile);
    fileOutput << 0 << "\n";
    fileOutput << name << "\n";
    fileOutput.close();
    fs::current_path(fs::current_path().parent_path());

    int dbSize = readSize();
    fileOutput.open(infoFile);
    fileOutput << ++dbSize << "\n";
    fileOutput.close();

    return true;
}

bool DiskDatabase::delete_NG(int id_NG){
    for(auto entry : fs::directory_iterator(fs::current_path())){
        if(entry.path().filename().compare(std::to_string(id_NG)) == 0){
            fs::remove_all(fs::path(std::to_string(id_NG)));
            return true;
        }
    }
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
			} catch (std::invalid_argument& e){
				//just skip file
			}
		}		
	} catch (fs::filesystem_error& e){
		throw std::runtime_error("no such newsgroup");
	}

	std::sort(list.begin(), list.end(), [](std::pair<int, std::string> p1, std::pair<int, std::string> p2){return p1.first < p2.first;});
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

bool DiskDatabase::create_article(int id_NG, std::string& name, std::string& author, std::string& text){
	
	//check and go into correct newsgroup
	if(!goto_NG(id_NG)){
		throw std::runtime_error("no such newsgroup");
	}

	
    //Get index from NG info-file
	int n = readSize();

	//make path for article
    const fs::path filePath = fs::current_path();
    const string filename = std::to_string(++n) + ".txt";
    
    if(fs::exists(filePath/filename)){	//will not happen probably
    	throw std::runtime_error("this article already exist");
    }

	//create and write to article
   	std::ofstream{filePath/filename}; // create regular file
	std::ofstream os(filePath/filename);
	os << name << endl;
	os << author << endl;
	os << text;
    os.close();	

	//update infoFile in newsgroup
    std::fstream infoStream(fs::current_path() / infoFile);
    infoStream << std::to_string(n); // standard is overwrite mode
    infoStream.close();

	//exit newsgroup
   	fs::current_path(fs::current_path().parent_path());
  	
	return true;	
}

void DiskDatabase::delete_article(int id_NG, int id_article){ // make void?
	string ng = std::to_string(id_NG);
	string filename = std::to_string(id_article) + ".txt";	
	
	
	//check and go into correct newsgroup
	if(!goto_NG(id_NG)){
		throw std::runtime_error("no such newsgroup");
	}
	
	//check is file exists
	if(!fs::exists(fs::current_path() / filename) ){ 
		throw std::runtime_error("no such newsgroup");
	}

	//remove article
	cout << "Remove file: \n" << fs::current_path() / filename << endl;
	fs::remove(fs::current_path() / filename);

	//exit newsgroup
   	fs::current_path(fs::current_path().parent_path());
	
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
	}

	//remove article
	string name, author, line, text;
	text = "";
	
	std::ifstream is(fs::current_path() / filename);
	getline(is, name);
	getline(is, author);
	
	getline(is, line);	
	text.append(line);
	while(!is.eof()){
		getline(is, line);	
		text.append("\n" + line);	
	}
		
	/*
	do{
		getline(is, line);	
		text.append("\n" + line);
		
	} while(!is.eof());
	*/
	std::vector<std::string> article{name, author, text};

	//exit newsgroup
   	fs::current_path(fs::current_path().parent_path());

	return article;

}


int DiskDatabase::readSize(){
    std::ifstream fileInput(infoFile);
    int size;
    fileInput >> size;
    fileInput.close();
    
    return size;
}

std::string DiskDatabase::readName(){
    std::ifstream fileInput(infoFile);
    string name;
    getline(fileInput,name);
    getline(fileInput,name);
    fileInput.close();
    
    return name;
}
