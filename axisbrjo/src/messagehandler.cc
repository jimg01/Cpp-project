#include "connection.h"	//remove here?
#include "connectionclosedexception.h"
#include "protocolviolationexception.h"
#include "protocol.h"
#include "messagehandler.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

/**
 * Message handler is the low-level message handler for messages to/from the
 * server. It handles transmission/reception of low-level message units.
 */



// to invoke move constructor? since copy constructors and assignments
//  are forbidden in Connection-class!
/*MessageHandler::MessageHandler(Connection conn): conn(std::move(conn)){ 
	//conn = std::move(conn);	
}
//USING INITIALIZER LIST IN HEADER FILE INSTEAD
*/




int MessageHandler::recvInt(){
	int b1 = recvByte();
//	logWindow.logByte(b1);
	int b2 = recvByte();
//	logWindow.logByte(b2);
	int b3 = recvByte();
//	logWindow.logByte(b3);
	int b4 = recvByte();
//	logWindow.logByte(b4);

	return b1 << 24 | b2 << 16 | b3 << 8 | b4;
}

int MessageHandler::recvIntParameter(){
	int code = recvCode();
	if (code != int(Protocol::PAR_NUM)) {
//		throw ProtocolViolationException("Receive numeric parameter",
//				Protocol::PAR_NUM, code);
//		ConnectionClosedException e;
		ProtocolViolationException e;
		throw (e);
	}
	return recvInt();
}


std::string MessageHandler::recvStringParameter(){
	int code = recvCode();
	if (code != int(Protocol::PAR_STRING)) {
//		throw ProtocolViolationException("Receive string parameter",
//				Protocol::PAR_STRING, code);

//		ConnectionClosedException e;
		ProtocolViolationException e;
		throw (e);	//fix correct violation??
	}
	int n = recvInt();
	if (n < 0) {

	//	throw ProtocolViolationException("Receive string parameter",
	//			"Number of characters < 0");
	//	ConnectionClosedException e;
		ProtocolViolationException e;
		throw (e);
	}
	
	//StringBuffer result = new StringBuffer(n);
	std::stringstream result;
	for (int i = 1; i <= n; i++) {
		char ch = char(connPtr->read());
		result << ch;
		
//		logWindow.logChar(ch);
	}
	return result.str();
}



int MessageHandler::recvByte(){
	int code = connPtr->read();
	if (!connPtr->isConnected()){//if (code == ::CONNECTION_CLOSED) {
		ConnectionClosedException e;
		throw (e);	
	}
	return code;
}

bool MessageHandler::isConnected(){
	return connPtr->isConnected();
}
	
int MessageHandler::recvCode(){
	int code = recvByte();
//	logWindow.logCode(code);
	return code;
}






//----------SEND-------------


void MessageHandler::sendStringParameter(std::string param){
	sendCode(int(Protocol::PAR_STRING));
	sendInt(param.length());
	for (long unsigned int i = 0; i < param.length(); i++) {
		sendByte(param[i]);
//			logWindow.logChar(param.charAt(i));
	}

}



void MessageHandler::sendByte(int code) {
	try {
			connPtr->write(char(code));
			//std::cout << char(code) << " or as a number: " << code << std::endl;
		} catch (ConnectionClosedException e) {
			throw (e);
		}
}


void MessageHandler::sendCode(int code) {
	sendByte(code);
	//logWindow.logCode(code);
}


void MessageHandler::sendInt(int value) {
		sendByte((value >> 24) & 0xFF);
//		logWindow.logByte((value >> 24) & 0xFF);
		sendByte((value >> 16) & 0xFF);
//		logWindow.logByte((value >> 16) & 0xFF);
		sendByte((value >> 8) & 0xFF);
//		logWindow.logByte((value >> 8) & 0xFF);
		sendByte(value & 0xFF);
//		logWindow.logByte(value & 0xFF);
	}

void MessageHandler::sendIntParameter(int param) {
	sendCode(int(Protocol::PAR_NUM));
	sendInt(param);
}

void MessageHandler::setConnection(std::shared_ptr<Connection>& conn){
    connPtr = conn;
}