
#include "TextStream.h"

using namespace Bicycle;
//------------------------------------------------------------------------------
TextStream::TextStream(IODevice *device,Buffer::SizeType bufferSize)
  :device_(device),
   buffer_(bufferSize)
{
}
//------------------------------------------------------------------------------
TextStream::~TextStream()
{
}
//------------------------------------------------------------------------------
void TextStream::setDevice(IODevice *device)
{
  if(device_ != device)
  {
     device_= device;
     clear();
  }
}
//------------------------------------------------------------------------------
IODevice *TextStream::device()
{
  return device_;
}
//------------------------------------------------------------------------------
void TextStream::setBufferSize(Buffer::SizeType size)
{
  buffer_.resize(size);
}
//------------------------------------------------------------------------------
const Buffer::SizeType TextStream::bufferSize() const
{
  return buffer_.size();
}
//------------------------------------------------------------------------------
void TextStream::clear()
{
  buffer_.clear();
}
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
ulong TextStream::readData(char *outData, size_t size)
{
  bool success= false;
  ulong allLength= buffer_.readData(outData,size,&success);
  while(!success)
  {
    ulong length= device_->read(buffer_.putPtr(),buffer_.availableSpace());
    if(length==0)
      throw EOFException();

    buffer_.addToPutPos(length);
    allLength+= buffer_.readData(outData,size-allLength,&success);
  }
  return allLength;
}
//------------------------------------------------------------------------------
ulong TextStream::readString(std::string &outStr, ulong size)
{
  bool success= false;
  ulong allLength= buffer_.readString(outStr,size,&success);
  while(!success)
  {
    ulong length= device_->read(buffer_.putPtr(),
                                buffer_.availableSpace());
    if(length==0)
      throw EOFException();

    buffer_.addToPutPos(length);
    allLength+= buffer_.readString(outStr,size-allLength,&success);
  }
  return allLength;
}
//------------------------------------------------------------------------------
std::string TextStream::readString(ulong size)
{
  std::string str;
  readString(str,size);
  return str;
}
//------------------------------------------------------------------------------
ulong TextStream::readLine(std::string &line,
                           const std::string &delemiter)
{
  bool success= false;
  ulong allLength= buffer_.readLine(line, success, delemiter);
  while (!success)
  {
    ulong length= device_->read(buffer_.putPtr(),
                                buffer_.availableSpace());
    if(length==0)
      throw EOFException();

    buffer_.addToPutPos(length);
    allLength+= buffer_.readLine(line, success, delemiter);
  }
  return allLength;
}
//------------------------------------------------------------------------------
std::string TextStream::readLine(const std::string &delemiter)
{
  std::string line;
  readLine(line,delemiter);
  return line;
}
//------------------------------------ Write ------------------------------------
ulong TextStream::writeData(const char *data,
                          ulong size)
{
  return device_->write(data,size);
}
//------------------------------------------------------------------------------
ulong TextStream::writeString(const std::string &str)
{
  return writeData(str.data(),str.size());
}
//------------------------------------------------------------------------------
ulong TextStream::writeLine(const std::string &line,
                          const std::string &delemiter)
{
  return writeString(line+delemiter);
}
//------------------------------------------------------------------------------

