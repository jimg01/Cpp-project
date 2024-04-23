// ------------------------------------------------------------------
//
//                                ProtocolViolationException header file
//
// A ProtocolViolationException is thrown when a MessageHandler get an 
// unrecognised protocol code.
//
//
// ------------------------------------------------------------------

#ifndef PROTOCOL_VIOLATION_EXCEPTION_H
#define PROTOCOL_VIOLATION_EXCEPTION_H

#include "protocol.h"
#include <string>
#include <iostream>

struct ProtocolViolationException {};
/*
struct ProtocolViolationException(std::string message, Protocol num, int codeRec) {
	std::cerr << message << std::endl;
	std::cerr << "Received " << codeRec << std::endl;
	std::cerr << "Should be " << int(num) << std::endl;
};

struct ProtocolViolationException(std::string mess1, std::string mess2) {
	std::cerr << mess1 << mess2 << std::endl;
};
*/
//make a more flexible implementation for change of number of paramaters??
#endif
