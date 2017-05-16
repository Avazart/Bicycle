#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef TextStreamH
#define TextStreamH
//---------------------------------------------------------------------------
#include "Win/Common/Global.h"
#include "Win/Common/Exception.h"
#include "Win/Common/NonCopyable.h"
#include "Win/Common/IODevice.h"
#include "Buffer.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class TextStream: private NonCopyable
{
public:
  explicit TextStream(IODevice* device,
                    Buffer::SizeType bufferSize= DEFAULT_BUFF_SIZE);
  virtual ~TextStream();

  void setDevice(IODevice* device);
  IODevice* device();
  void setBufferSize(Buffer::SizeType size);
  const Buffer::SizeType bufferSize() const;
  void clear();

  ulong readData(char* data, size_t size);        // throw EOFException if length==0

  ulong readString(std::string& str, ulong size); // throw EOFException
  std::string readString(ulong size);             // throw EOFException

  ulong readLine(std::string& line,
                 const std::string& delemiter=CRLF);      // throw EOFException
  std::string readLine(const std::string& delemiter=CRLF);// throw EOFException

  ulong writeData(const char* data, ulong size);

  ulong writeString(const std::string& str);

  ulong writeLine(const std::string& line,
                  const std::string& delemiter=CRLF);
private:
  IODevice* device_;
  Buffer buffer_;
};
//---------------------------------------------------------------------------
}

#endif // IOSTREAM_H
