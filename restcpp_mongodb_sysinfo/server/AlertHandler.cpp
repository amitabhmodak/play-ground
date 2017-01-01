#include "AlertHandler.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <iostream>
#include "Utlity.h"
 
void AlertHandler::handleCpuAlert(double cpu, std::string clientId) {

	std::string value = Utlity::getValue(clientId + ".cpu", SERVERINI);
	std::string mail = Utlity::getValue(clientId + ".mail", SERVERINI);
	if (value.empty() == true)
		return;
	if (mail.empty() == true)
		return;
	int threshHold = std::stoi(value);
	if (threshHold <= 0)
		return;
	if (cpu >= threshHold) {
		std::stringstream msg;
		msg << "CPU alert: process count is " << cpu;
		m_mail.sendMail(msg.str(), mail);
	}

}
void AlertHandler::handleMemoryAlert(double memory, std::string clientId) {
	
	std::string value = Utlity::getValue(clientId + ".memory", SERVERINI);
	std::string mail = Utlity::getValue(clientId + ".mail", SERVERINI);
	if (value.empty() == true)
		return;
	if (mail.empty() == true)
		return;
	int threshHold = std::stoi(value);
	if (threshHold <= 0)
		return;
	if (memory >= threshHold) {
		std::stringstream msg;
		msg << "Memory alert: process count is " << memory;
		m_mail.sendMail(msg.str(), mail);
	}
	 
}
void AlertHandler::handleProcessAlert(size_t count, std::string clientId) {

	std::string value = Utlity::getValue(clientId + ".process", SERVERINI);
	std::string mail = Utlity::getValue(clientId + ".mail", SERVERINI);
	if (value.empty() == true)
		return;
	if (mail.empty() == true)
		return;
	auto threshHold = std::stoul(value);
	if (threshHold <= 0)
		return;
	if (count >= threshHold) {
		std::stringstream msg;
		msg << "Process alert: process count is " << count;
		m_mail.sendMail(msg.str(), mail);
	}
}