//----------------------------------------------------------
#include "Library.h"

using namespace Bicycle;
//----------------------------------------------------------
Library::Library(const std::string &modulePath)
  :module_(0)
{
  load(modulePath);
}
//----------------------------------------------------------
Library::Library(const std::wstring &modulePath)
  :module_(0)
{
  load(modulePath);
}
//----------------------------------------------------------
Library::~Library()
{
  Library::free(false);
}
//----------------------------------------------------------
void Library::free(bool throwException/*=true*/)
{
  if (module_)
  {
    if(!FreeLibrary(module_))
    {
      module_= 0;
      if(!throwException)
         throw SystemException();
    }
    module_= 0;
  }
}
//----------------------------------------------------------
void Library::load(const std::string& modulePath)
{
  Library::free();
  module_= LoadLibraryA(modulePath.c_str());
  if(!module_)
     throw SystemException("Library: ");
}
//----------------------------------------------------------
void Library::load(const std::wstring& modulePath)
{
  Library::free();
  module_= LoadLibraryW(modulePath.c_str());
  if(!module_)
     throw SystemException("Library: ");
}
//----------------------------------------------------------
bool Library::isLoaded()const
{
  return module_!=NULL;
}
//----------------------------------------------------------
