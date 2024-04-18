#include "messagehandler.h"
#include "connection.h"
#include <iostream>

int main(){
	Connection conn("local host", 7777);
	MessageHandler mh(std::move(conn));
	mh.sendCode(1);
	mh.sendStringParameter("hej");
	//std::cout << "hej" << std::endl;
	
	
}
