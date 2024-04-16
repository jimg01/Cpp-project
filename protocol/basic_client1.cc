#include <iostream>
#include <string>

void printAlt(){
	std::string s = "\n1. List newsgroups. \n2. Create a newsgroup.";
	s.append("\n3. Delete a newsgroup.\n4. List articles in a newsgroup.");
	s.append("\n5. Create an article.\n6. Delete an article.\n7. Get an article.");			
	
	std::cout << s << std::endl;
	
}


int main(){
	printAlt();

	int i;
	std::cin >> i;
	string message;

	// create connection
	MessageHandler handler;
	
	if(i == 2){
		std::string name;
		std::cin >> name;

		handler.sendCode(i);
		
		message.append(Protocol.COM_CREATE_NG);
		message.append(Protocol.PAR_STRING);
		message.append(std::to_string(name.size());
		message.append(name);
		message.append(Protocol.COM_END);
	}
}
