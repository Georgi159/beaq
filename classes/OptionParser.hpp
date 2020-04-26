#ifndef OptionParser_HPP
#define OptionParser_HPP

#include "EnvBeaq.hpp"



class OptionParser
{
private: 
	const static uint32 maxObjects = NUMBER_OF_OPTIONS;

	static uint32 numOfObjects;


protected:
	char *CLIArg;
	eOptions ID;
	StdRet Error;

public:

	virtual StdRet argOpParser(char const *argv[]);

	virtual void printError();

	StdRet getError();


	const char* CLIArgument();

	static uint32 getNumOfObjects ();
	static uint32 getMaxNumOfObjects ();
	eOptions getID();





	void printUsage();


	OptionParser();
	
	~OptionParser();

};


#endif