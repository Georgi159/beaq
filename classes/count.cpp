#include "EnvBeaq.hpp"
#include "count.hpp"



StdRet  CountOp::argOpParser(char const *argv[])
{
	StdRet ret= E_OK;

	count = atol(argv[1]);


	// std::cout << count;
	// puts("tesss");
	return ret;
}

CountOp::CountOp() 
{
	static const char CLIArg_local[]="-c";
	CLIArg =(char *)CLIArg_local;
	ID=COUNT;
}

CountOp::~CountOp() = default;

