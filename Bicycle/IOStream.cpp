#include "IOStream.h"

using namespace Bicycle;
//------------------------------------------------------------------------------
IOStream::IOStream(IODevice *device,Buffer::SizeType bufferSize)
  :device_(device),
   buffer_(bufferSize)
{
}
//------------------------------------------------------------------------------
IOStream::~IOStream()
{
}
//------------------------------------------------------------------------------
void IOStream::setDevice(IODevice *device)
{
  if(device_ != device)
  {
     device_= device;
     clear();
  }
}
//------------------------------------------------------------------------------
IODevice *IOStream::device()
{
  return device_;
}
//------------------------------------------------------------------------------
void IOStream::setBufferSize(Buffer::SizeType size)
{
  buffer_.resize(size);
}
//------------------------------------------------------------------------------
const Buffer::SizeType IOStream::bufferSize() const
{
  return buffer_.size();
}
//------------------------------------------------------------------------------
void IOStream::clear()
{
  buffer_.clear();
}
//------------------------------------------------------------------------------
//
//             use error code
//
//------------------------------------ Read ------------------------------------
ulong IOStream::readData(char *outData, size_t size, ulong &errorCode)
{
  errorCode= 0;
  bool success= false;
  ulong allLength= buffer_.readData(outData,size,&success);
  while(!success && !errorCode)
  {
    ulong length= device_->read(buffer_.putPtr(),
                                buffer_.availableSpace(),
                                errorCode);
    buffer_.addToPutPos(length);
    allLength+= buffer_.readData(outData,size-allLength,&success);
  }
  return allLength;
}
//------------------------------------------------------------------------------
ulong IOStream::readString(std::string &outStr,ulong size, ulong &errorCode)
{
  errorCode= 0;
  bool success= false;
  ulong allLength= buffer_.readString(outStr,size,&success);
  while(!success && !errorCode)
  {
    ulong length= device_->read(buffer_.putPtr(),
                                buffer_.availableSpace(),
                                errorCode);
    buffer_.addToPutPos(length);
    allLength+= buffer_.readString(outStr,size-allLength,&success);
  }
  return allLength;
}
//------------------------------------------------------------------------------
ulong IOStream::readLine(std::string &line, ulong &errorCode,
                         const std::string &delemiter)
{
  errorCode= 0;
  bool success= false;
  ulong allLength= buffer_.readLine(line, success, delemiter);
  while (!success && !errorCode)
  {
    ulong length= device_->read(buffer_.putPtr(),
                                buffer_.availableSpace(),
                                errorCode);
    buffer_.addToPutPos(length);
    allLength+= buffer_.readLine(line, success, delemiter);
  }
  return allLength;
}
//------------------------------------ Write ------------------------------------
ulong IOStream::writeData(const char *data,
                          ulong size,
                          ulong &errorCode)
{
  return device_->write(data,size,errorCode);
}
//------------------------------------------------------------------------------
ulong IOStream::writeString(const std::string &str,
                            ulong &errorCode)
{
  return writeData(str.data(),str.size(),errorCode);
}
//------------------------------------------------------------------------------
ulong IOStream::writeLine(const std::string &line,
                          ulong &errorCode,
                          const std::string &delemiter)
{
  return writeString(line+delemiter,errorCode);
}
//------------------------------------------------------------------------------
//
//             use exception
//
//---------------------------------------------------------------------------
std::string IOStream::readStr(ulong size,
                              ulong* errorCode)
{
  std::string str;
  ulong error;
  readString(str,size,error);
  if(errorCode)
    *errorCode= error;
  else
    device_->checkErrorCode(error);
  return str;
}
//---------------------------------------------------------------------------
std::string IOStream::readLn(const std::string& delemiter,
                             ulong* errorCode)
{
  std::string line;
  ulong error;
  readLine(line,error,delemiter);
  if(errorCode)
    *errorCode= error;
  else
    device_->checkErrorCode(error);
  return line;
}
//---------------------------------------------------------------------------
std::string IOStream::readLn(ulong* errorCode,
                             const std::string& delemiter)
{
  return readLn(delemiter,errorCode);
}
//---------------------------------------------------------------------------
ulong IOStream::writeStr(const std::string& str,
                         ulong* errorCode)
{
  ulong error;
  ulong length= writeString(str,error);
  if(errorCode)
    *errorCode= error;
  else
    device_->checkErrorCode(error);
  return length;
}
//---------------------------------------------------------------------------
ulong IOStream::writeLn(const std::string& line,
                        const std::string& delemiter,
                        ulong* errorCode)
{
  ulong error;
  ulong length= writeLine(line,error,delemiter);
  if(errorCode)
    *errorCode= error;
  else
    device_->checkErrorCode(error);
  return length;
}
//---------------------------------------------------------------------------
ulong IOStream::writeLn(const std::string& line,
                        ulong* errorCode,
                        const std::string& delemiter)
{
  return writeLn(line, delemiter, errorCode);
}
//---------------------------------------------------------------------------

