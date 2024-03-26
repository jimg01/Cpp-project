#include "inmemorydatabase.h"

InMemoryDatabase::InMemoryDatabase(){
	//gör mappen
}

std::vector<NewsGroup> InMemoryDatabase::list_NG() override{

}

bool InMemoryDatabase::create_NG(std::string name) override{

}

bool InMemoryDatabase::delete_NG(int id_NG) override{

}

std::vector<Article> InMemoryDatabase::list_articles(int id_NG) override{

}

bool InMemoryDatabase::create_article(int id_NG, std::string name, std::string author, std::string text) override{

}

void InMemoryDatabase::delete_article(int id_NG, int id_article) override{

}

Article InMemoryDatabase::get_article(int id_NG, int id_article) override{

}

