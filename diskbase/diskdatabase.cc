#include "diskdatabase.h"
#include <iostream>
#include <algorithm>
#include<cstdlib>
#include<filesystem>
#include<fstream>

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
	// std::vector<std::pair<int, std::string>> list_of_articles{};
	// try{
	// 	auto NG = news_groups.at(id_NG);
	// 	std::map<int, Article> map_of_articles = NG.map_of_articles();
	// 	//for (const auto& [id, ng] : news_groups)
	// 	for (auto it = map_of_articles.begin(); it != map_of_articles.end(); ++it){
	// 		list_of_articles.push_back(std::make_pair((*it).first, (*it).second.get_name()) );
	// 	}
	// 	std::cout << list_of_articles.size() << map_of_articles.size() << std::endl;
	// }
	// catch(const std::out_of_range& e){
	// 	//News group does not exist
	// 	std::cout << "no such news group" << std::endl;
	// 	throw std::runtime_error("no such NG");
	// }
	// return list_of_articles;
}

bool DiskDatabase::create_article(int id_NG, std::string name, std::string author, std::string text){
	// try{
	// 	auto NG = news_groups.at(id_NG); 
	// 	return NG.create_article(name, author, text);
	// }
	// catch(const std::out_of_range& e){
	// 	//News group does not exist
	// 	std::cout << "no such news group" << std::endl;
	// 	return false;
	// }
}

bool DiskDatabase::delete_article(int id_NG, int id_article){
	// try{
	// 	auto NG = news_groups.at(id_NG);
	// 	try{
	// 		NG.delete_article(id_article);
	// 	}
	// 	catch(const std::out_of_range& e){ //catch error thrown by delete_article in NewsGroup
	// 		//artcie does not exist
	// 		std::cout << "no such article" << std::endl;
	// 		throw std::runtime_error("no such article");
	// 	}
	// }
	// catch(const std::out_of_range& e){
	// 	//News group does not exist
	// 	std::cout << "no such news group" << std::endl;
	// 	throw std::runtime_error("no such NG");
	// }
}

std::vector<std::string> DiskDatabase::get_article(int id_NG, int id_article){

	// try{
	// 	auto NG = news_groups.at(id_NG);
	// 	try{
	// 		Article art = NG.get_article(id_article);
	// 		std::vector<std::string> article{art.get_name(), art.get_author(), art.get_text()};
	// 		return article;
	// 	}
	// 	catch(const std::out_of_range& e){ //catch error thrown by get_article in NewsGroup
	// 		//artcie does not exist
	// 		std::cout << "no such article" << std::endl;
	// 		throw std::runtime_error("no such article");
	// 	}
	// }
	// catch(const std::out_of_range& e){
	// 	//News group does not exist
	// 	std::cout << "no such news group" << std::endl;
	// 	throw std::runtime_error("no such NG");
	// }
}

int DiskDatabase::readSize(){
    std::ifstream fileInput;
    fileInput.open(infoFile);
    int size;
    fileInput >> size;
    fileInput.close();
    return size;
}

std::string DiskDatabase::readName(){
    std::ifstream fileInput;
    fileInput.open(infoFile);
    string name;
    getline(fileInput,name);
    getline(fileInput,name);
    fileInput.close();
    return name;
}