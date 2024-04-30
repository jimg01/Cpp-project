#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>




class Article{

	public:
		//Article(int ind);
		Article(int ind, std::string& titl, std::string& auth, std::string& txt);
		//~Article(); 	// not req due to no pointers atm
		std::string to_string();
		const std::string& get_name() const;
		const std::string& get_author() const;
		const std::string& get_text() const;
		
	private:
		std::string title;
		std::string author;
		std::string text;
		int id;

	
};

#endif

