#include "messagehandler.h"
#include <iostream>

int main(){
	Connection conn;
	MessageHandler mh(std::move(conn));
	//std::cout << mh.recvByte() << std::endl;
	
}
