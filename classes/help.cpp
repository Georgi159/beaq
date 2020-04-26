#include "EnvBeaq.hpp"
#include "help.hpp"



StdRet  HelpOp::argOpParser(char const *argv[])
{
	(void) argv;
	this->printUsage();
	return E_OK;
}

HelpOp::HelpOp() 
{
	static const char CLIArg_local[]="-h";
	CLIArg =(char *)CLIArg_local;
	Error=0;
	ID=HELP;
}



HelpOp::~HelpOp() = default;

