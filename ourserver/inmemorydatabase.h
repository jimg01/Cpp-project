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
	virtual std::vector<std::pair<int, std::string>> list_NG() override;
	virtual bool create_NG(std::string name) override;
	virtual bool delete_NG(int id_NG) override;
	virtual std::vector<std::pair<int, std::string>> list_articles(int id_NG) override;//noexcept(false) ; //Throws runtime error
	virtual bool create_article(int id_NG, std::string name, std::string author, std::string text) override;
	virtual void delete_article(int id_NG, int id_article) override;
	virtual std::vector<std::string> get_article(int id_NG, int id_article) override;
private:
	std::map<int, NewsGroup> news_groups;
	int next_free_index;
};

#endif