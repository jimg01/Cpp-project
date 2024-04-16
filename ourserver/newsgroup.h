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

	int get_id();
	std::string get_name();
	std::map<int, Article> map_of_articles();
	bool create_article(std::string name, std::string author, std::string text);
	std::string to_string();
	bool create_article();
	
private:
	int id;
	int next_free_index;	//change to be time-based instead?
	
	std::string name;
	std::map<int, Article> articles;

};

#endif
