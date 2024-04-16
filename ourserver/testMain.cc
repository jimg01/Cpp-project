#include "newsgroup.h"

#include <string>
#include <iostream>

void print(NewsGroup g){
	std:: cout << g.to_string() << std::endl;
}

int main() {
	NewsGroup group(1, "testgroup1");
	print(group);

	group.create_article("titel", "forf1", "blablabla" );
	print(group);
};
