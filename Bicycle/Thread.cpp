//---------------------------------------------------------------------------
#include "Thread.h"
//---------------------------------------------------------------------------
using namespace Bicycle;
//---------------------------------------------------------------------------
Thread::Thread()
  :autoDelete_(false),
   handle_(NULL),
   interrupted_(false)
{
}
//---------------------------------------------------------------------------
Thread::~Thread()
{
}
//---------------------------------------------------------------------------
ulong Thread::handle()const
{
  return handle_;
}
//---------------------------------------------------------------------------
void Thread::setAutoDelete(bool autoDelete)
{
  autoDelete_= autoDelete;
}
//---------------------------------------------------------------------------
bool Thread::autoDelete()const
{
  return  autoDelete_;
}
//---------------------------------------------------------------------------
void Thread::start()
{
  if(!handle_)
		handle_= _beginthread(&threadFunction,0,this);
}
//---------------------------------------------------------------------------
void Thread::requestInterruption()
{
  interrupted_= true;
}
//---------------------------------------------------------------------------
bool Thread::isInterruptionRequested() const
{
  return interrupted_ == TRUE;
}
//---------------------------------------------------------------------------
void Thread::threadFunction(void* params)
{
  Thread* self= reinterpret_cast<Thread*>(params);
  self->run();
  if(self->autoDelete()) // Автоматическое удаление объекта после выполнения потока
    delete self;
}
//---------------------------------------------------------------------------

