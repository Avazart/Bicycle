#ifdef _MSC_VER
  #pragma once
#endif
// ---------------------------------------------------------------------------
#ifndef FileH
#define FileH
// ---------------------------------------------------------------------------
#include "Global.h"
#include "IODevice.h"
#include "NonCopyable.h"
#include "SystemException.h"
// ---------------------------------------------------------------------------
namespace Bicycle
{
// ---------------------------------------------------------------------------
class File: public IODevice, private NonCopyable
{
public:
   //  IODevice
   virtual ulong read(char* data, ulong size, ulong& errorCode);
   virtual ulong write(const char* data, ulong size, ulong& errorCode);
   virtual void checkErrorCode(ulong code) const;
  
   enum { Read=  GENERIC_READ,
          Write= GENERIC_WRITE };

   enum { CreateNew=   CREATE_NEW,
          CreateAlways= CREATE_ALWAYS,
          OpenExisting= OPEN_EXISTING,
          OpenAlways=  OPEN_ALWAYS,
          TrancateExisting= TRUNCATE_EXISTING };



   explicit File(const tstring& fileName= tstring(),
                 ulong desiredAccess=GENERIC_READ|GENERIC_WRITE,
                 ulong creationDisposition= OPEN_EXISTING);
   ~File();
  
   void open();
   void close();

   HANDLE handle();

   ulong desiredAccess()const;
   ulong shareMode()const;
   ulong creationDisposition()const;
   ulong flagsAndAttributes()const;

   void setDesiredAccess(ulong access);
   void setShareMode(ulong mode);
   void setCreationDisposition(ulong disposition);
   void setFlagsAndAttributes(ulong flagsAndAttr);

   ulong setFilePointer(long distanceToMove,
                        ulong moveMethod,
                        long* distanceToMoveHigh=0);

   __int64 seek(__int64 distance, ulong moveMethod);

   void setEndOfFile();


private:
   tstring fileName_; 
   HANDLE handle_;

   ulong desiredAccess_;
   ulong shareMode_;
   ulong creationDisposition_;
   ulong flagsAndAttributes_ ;
};
// ---------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------
#endif
