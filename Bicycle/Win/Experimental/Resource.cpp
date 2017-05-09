#include "Resource.h"

using namespace Bicycle;

ResourceUpdater::ResourceUpdater()
  :handle_(0)
{

}
//-----------------------------------------------------------------------------------
void ResourceUpdater::beginUpdate(const tstring &fileName, bool deleteExistingResources)
{
  handle_ = BeginUpdateResource(fileName.c_str(),deleteExistingResources);
  if(!handle_)
    throw SystemException();
}
//-----------------------------------------------------------------------------------
void ResourceUpdater::update(const tchar* type, const tstring &name,
                      void *data, ulong dataSize,
                      uint language)
{
  if(!UpdateResource(handle_,
                     type, name.c_str(),
                     language,
                     data, dataSize))
    throw SystemException();
}
//-----------------------------------------------------------------------------------
void ResourceUpdater::update(const tstring &type, const tstring &name,
                      void *data, ulong dataSize,
                      uint language)
{
  update(type.c_str(),name,data,dataSize,language);
}
//-----------------------------------------------------------------------------------
void ResourceUpdater::update(uint type, const tstring &name,
                      void *data, ulong dataSize,
                      uint language)
{
  if(!UpdateResource(handle_,
                     MAKEINTRESOURCE(type), name.c_str(),
                     language,
                     data, dataSize))
    throw SystemException();
}
//-----------------------------------------------------------------------------------
void ResourceUpdater::endUpdate(bool discard)
{
  if(handle_)
  {
    if(!EndUpdateResource(handle_,discard))
    {
      handle_ = 0;
      throw SystemException();
    }
    handle_ = 0;
  }
}
//-----------------------------------------------------------------------------------
ResourceUpdater::~ResourceUpdater()
{
  endUpdate(true);
}
//===================================================================================
ResourceReader::ResourceReader()
  :handle_(0),
   src_(0),
   resourceData_(0)
{

}
//----------------------------------------------------------------------
void ResourceReader::loadFile(const tstring &fileName)
{
  handle_ =
      fileName.empty()?
        GetModuleHandle(0):
        LoadLibraryEx(fileName.c_str(),0,LOAD_LIBRARY_AS_DATAFILE);

  if(!handle_)
    throw Bicycle::SystemException();
}

//----------------------------------------------------------------------
void ResourceReader::findResource( const tstring &name,const tchar *type)
{
  src_ =
      FindResource(handle_,name.c_str(),type);
  if(!src_)
    throw Bicycle::SystemException();
}

void ResourceReader::findResource(const tstring &name, const tstring &type)
{
  findResource(name,type.c_str());
}

void ResourceReader::findResource(const tstring &name, uint type)
{
  src_ =
      FindResource(handle_,name.c_str(),MAKEINTRESOURCE(type));
  if(!src_)
    throw Bicycle::SystemException();
}
//----------------------------------------------------------------------
void ResourceReader::loadResource()
{
  freeResource();
  resourceData_ = LoadResource(handle_, src_);
  if(!resourceData_)
    throw Bicycle::SystemException();
}
//----------------------------------------------------------------------
const char *ResourceReader::lockResource()
{
  unlockResource();
  return static_cast<char*>(LockResource(resourceData_));
}
//----------------------------------------------------------------------
ResourceReader::~ResourceReader()
{
  freeFile(true);
}

void ResourceReader::freeFile(bool notThrow)
{
  if(handle_)
  {
     freeResource(notThrow);

     bool success= FreeLibrary(handle_)==TRUE;
     handle_= 0;
     if (!success && !notThrow)
       throw Bicycle::SystemException();
  }
}

void ResourceReader::freeResource(bool notThrow)
{
  if(resourceData_)
  {
     unlockResource();

     bool success= FreeResource(resourceData_)==TRUE;
     resourceData_= 0;

     if (!success && !notThrow)
       throw Bicycle::SystemException();
  }
}
void ResourceReader::unlockResource()
{
  if(resourceData_)
    UnlockResource(resourceData_);
}

ulong ResourceReader::sizeResource() const
{
  if(handle_ && src_)
    return SizeofResource(handle_,src_);
  else
    return 0;
}





