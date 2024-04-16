#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>




class Article{

	public:
		Article(int ind);
		Article(int ind, std::string titl, std::string auth, std::string txt);
		//~Article(); 	// not req due to no pointers atm
		std::string to_string();
		
	private:
		std::string title, author, text;
		int id;

	
};

#endif

