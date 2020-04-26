#ifndef TARGET_HPP
#define TARGET_HPP

#include "EnvBeaq.hpp"
#include "OptionParser.hpp"




class TargetOp : public OptionParser
{
private:
	eFileType fType;

public:
	std::string target;
	void printError() override;
	StdRet argOpParser(char const *argv[]) override;

	TargetOp();

	~TargetOp();

};



#endif 