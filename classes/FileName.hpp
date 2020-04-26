#ifndef FILENAME
#define FILENAME 

#include "EnvBeaq.hpp"
#include "OptionParser.hpp"





class FileName : public OptionParser
{
private:
	eFileType fType;
	

public:

	static eFileType fileType(const char *path);


	std::string filename;
	
	StdRet argOpParser(char const *argv[]) override;

	void printError() override;


	FileName();

	~FileName();

};




#endif