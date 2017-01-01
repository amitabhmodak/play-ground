#include "DeviceMonitor.h"
 #include "Client.h"
#include <conio.h>
#include "RestClient.h"
#include "Utlity.h"

void readConfig(std::string& url, std::string &mail, std::string &clientKey) {


}
int main(int argc, char *argv[])
{
	_getch();
	std::string host = Utlity::getValue("Server.host", "clientconfig.ini");
	std::string mail = Utlity::getValue("Device.mail", "clientconfig.ini");
	if (host.empty()) {
		std::cout << "Configure clientconfig.ini to set server address\n";
		return 0;
	}
	std::unique_ptr<RestClient> handler = std::make_unique<RestClient>(host);
	Client client(mail,std::move(handler));
	client.start();
	
	std::cout<<"Press any key to exit\n";
	_getch();
	return 1;
}
 