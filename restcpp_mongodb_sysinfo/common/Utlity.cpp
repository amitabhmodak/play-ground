#include"Utlity.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp> 
 
std::string Utlity::getValue(std::string text, std::string configFile) {
	boost::property_tree::ptree pt;
	std::string value;
	try {
		boost::property_tree::ini_parser::read_ini(configFile, pt);
		if (pt.size() == 0)
			return value;
		value = pt.get<std::string>(text);
	}
	catch (...) {
		return value;
	}
	return value;
}
