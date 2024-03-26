#ifndef DATABASE_INTERFACE_H
#define DATABASE_INTERFACE_H 

#include <string>
#include "Article.h"

class Database_interface {
	public:
	std::vector<std::string> list_NG();
	bool create_NG(std::string name);
	bool delete_NG(int id_NG);
	std::vector<Article> list_articles(int id_NG);
	bool create_article(int id_NG, std::string name, std::string author, std::string text);
	void delete_article(int id_NG, int id_article);
	Article get_article(int id_NG, int id_article);

};


#endif