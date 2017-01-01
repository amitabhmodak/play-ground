#include "SendMail.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <iostream>
#include "Utlity.h"
 
void SendMail::sendMail(std::string message, std::string to) {
	if (updateMailSettings()) {
		std::stringstream mailMessage;
		mailMessage << "curl " << m_smtp << " -v --mail-from " << m_from << " --mail - rcpt " << to
			<< " --ssl -u " << m_from << ":" << m_password << " -T " << message << " -k --anyauth";
		std::cout << mailMessage.str();
		WinExec(mailMessage.str().data(), SW_HIDE);
	}
}

bool SendMail::updateMailSettings() {
	if (m_initSuccess)
		return true;
	boost::property_tree::ptree pt;
	try {
		boost::property_tree::ini_parser::read_ini(SERVERINI, pt);
		if (pt.size() == 0)
			return false;

		m_from = pt.get<std::string>("From.mailid");
		if (m_from.empty())
			return false;

		m_password = pt.get<std::string>("From.password");
		if (m_from.empty())
			return false;

		m_smtp = pt.get<std::string>("From.smtp") ;
		if (m_from.empty())
			return false;
	}
	catch (...) {
		return false;
	}
	m_initSuccess = true;
	return true;
}
