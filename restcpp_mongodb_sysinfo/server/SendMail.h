#pragma once
#include <windows.h>
#include <string>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

class SendMail
{
	std::string m_smtp;
	std::string m_from;
	std::string m_password;
	bool m_initSuccess = false;
public:
	SendMail() = default;
	~SendMail() = default;
	void sendMail(std::string message, std::string to);
	 
	bool updateMailSettings();
};

