#include "EnvBeaq.hpp"

#include "mBeaq.hpp"


using namespace std;
// -h help
// -c number of  version of backup
// -a automatic updates
// -p period for automatix updates implies -a
// -tar put files in tar archive
// -gz gzip compress
// -xz xz compresion
// -rsync [rsync comand]
// -f file name
// -t target directiry

class ParseLogic
{
private:
	OptionParser *allOP[NUMBER_OF_OPTIONS];

	eOptions idConvert(char const argv[])
	{
		eOptions out = EMPTY;

		for (size_t i = 0; i < OptionParser::getMaxNumOfObjects(); ++i)
		{
			if (NULL !=allOP[i])
			{
				if (0 != &argv[0] && 0 == strcmp(&argv[0], allOP[i]->CLIArgument()))
				{
					out = allOP[i]->getID();
				}
			}
			else
			{
				//  puts("NULL");
			}
			
		}

		return out;
	}

public:

	void checkArg(int argc, char const *argv[])
	{
		for (size_t i = 1; i < (size_t)argc; ++i)
		{
			eOptions id = idConvert(argv[i]);

			// std::cout << id << "\n";
			if (EMPTY != id)
			{
				if (NULL != allOP[id])
				{
					if(E_OK != allOP[id]->argOpParser(&argv[i]))
					{
						allOP[id]->printError();
						allOP[id]->printUsage();
					}
				}
			}
		}
	}

	ParseLogic()  = default;

	ParseLogic(OptionParser *allOP[NUMBER_OF_OPTIONS]) 
	{
		for (uint32 i = 0; i < NUMBER_OF_OPTIONS; ++i)
		{
			this->allOP[i]=allOP[i];
		}
	}

	~ParseLogic() = default;
};

void backupMain(OptionParser *allOP[NUMBER_OF_OPTIONS]);
bool compare_files(const std::string& filename1, const std::string& filename2);
string genTimeExtension();

int main(int argc, char const *argv[])
{
	HelpOp hel;
	FileName f;
	CountOp c;
	TargetOp s;

	OptionParser *allOP[NUMBER_OF_OPTIONS]={NULL};

	allOP[HELP]= (OptionParser *)&hel;
	allOP[FILE_NAME]= (OptionParser *)&f;
	allOP[COUNT]=(OptionParser *)&c;
	allOP[TARGET]= (OptionParser *)&s;

	ParseLogic a(allOP);

	a.checkArg(argc, argv);

	// cout << (((TargetOp*)allOP[TARGET])->target) << "\n";

	backupMain(allOP);

	return 0;
}



void backupMain(OptionParser *allOP[NUMBER_OF_OPTIONS])
{
	do
	{
		//check error state 
		StdRet Error = E_OK;
		for (uint32 i = 0; i < OptionParser::getMaxNumOfObjects(); ++i)
		{
			if (NULL != allOP[i])
			{
				Error |= allOP[i]->getError();
			}

		}
		if (E_OK != Error)
		{
			std::cout << "Errors detected" << std::endl;
			break;
		}




		string sourceName(((FileName*)allOP[FILE_NAME])->filename);
		string targetName  (((TargetOp*)allOP[TARGET])->target);

		std::filesystem::path source(sourceName);

		targetName.append(source.filename()).append(".beaq.");
		string regexName(targetName);
		regexName.append("[0-9]+(.*).bak");
		targetName.append(genTimeExtension());
		std::filesystem::path target(targetName);

		//make list of files in target directory

		std::filesystem::directory_iterator targetDir((target.parent_path()));

		std::vector<std::string> FilesInDirectory;
		for(auto& p: targetDir)
		{
			if (regex_match(p.path().c_str(),regex(regexName)))
			{
				FilesInDirectory.push_back(p.path());
				// cout << p.path() << std::endl;
			}	
		}
		sort(FilesInDirectory.begin(),FilesInDirectory.end(), [](const string & a, const string & b) -> bool { return a > b; });

		bool isReadyToCopy = false;

		//check if backup needs to be made
		if(0 != FilesInDirectory.size())
		{
			// cout << "\n" << sourceName;
			// cout << "\n" << FilesInDirectory[0].c_str() << "\n";

			if (true == compare_files(sourceName, FilesInDirectory[0]))
			{
		 		cout << "Files are the same not copied" << std::endl;
		 		isReadyToCopy = false;
		 	}
		 	else
		 	{
		 		isReadyToCopy = true;
		 	}
		}
		else
		{
			isReadyToCopy = true;
		}


		
		if (true == isReadyToCopy)
		{
			//make copy of file 
			std::filesystem::copy(source,target);

			//rename file if sucsesfull copy
			if (true == compare_files(sourceName, targetName))
			{
				std::filesystem::rename(target, std::filesystem::path(targetName.append(".bak")));
			}
			else
			{
				std::cout << "Unsucsesfull copy" << std::endl;
			}
		}


		uint32 countOfBackups = ((CountOp*)allOP[COUNT])->count;
		
		//remove old versions if nesasary
		if (1 < FilesInDirectory.size() && countOfBackups !=  FilesInDirectory.size() + 1 ) 
		{
			for (uint32 i = (isReadyToCopy) ? countOfBackups - 1  : countOfBackups ; i < FilesInDirectory.size() ; ++i)
			{	
				cout << "Removing OLD files: " << FilesInDirectory[i-1] << std::endl;
				std::remove(FilesInDirectory[i-1].c_str());
			}
		}	



	}while (0);
}



template<typename InputIterator1, typename InputIterator2>
bool
range_equal(InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2, InputIterator2 last2)
{
    while(first1 != last1 && first2 != last2)
    {
        if(*first1 != *first2) return false;
        ++first1;
        ++first2;
    }
    return (first1 == last1) && (first2 == last2);
}

bool compare_files(const std::string& filename1, const std::string& filename2)
{
    std::ifstream file1(filename1);
    std::ifstream file2(filename2);

    std::istreambuf_iterator<char> begin1(file1);
    std::istreambuf_iterator<char> begin2(file2);

    std::istreambuf_iterator<char> end;

    return range_equal(begin1, end, begin2, end);
}

string genTimeExtension()
{
	time_t timeStart = time(NULL);
 	std::ostringstream oss;
 	oss<<timeStart;
 	//making fancy time for name of the backup
 	struct tm * timeinfo = localtime(&timeStart);
 	char timeHumanReadeble[40];
 	strftime(timeHumanReadeble,40,".%d-%b-%Y-%Hh-%Mm-%Ss", timeinfo);


 	string returnString(oss.str());

 	returnString.append(timeHumanReadeble);

 	return returnString;
}


