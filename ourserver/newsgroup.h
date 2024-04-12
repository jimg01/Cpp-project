#ifndef NEWSGROUP_H
#define NEWsGROUP_H

#include <map> //??
#include <string>

class NewsGroup{
public:

private:
	int id;
	std::string name;
	std::map<int, Article> articles;
	int next_free_index;

};

#endif