#ifndef RESOURCE_H
#define RESOURCE_H

#include "Win/Common/Global.h"
#include "Win/Common/Exception.h"

namespace Bicycle
{
//------------------------------------------------
  class ResourceUpdater
  {
    public:
      ResourceUpdater();

      void beginUpdate(const tstring& fileName,bool deleteExistingResources=false);

      void update(const tchar* type,const tstring& name, // RT_RCDATA,
                  void* data, ulong dataSize,
                  uint language=0); // MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL)

      void update(uint type,const tstring& name, // RT_RCDATA,
                  void* data, ulong dataSize,
                  uint language=0); // MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL)

      void update(const tstring& type,const tstring& name, // RT_RCDATA,
                  void* data, ulong dataSize,
                  uint language=0); // MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL)


      void endUpdate(bool discard=false);

      ~ResourceUpdater();
    private:
      HANDLE handle_;
  };
  //------------------------------------------------
  class ResourceReader
  {
     public:
        ResourceReader();
        ~ResourceReader();

        void loadFile(const tstring& fileName= tstring());
        void freeFile(bool notThrow= false);

        void findResource(const tstring& name, const tchar* type);
        void findResource(const tstring& name, const tstring& type);
        void findResource(const tstring& name, uint type);

        void loadResource();
        void freeResource(bool notThrow= false);

        const char* lockResource();
        void unlockResource();

        ulong sizeResource()const;

    private:
      HMODULE handle_;
      HRSRC src_;
      HGLOBAL resourceData_;

      const char* data_;
      ulong size_;
  };
  //------------------------------------------------
}
#endif // RESOURCE_H
