//---------------------------------------------------------------------------
#include "File.h"
//---------------------------------------------------------------------------
// http://comprice.ru/articles/detail.php?ID=42529
//---------------------------------------------------------------------------
using namespace Bicycle;
//------------------ IODevice -----------------------------------------------
ulong File::read(char *data, ulong size)
{
  ulong length= 0;
  BOOL success= ReadFile(handle_, data, size, &length, NULL);
  if(!success)
  {
    throw SystemException();
  }
//  else if(length==0)
//  {
//    throw EOFException(ERROR_HANDLE_EOF);
//  }
  return length;
}
//---------------------------------------------------------------------------
ulong File::write(const char *data, ulong size)
{
  ulong length= 0;
  BOOL success= WriteFile(handle_, data, size, &length, NULL);
  if(!success)
     throw SystemException();
  return length;
}
//------------------------- File --------------------------------------------
File::File(const tstring& fileName/*= tstring()*/,
           ulong desiredAccess/*=GENERIC_READ|GENERIC_WRITE*/,
           ulong creationDisposition/*=OPEN_EXISTING*/)
    :fileName_(fileName),
     handle_(INVALID_HANDLE_VALUE),
     desiredAccess_(desiredAccess),
     shareMode_(0), // FILE_SHARE_READ  FILE_SHARE_WRITE который контролирует открытие файла другими приложениями (пользователями).
     creationDisposition_(creationDisposition),
     /* CREATE_NEW - создается новый файл;
        CREATE_ALWAYS - создается файл с указанным именем, или если такой файл уже создан, то он удаляется и создается заново;
        OPEN_EXISTING - открывает уже созданный файл;
        OPEN_ALWAYS - открывает файл с указанным именем (параметр lpFileName), если его нет, то он создается;
        TRUNCATE_EXISTING - открывает файл, после чего происходит удаление его содержимого до нуля байт.
     */
     flagsAndAttributes_(FILE_ATTRIBUTE_NORMAL)
     /* указывает, какие атрибуты применять при создании файла
        FILE_ATTRIBUTE_READONLY - только чтение,
        FILE_ATTRIBUTE_ARCHIVE - архивный файл;
        FILR_ATTRIBUTE_HIDDEN - скрытый файл
     */
{

}
//---------------------------------------------------------------------------  
File::~File()
{
  close();
}
//---------------------------------------------------------------------------  
void File::open()
{
  close();

  handle_=
      CreateFile(fileName_.c_str(),
                 desiredAccess_,
                 shareMode_,
                 NULL,
                 creationDisposition_,
                 flagsAndAttributes_,
                 NULL);

  if(handle_== INVALID_HANDLE_VALUE)
    throw SystemException();
}
//---------------------------------------------------------------------------
void File::close()
{
  if(handle_!= INVALID_HANDLE_VALUE)
  {
    CloseHandle(handle_);
    handle_= INVALID_HANDLE_VALUE;
  }
}
//---------------------------------------------------------------------------
HANDLE File::handle()
{
  return handle_;
}
//---------------------------------------------------------------------------
ulong File::desiredAccess() const
{
  return desiredAccess_;
}
//---------------------------------------------------------------------------
ulong File::shareMode() const
{
  return shareMode_;
}
//---------------------------------------------------------------------------
ulong File::creationDisposition() const
{
  return creationDisposition_;
}
//---------------------------------------------------------------------------
ulong File::flagsAndAttributes() const
{
  return flagsAndAttributes_;
}
//---------------------------------------------------------------------------
void File::setDesiredAccess(ulong access)
{
  desiredAccess_= access;
}
//---------------------------------------------------------------------------
void File::setShareMode(ulong mode)
{
  shareMode_= mode;
}
//---------------------------------------------------------------------------
void File::setCreationDisposition(ulong disposition)
{
 creationDisposition_= disposition;
}
//---------------------------------------------------------------------------
void File::setFlagsAndAttributes(ulong flagsAndAttr)
{
  flagsAndAttributes_= flagsAndAttr;
}
//---------------------------------------------------------------------------
// https://msdn.microsoft.com/en-us/library/windows/desktop/aa365541(v=vs.85).aspx
//---------------------------------------------------------------------------
ulong File::setFilePointer(long  distanceToMove,
                           ulong moveMethod,
                           long* distanceToMoveHigh/* =0 */)
{
  ulong newFilePointer=
      SetFilePointer(handle_,
                     distanceToMove,
                     distanceToMoveHigh,
                     moveMethod);

  /* Последний аргумент moveMethod указывает,
     откуда будет начат отсчет, принимает значения:
     FILE_BEGIN - начало файла,
     FILE_CURRENT - с текущего значения,
     FILE_END - с конца файла.
   */

  if(distanceToMoveHigh)
  {
    ulong errorCode= GetLastError();
    if(newFilePointer==INVALID_SET_FILE_POINTER && errorCode != NO_ERROR)
       throw SystemException(errorCode);
  }
  else
  {
    if(newFilePointer==INVALID_SET_FILE_POINTER)
      throw SystemException();
  }
  return newFilePointer;
}
//---------------------------------------------------------------------------
__int64 File::seek(__int64 distance, ulong moveMethod)
{
   LARGE_INTEGER li;
   li.QuadPart = distance;
   li.LowPart = setFilePointer(li.LowPart, moveMethod, &li.HighPart);
   return li.QuadPart;
}
//---------------------------------------------------------------------------
void File::setEndOfFile()
{
  if(SetEndOfFile(handle_))
    throw SystemException();
}
//---------------------------------------------------------------------------

