#ifndef HELP_HPP
#define HELP_HPP

#include "EnvBeaq.hpp"
#include "OptionParser.hpp"





class HelpOp : public OptionParser
{
private:

public:
	StdRet argOpParser(char const *argv[]) override;

	

	HelpOp();

	~HelpOp();

};

#endif 