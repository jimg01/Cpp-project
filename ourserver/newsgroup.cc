#include "newsgroup.h"
#include "article.h"
#include <vector>

NewsGroup::NewsGroup(int ind, std::string n){
	id = ind;
	name = n;
	std::map<int, Article> articles;	
	next_free_index = 1;
}

NewsGroup::~NewsGroup(){}

int NewsGroup::get_id(){
	return id;
}

std::string NewsGroup::get_name(){
	return name;
}

std::map<int, Article> NewsGroup::map_of_articles(){
	return articles;	
}

bool NewsGroup::create_article(std::string title, std::string author, std::string text){
		Article a(next_free_index, title, author, text);
		next_free_index++;
		return true;
}



std::string NewsGroup::to_string(){

	return "not implemented";
	/*
	std::string s = "Group Name: " + name + " Id: " + std::to_string(id)
				+ "\nNumber of Articles: " + std::to_string(next_free_index -1);
				
	if(next_free_index != 1){
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


