#include <string>
#include "article.h"
#include <iostream>


/*
Article::Article(int ind){
	std::string title("");
	std::string author("");
	std::string text("");
	int id = ind;
	
}
*/

//Article::Article(int ind): id(ind), title(""), author(""), text("") {}
Article::Article(int ind, std::string& titl, std::string& auth, std::string& txt): id(ind), title(titl), author(auth), text(txt) {}

/*
Article::Article(int ind, std::string& titl, std::string& auth, std::string& txt){
	std::string title = titl;
	//std::cout << "MY NAME IS NOW " << title << std::endl;
	std::string author = auth;
	std::string text = txt;
	int id = ind;
}*/

const std::string& Article::get_name() const{
	std::cout << "MY NAME IS " << title << std::endl;

	return title;
}

const std::string& Article::get_author() const{
	return author;
}

const std::string& Article::get_text() const{
	return text;
}

std::string Article::to_string(){
	return "Title: " + title + "\nAuthor: " + author
		 + "\nId: " + std::to_string(id) + "\nText: " + text;
			
}

	

