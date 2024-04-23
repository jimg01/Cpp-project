#ifndef INMEMORYDATABASE_H
#define INMEMORYDATABASE_H

#include "database_interface.h"
#include "newsgroup.h"
#include "article.h"
#include <map>

class InMemoryDatabase : public Database_interface{
public:
	InMemoryDatabase();
	~InMemoryDatabase();
	//behövs detta?
	std::vector<std::pair<int, std::string>> list_NG() override;
	bool create_NG(std::string name) override;
	bool delete_NG(int id_NG) override;
	std::vector<std::pair<int, std::string>> list_articles(int id_NG) override; //Throws runtime error
	bool create_article(int id_NG, std::string name, std::string author, std::string text) override;
	void delete_article(int id_NG, int id_article) override;
	std::vector<std::string> get_article(int id_NG, int id_article) override;
private:
	std::map<int, NewsGroup> news_groups;
	int next_free_index;
};

#endif