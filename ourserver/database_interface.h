#ifndef DATABASE_INTERFACE_H
#define DATABASE_INTERFACE_H 

#include <string>
#include "article.h"
#include "newsgroup.h"

class Database_interface {
public:
	virtual std::vector<NewsGroup> list_NG(); //retun map insted?
	virtual bool create_NG(std::string name);
	virtual bool delete_NG(int id_NG);
	virtual std::vector<Article> list_articles(int id_NG);
	virtual bool create_article(int id_NG, std::string name, std::string author, std::string text); //return map insted?
	virtual void delete_article(int id_NG, int id_article);
	virtual Article get_article(int id_NG, int id_article);

};


#endif