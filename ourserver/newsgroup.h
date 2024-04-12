#ifndef NEWSGROUP_H
#define NEWsGROUP_H

#include <map> //??
#include <string>
#include <vector>
#include "article.h"

class NewsGroup{
public:
	NewsGroup(int ind, std::string n);
	~NewsGroup();

	int getId();
	std::string getName();
	std::map<int, Article> NewsGroup::map_of_articles();
	bool create_article(std::string name, std::string author, std::string text);
	void print();
	bool create_article();
	
private:
	int id;
	int next_free_index;	//change to be time-based instead?
	
	std::string name;
	std::map<int, Article> articles;

};

#endif
