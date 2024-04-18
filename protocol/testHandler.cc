#include "messagehandler.h"
#include "connection.h"
#include <iostream>

int main(){
	Connection conn;
	MessageHandler mh(std::move(conn));
	mh.sendCode(1);
	std::cout << "hej" << std::endl;
	
	
}
