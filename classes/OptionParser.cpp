#include "EnvBeaq.hpp"
#include "OptionParser.hpp"





uint32 OptionParser::numOfObjects = 0;

StdRet OptionParser::argOpParser(char const *argv[])
{
	(void) argv;
	std::cout << "virtual" << "\n";
	return E_OK;
}

uint32 OptionParser::getNumOfObjects()
{
	return numOfObjects;
}
uint32 OptionParser::getMaxNumOfObjects()
{
	return maxObjects;
}

const char* OptionParser::CLIArgument()
{
	return this->CLIArg;
}

eOptions OptionParser::getID()
{
	return ID;
}


void OptionParser::printError()
{
	if (0 != this->Error)
	{
		std::cout << "no error mesage defined" << std::endl;
	}
}

StdRet OptionParser::getError()
{
	return this->Error;
}



void OptionParser::printUsage()
{
	static bool isPrinted=false;
	if (isPrinted)
	{
		std::cout << "beaq [-h] [-c number of backups] [-f file:directory] [-t backup directory] " << "\n";
		isPrinted=true;
	}
}

OptionParser::OptionParser()
{
	numOfObjects++;
	Error=E_OK;
}



OptionParser::~OptionParser() = default;