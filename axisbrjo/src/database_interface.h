#ifndef DATABASE_INTERFACE_H
#define DATABASE_INTERFACE_H 

#include <string>
#include <vector>

class Database_interface {
public:
	virtual std::vector<std::pair<int, std::string>> list_NG() = 0; //retun map insted? no
	virtual bool create_NG(std::string name) = 0;
	virtual bool delete_NG(int id_NG) = 0;
	virtual std::vector<std::pair<int, std::string>> list_articles(int id_NG) noexcept(false) = 0; //Throws runtime error //return map instead? no 
	virtual bool create_article(int id_NG, std::string& name, std::string& author, std::string& text) = 0; 
	virtual void delete_article(int id_NG, int id_article) = 0;
	virtual std::vector<std::string> get_article(int id_NG, int id_article) = 0;
};


#endif