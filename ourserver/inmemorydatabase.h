#ifndef INMEMORYDATABASE_H
#define INMEMORYDATABASE_H

#include "database_interface.h"
#include "article.h"
#include "newsgroup.h"
#include <map>

class InMemoryDatabase : public Database_interface{
public:
	InMemoryDatabase();
	~InMemoryDatabase();
	//behövs detta?
	std::vector<NewsGroup> list_NG();
	bool create_NG(std::string name);
	bool delete_NG(int id_NG);
	std::vector<Article> list_articles(int id_NG);
	bool create_article(int id_NG, std::string name, std::string author, std::string text);
	void delete_article(int id_NG, int id_article);
	Article get_article(int id_NG, int id_article);
private:
	std::map<int, NewsGroup> news_groups;
	int next_free_index;
};

#endif