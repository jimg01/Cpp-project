#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>

class Article{
	public:
		Article(int id, std::string name, std::string author, std::string text);
		~Article();

	private:
		//int id;
		std::string name;
		std::string author;
		std::string text;
};

#endif