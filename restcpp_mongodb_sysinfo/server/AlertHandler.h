#pragma once

#include<string>
#include "SendMail.h"

class AlertHandler
{
	SendMail m_mail;
public:
	AlertHandler() = default;
	~AlertHandler() = default;
	void handleCpuAlert(double cpu, std::string clientId);
	void handleMemoryAlert(double memory, std::string clientId);
	void handleProcessAlert(size_t count, std::string clientId);
 };

