#ifndef NEWSGROUP_H
#define NEWsGROUP_H

#include <map> //??
#include <string>

class NewsGroup{
public:
	NewsGroup();
	~NewsGroup();

	std::map<Article> list_articles();
	bool create_article(std::string name, std::string author, std::string text); //generate id
	void delete_article(int id); //throws error if no such article exists
	Article get_article(int id); //throws error if no such article exists

private:
	int id;
	std::string name;
	std::map<int, Article> articles;
	int next_free_index; //use time instead?

};

#endif