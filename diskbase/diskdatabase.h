#ifndef DISKDATABASE_H
#define DISKDATABASE_H

#include "database_interface.h"
#include <map>

class DiskDatabase : public Database_interface{
public:
	DiskDatabase();
	~DiskDatabase();
	//behövs detta?
	virtual std::vector<std::pair<int, std::string>> list_NG() override;
	virtual bool create_NG(std::string name) override;
	virtual bool delete_NG(int id_NG) override;
	virtual std::vector<std::pair<int, std::string>> list_articles(int id_NG) override;//noexcept(false) ; //Throws runtime error
	virtual bool create_article(int id_NG, std::string name, std::string author, std::string text) override;
	virtual void delete_article(int id_NG, int id_article) override;
	virtual std::vector<std::string> get_article(int id_NG, int id_article) override;

	const std::string infoFile = "info.txt";
private:
	//std::map<int, NewsGroup> news_groups;
	
};

#endif
