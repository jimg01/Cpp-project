#include "connection.h"
#include "connectionclosedexception.h"
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

        std::shared_ptr<Connection> connPtr;
	
		//Connection conn; // the connection
//		Logger logWindow; // the log window	//ignore for now

		//throws (ConnectionClosedException)
		void sendByte(int code);

		//throws (ConnectionClosedException)
		int recvByte();

	public:

	bool isConnected();
	/**
	 * Create a message handler.
	 * 
	 * @param conn
	 *            The connection to use messages
	 */
	MessageHandler(std::shared_ptr<Connection>& connec): connPtr(std::move(connec)) {}

    //MessageHandler(Connection& connec): conn(std::move(connec)) {}

    MessageHandler() = default;

    void setConnection(std::shared_ptr<Connection>& conn);
	// to invoke move constructor, since copy constructors and assignments
	//  are forbidden in Connection-class!
	
	
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
	void sendCode(int code); 
	

	/**
	 * Transmit an int value, according to the protocol.
	 * 
	 * @param value
	 *            The value to transmit
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	void sendInt(int value);
	
	/**
	 * Transmit an int parameter, according to the protocol.
	 * 
	 * @param value
	 *            The parameter to transmit
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	void sendIntParameter(int param);

	/**
	 * Transmit a string parameter, according to the protocol.
	 * 
	 * @param value
	 *            The parameter to transmit
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	void sendStringParameter(std::string param);
	
	/**
	 * Receive a command code or an error code from the server.
	 * 
	 * @return The code
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	int recvCode();


	/**
	 * Receive an int value from the server.
	 * 
	 * @return The int value
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	int recvInt();
	
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
