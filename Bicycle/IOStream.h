#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef IOStreamH
#define IOStreamH
//---------------------------------------------------------------------------
#include "Global.h"
#include "NonCopyable.h"
#include "IODevice.h"
#include "Buffer.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
class IOStream: private NonCopyable
{
public:
  IOStream(IODevice* device,
           Buffer::SizeType bufferSize= DEFAULT_BUFF_SIZE);
  virtual ~IOStream();

  void setDevice(IODevice* device);
  IODevice* device();
  void setBufferSize(Buffer::SizeType size);
  const Buffer::SizeType bufferSize() const;
  void clear();

  // use error code:

  ulong readData(char* data, size_t size, ulong& errorCode);
  ulong readString(std::string& str, ulong size, ulong& errorCode);
  ulong readLine(std::string& line,
                 ulong& errorCode,
                 const std::string& delemiter=CRLF);

  ulong writeData(const char* data, ulong size, ulong& errorCode);
  ulong writeString(const std::string& str, ulong& errorCode);
  ulong writeLine(const std::string& line,
                  ulong& errorCode,
                  const std::string& delemiter=CRLF);

  // use exception:

  std::string readStr(ulong size, ulong* errorCode=0);
  std::string readLn(const std::string& delemiter=CRLF,ulong* errorCode=0);
  std::string readLn(ulong* errorCode,const std::string& delemiter=CRLF);

  ulong writeStr(const std::string& str, ulong* errorCode=0);
  ulong writeLn(const std::string& line,
                const std::string& delemiter=CRLF,
                ulong* errorCode=0);
  ulong writeLn(const std::string& line,
                ulong* errorCode,
                const std::string& delemiter=CRLF);
private:
  IODevice* device_;
  Buffer buffer_;
};
//---------------------------------------------------------------------------
}

#endif // IOSTREAM_H
