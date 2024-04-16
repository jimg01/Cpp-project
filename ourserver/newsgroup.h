#ifndef NEWSGROUP_H
#define NEWsGROUP_H

#include <map> //??
#include <string>
#include <vector>
#include "article.h"

class NewsGroup{
public:
	NewsGroup();
	~NewsGroup();

	int get_id() const;
	const std::string& get_name() const;
	const std::map<Article>& map_of_articles() const;
	bool create_article(std::string name, std::string author, std::string text); //generate id
	void delete_article(int id); //throws error if no such article exists
	const Article get_article(int id); //throws error if no such article exists
	
	std::string to_string();
	
private:
	int id;
	int next_free_index;	//change to be time-based instead?
	
	std::string name;
	std::map<int, Article> articles;

};

#endif
