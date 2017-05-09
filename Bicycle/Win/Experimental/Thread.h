//---------------------------------------------------------------------------
#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef ThreadH
#define ThreadH
//---------------------------------------------------------------------------
#include "Global.h"
#include "NonCopyable.h"
#include "Sync/AtomicCounter.h"

#include <process.h>
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
class Thread: private NonCopyable
{
public:
  Thread();
  virtual ~Thread();

  void start();

  ulong handle()const;

  void setAutoDelete(bool autoDelete);
  bool autoDelete()const;

  void requestInterruption();
  bool isInterruptionRequested() const;

protected:
  virtual void run()= 0;

private:
  static void threadFunction(void* params);

private:
  ulong  handle_;
  bool   autoDelete_;
  AtomicCounter interrupted_;
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
