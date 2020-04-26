#ifndef COUNT_HPP
#define COUNT_HPP

#include "EnvBeaq.hpp"
#include "OptionParser.hpp"




class CountOp : public OptionParser
{
private:

public:

	uint32 count;


	StdRet argOpParser(char const *argv[]) override;

	CountOp();

	~CountOp();

};



#endif 