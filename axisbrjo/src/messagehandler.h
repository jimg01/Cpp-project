#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H


#include "connection.h"
#include "connectionclosedexception.h"
#include "protocolviolationexception.h"
#include "protocol.h"


#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <memory>

using std::string;

/**
 * Message handler is the low-level message handler for messages to/from the
 * server. It handles transmission/reception of low-level message units.
 */

class MessageHandler {

	private:

    std::shared_ptr<Connection> connPtr; // the connection

    //Logger logWindow; // the log window	//ignore for now

	//throws (ConnectionClosedException)
	void sendByte(const int code);

	//throws (ConnectionClosedException)
	int recvByte();

    /**
	 * Transmit an int value, according to the protocol.
	 * 
	 * @param value
	 *            The value to transmit
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	void sendInt(const int value);

    /**
	 * Receive an int value from the server.
	 * 
	 * @return The int value
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	int recvInt();

	public:

	bool isConnected();
	/**
	 * Create a message handler.
	 * 
	 * 
     * 
    **/
    MessageHandler() = default;

    void setConnection(std::shared_ptr<Connection>& conn);
	
	
	
	/**
	 * Set the log window to use.
	 * 
	 * @param logWindow
	 *            The log window
	 */
	//void setLogWindow(Logger logWindow): logWindow(logWindow) {}	//ignore for now

		/**
	 * Transmit a code (a constant from the Protocol class).
	 * 
	 * @param code
	 *            The code to transmit.
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	void sendCode(const int code); 
	
	/**
	 * Transmit an int parameter, according to the protocol.
	 * 
	 * @param value
	 *            The parameter to transmit
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	void sendIntParameter(const int param);

	/**
	 * Transmit a string parameter, according to the protocol.
	 * 
	 * @param value
	 *            The parameter to transmit
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	void sendStringParameter(const std::string param);
	
	/**
	 * Receive a command code or an error code from the server.
	 * 
	 * @return The code
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	int recvCode();
	
	/**
	 * Receive an int parameter from the server.
	 * 
	 * @return The parameter value
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	int recvIntParameter();

	/**
	 * Receive a string parameter from the server.
	 * 
	 * @return The parameter value
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	std::string recvStringParameter();



};

#endif