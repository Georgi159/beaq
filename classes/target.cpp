#include "EnvBeaq.hpp"
#include "target.hpp"
#include "FileName.hpp"


using namespace std;

void TargetOp::printError()
{
  std::cout << "No valid target  directory" << std::endl;
}


StdRet  TargetOp::argOpParser(char const *argv[])
{
	StdRet ret= E_OK;

	// std::cout <<argv[1];

	fType = FileName::fileType(argv[1]);

	if (DIR != fType)
	{
		ret=E_ERROR; 
		Error = E_ERROR;
	}

	// std::cout <<strlen(&argv[1][0]) << "\n";
  	this->target.assign(argv[1]) ;


  	 // std::cout <<"\t\t\t\t"<<this->target;
	return ret;
}

TargetOp::TargetOp() 
{
	static const char CLIArg_local[]="-t";
	CLIArg =(char *)CLIArg_local;
	ID=TARGET;
}

TargetOp::~TargetOp() = default;

