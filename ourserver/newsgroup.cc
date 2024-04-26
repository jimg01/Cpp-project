#include "newsgroup.h"
#include "article.h"
#include <vector>
#include <iostream>

NewsGroup::NewsGroup(int& ind, std::string& n){
	id = ind;
	name = n;
	articles = std::map<int, Article>();	
	NG_next_free_index = 1;
	std::cout << "inisitannized a ng" << articles.size() << NG_next_free_index << std::endl;
}

NewsGroup::~NewsGroup(){}

int NewsGroup::get_id() const{
	return id;
}

const std::string& NewsGroup::get_name() const{
	return name;
}

const std::map<int, Article>& NewsGroup::map_of_articles() const{
	//std::cout << "first name aaaaaaaaaaaaaaa " << articles.at(1).get_name() << std::endl << "))";
	return articles;
}

bool NewsGroup::create_article(std::string& title, std::string& author, std::string& text){	
	//std::cout << "start of NG create art" << articles.size() << " : " << NG_next_free_index << std::endl;
	articles.insert(std::make_pair(NG_next_free_index, Article(NG_next_free_index, title, author, text)));
	//std::cout << "first name AAAAAAAAAAAAAAAAAAA " << title << "< title, name >" << articles.at(NG_next_free_index).get_name() << std::endl << "))";
	++(NG_next_free_index);
	//std::cout << "end of NG create art" << articles.size() << " : " << NG_next_free_index << std::endl;
	return true;
}

void NewsGroup::delete_article(int id){ //throws error if no such article exists
	articles.at(id); //for out of range error
	std::cout << "size before erase " << articles.size() << std::endl;
	articles.erase(id);
	std::cout << "size after erase " << articles.size() << std::endl;
} 

const Article NewsGroup::get_article(int id){ //throws error if no such article exists
	auto article = articles.at(id); //for out of range error
	return article;
}

std::string NewsGroup::to_string(){

	return "not implemented";
	/*
	std::string s = "Group Name: " + name + " Id: " + std::to_string(id)
				+ "\nNumber of Articles: " + std::to_string(NG_next_free_index -1);
				
	if(NG_next_free_index != 1){
		s.append("\nArticles:\n");
		for (auto& article : articles){
			Article ab = article.second();
			std::string a = ab.to_string();
			std::string id = std::to_string(article.first());
			s.append(std::to_string(article.first()) + " " + a);
		}
	}
	return s;

	*/
}


