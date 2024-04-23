#ifndef DATABASE_INTERFACE_H
#define DATABASE_INTERFACE_H 

#include <string>
#include "article.h"
#include "newsgroup.h"

class Database_interface {
public:
	virtual std::vector<std::pair<int, std::string>> list_NG(); //retun map insted? no
	virtual bool create_NG(std::string name);
	virtual bool delete_NG(int id_NG);
	virtual std::vector<std::pair<int, std::string>> list_articles(int id_NG) noexcept(false); //Throws runtime error //return map instead? no 
	virtual bool create_article(int id_NG, std::string name, std::string author, std::string text); 
	virtual void delete_article(int id_NG, int id_article);
	virtual std::vector<std::string> get_article(int id_NG, int id_article);

};


#endif