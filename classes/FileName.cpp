#include "EnvBeaq.hpp"
#include "FileName.hpp"





void FileName::printError()
{
  std::cout << "No valid source file or directory" << std::endl;
}


StdRet  FileName::argOpParser(char const *argv[])
{
  this->fType = fileType(argv[1]);
  this->filename.assign(argv[1]) ;
  // std::cout <<this->filename;

  if (this->fType != FILEE && this->fType != DIR)
  {
    Error=E_NO_SOURCE;
  }
  else
  {
    Error=E_OK;
  }

  return Error;
}

eFileType FileName::fileType(const char *path)
{
  struct stat info;
  eFileType ret;
  if (stat( path, &info ) != 0)
  {
    ret = ERROR;
  }
  switch (info.st_mode & S_IFMT)
  {
    case S_IFREG:
       ret = FILEE;
       break;
    case S_IFDIR:  
      ret=DIR;
      break;
    case S_IFBLK:  
    case S_IFCHR: 
    case S_IFIFO: 
    case S_IFLNK:  
    case S_IFSOCK: 
    default:
      ret=OTHER;
      break;
  }
  return ret;
}


FileName::FileName()
{
  static const char CLIArg_local[] = "-f";
  CLIArg = (char *)CLIArg_local;
  ID = FILE_NAME;
}

FileName::~FileName() = default;

