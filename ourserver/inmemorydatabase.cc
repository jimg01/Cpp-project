#include "inmemorydatabase.h"
#include <iostream>
#include <algorithm>

InMemoryDatabase::InMemoryDatabase(){
	news_groups{};
	next_free_index{0};
}

InMemoryDatabase::~InMemoryDatabase() = default;

std::vector<std::pair<int, std::string>> InMemoryDatabase::list_NG(){
	std::vector<std::pair<int, std::string>> list_of_NG;
	for (auto it = news_groups.begin(); it != news_groups.end(): ++it){
		list_of_NG.pushback(std::make_pair((*it), (*it).value().get_name()) );
	}
	return list_of_NG;
}

bool InMemoryDatabase::create_NG(std::string name){
	auto it = std::find_if(news_groups.begin(), news_groups.end(), [&name](const auto& pair){return name == pair.second.name});
	if (it != news_groups.end()){
		return false;
	} else{
		news_groups[next_free_index] = NewsGroup(next_free_index, name);
		++next_free_index;
		return true;
	}
}

bool InMemoryDatabase::delete_NG(int id_NG){
	try{
		news_groups.at(id_NG); //throws out_of_range error
		news_groups.erase(id_NG);
		return true;
	}
	catch(const std::out_of_range& e){
		//News group does not exist
		std::cout << "no such news group" << std::endl;
		return false;
	}
	
}

std::vector<std::pair<int, std::string>> InMemoryDatabase::list_articles(int id_NG){
	std::vector<std::pair<int, std::string>> list_of_articles{};
	try{
		auto NG = news_groups.at(id_NG);
		std::map<int, std::pair<int, std::string>> map_of_articles = NG.map_of_articles();
		for (auto it = map_of_articles.begin(); it != map_of_articles.end(): ++it){
			list_of_articles.pushback(std::make_pair((*it), (*it).value().get_name()) );
		}
	}
	catch(const std::out_of_range& e){
		//News group does not exist
		std::cout << "no such news group" << std::endl;
		throw std::runtime_error("no such news group");
	}
	return list_of_articles;
}

bool InMemoryDatabase::create_article(int id_NG, std::string name, std::string author, std::string text){
	try{
		auto NG = news_groups.at(id_NG); 
		return NG.create_article(name, author, text);
	}
	catch(const std::out_of_range& e){
		//News group does not exist
		std::cout << "no such news group" << std::endl;
		return false;
	}
}

void InMemoryDatabase::delete_article(int id_NG, int id_article){
	try{
		auto NG = news_groups.at(id_NG);
		try{
			NG.delete_article(id_article);
		}
		catch(const std::out_of_range& e){ //catch error thrown by delete_article in NewsGroup
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
}

std::vector<std::string> InMemoryDatabase::get_article(int id_NG, int id_article){
	try{
		auto NG = news_groups.at(id_NG);
		try{
			Article art = NG.get_article(id_article);
			return std::vector<std::string> article{art.get_name(), art.get_author(), art.get_text()}
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
}

