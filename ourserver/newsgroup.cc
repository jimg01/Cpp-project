#include "newsgroup.h"
#include <vector>

NewsGroup::NewsGroup(int ind, std::string n){
	id = ind;
	name = n;
	std::map<int, Article> articles;	
	next_free_index = 1;
}

NewsGroup::~NewsGroup(){}

int NewsGroup::getId(){
	return id;
}

std::string NewsGroup::getName(){
	return name;
}

std::map<int, Article> NewsGroup::map_of_articles(){
	return articles;	
}

bool create_article(std::string title, std::string author, std::string text){
		Article a(next_free_index, );
		next_free_index++;
}


void NewsGroup::print(){}
	

