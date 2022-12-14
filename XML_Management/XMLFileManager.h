#pragma once
#include <string>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include <vector>
#include "./../Algorithm/Type.h"

class XMLFileManager
{
private:

	rapidxml::file<>* XMLFile;
	void OpenFile(std::string path);

public:
	XMLFileManager();
	~XMLFileManager();

    std::vector<FPA::Type*> ReadFromXML(std::string path);
    void SaveToXML(std::vector<FPA::Type*> types, std::string path);
};

