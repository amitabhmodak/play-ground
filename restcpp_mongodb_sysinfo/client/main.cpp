#include "DeviceMonitor.h"
 #include "Client.h"
#include <conio.h>
#include "RestClient.h"
#include "Utlity.h"

void readConfig(std::string& url, std::string &mail, std::string &clientKey) {


}
int main(int argc, char *argv[])
{
 
	std::string host = Utlity::getValue("Server.host", "clientconfig.ini");
	std::string mail = Utlity::getValue("Device.mail", "clientconfig.ini");
	if (host.empty()) {
		std::cout << "Configure clientconfig.ini to set server address\n";
		return 0;
	}

	{
		std::unique_ptr<RestClient> handler = std::make_unique<RestClient>(host);
		Client client(mail, std::move(handler));
		client.run();

		std::cout << "Press any key to stop processing\n";
		_getch();
		std::cout << "Stop thread called\n";
		client.stop();
		std::cout << "Press any key to exit\n";
		Logger::instance().closeFile();
	}
	
	_getch();
	return 1;
}
 