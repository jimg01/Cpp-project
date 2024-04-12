#ifndef NEWSGROUP_H
#define NEWsGROUP_H

#include <map> //??
#include <string>

class NewsGroup{
public:
	NewsGroup(int ind, std::string n);
	~NewsGroup();

	int getId();
	string:: getName();
	std::map<int, Article> getArticles();
	void print();
	
private:
	int id;
	int next_free_index;
	
	std::string name;
	std::map<int, Article> articles;

};

#endif
