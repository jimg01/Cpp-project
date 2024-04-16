#include "connection.h"	//remove here?
#include "connectionclosedexception.h"
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

#if 0
	/**
	 * Transmit a string parameter, according to the protocol.
	 * 
	 * @param value
	 *            The parameter to transmit
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	void sendStringParameter(String param){
		sendCode(Protocol.PAR_STRING);
		sendInt(param.length());
		for (int i = 0; i < param.length(); i++) {
			sendByte(param.charAt(i));
			logWindow.logChar(param.charAt(i));
		}
	}

	
	/**
	 * Receive a command code or an error code from the server.
	 * 
	 * @return The code
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	int recvCode(){
		int code = recvByte();
		logWindow.logCode(code);
		return code;
	}

	/**
	 * Receive an int value from the server.
	 * 
	 * @return The int value
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	int recvInt(){
		int b1 = recvByte();
		logWindow.logByte(b1);
		int b2 = recvByte();
		logWindow.logByte(b2);
		int b3 = recvByte();
		logWindow.logByte(b3);
		int b4 = recvByte();
		logWindow.logByte(b4);

		return b1 << 24 | b2 << 16 | b3 << 8 | b4;
	}

	/**
	 * Receive an int parameter from the server.
	 * 
	 * @return The parameter value
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	int recvIntParameter(){
		int code = recvCode();
		if (code != Protocol.PAR_NUM) {
			throw new ProtocolViolationException("Receive numeric parameter",
					Protocol.PAR_NUM, code);
		}
		return recvInt();
	}

	/**
	 * Receive a string parameter from the server.
	 * 
	 * @return The parameter value
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	String recvStringParameter(){
		int code = recvCode();
		if (code != Protocol.PAR_STRING) {
			throw new ProtocolViolationException("Receive string parameter",
					Protocol.PAR_STRING, code);
		}
		int n = recvInt();
		if (n < 0) {
			throw new ProtocolViolationException("Receive string parameter",
					"Number of characters < 0");
		}
		StringBuffer result = new StringBuffer(n);
		for (int i = 1; i <= n; i++) {
			char ch = (char) conn.read();
			result.append(ch);
			logWindow.logChar(ch);
		}
		return result.toString();
	}
#endif


void MessageHandler::sendByte(int code) {
	try {
			conn.write(char(code));
		} catch (ConnectionClosedException& e) {
			throw ConnectionClosedException();
		}
	

	/*		try {
				conn.write((char) code);
			} catch (java.io.IOException e) {
				throw new ConnectionClosedException();
			}
		}
	*/
}

int MessageHandler::recvByte(){
	int code = conn.read();
	if (code == Connection.CONNECTION_CLOSED) {
		throw ConnectionClosedException();
	}
	return code;
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
	sendCode(Protocol.PAR_NUM);
	sendInt(param);
}
