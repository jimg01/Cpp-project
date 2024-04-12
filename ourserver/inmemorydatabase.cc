#include "inmemorydatabase.h"
#include <iostream>

InMemoryDatabase::InMemoryDatabase(){
	news_groups{};
	next_free_index{0};
}

InMemoryDatabase::~InMemoryDatabase() = default;

std::vector<NewsGroup> InMemoryDatabase::list_NG() override{
	std::vector<NewsGroup> list_of_NG;
	for (auto it = news_groups.begin(); it != news_groups.end(): ++it){
		list_of_NG.pushback((*it).value());
	}
	return list_of_NG;
}

bool InMemoryDatabase::create_NG(std::string name) override{
	news_groups[next_free_index] = NewsGroup(next_free_index, name);
	++next_free_index;
}

bool InMemoryDatabase::delete_NG(int id_NG) override{
	//catch some errors?
	news_groups.erase(id_NG);
}

std::vector<Article> InMemoryDatabase::list_articles(int id_NG) override{
	auto NG = news_groups.at(id_NG);
	std::vector<NewsGroup> list_of_articles;
	for (auto it = NG.articles.begin(); it != NG.articles.end(): ++it){
		list_of_articles.pushback((*it).value());
	}
	return list_of_articles;
}

bool InMemoryDatabase::create_article(int id_NG, std::string name, std::string author, std::string text) override{
	auto NG = news_groups.at(id_NG);
	NG.articles[NG.next_free_index] = Article(next_free_index, name, author, text);
	++NG.next_free_index;

}

void InMemoryDatabase::delete_article(int id_NG, int id_article) override{
	try{
		auto NG = news_groups.at(id_NG);
		try{
			NG.articles.at(id_article); //check for existance
			NG.articles.erase(id_article);
		}
		catch(const std::out_of_range& e){
			//artcie does not exist
			std::cout << "no such article" << std::endl;
		}
	}
	catch(const std::out_of_range& e){
		//News group does not exist
		std::cout << "no such news group" << std::endl;
	}
}

Article InMemoryDatabase::get_article(int id_NG, int id_article) override{
	try{
		auto NG = news_groups.at(id_NG);
		try{
			return NG.articles.at(id_article); 
		}
		catch(const std::out_of_range& e){
			//artcie does not exist
			std::cout << "no such article" << std::endl;
		}
	}
	catch(const std::out_of_range& e){
		//News group does not exist
		std::cout << "no such news group" << std::endl;
	}
}

