//---------------------------------------------------------------------------
#ifndef UWorkThreadH
#define UWorkThreadH
//---------------------------------------------------------------------------
#include "Bicycle/Win/Process/Process.h"
#include "Bicycle/Win/Common/TextStream.h"
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
#include <IdSync.hpp>
//---------------------------------------------------------------------------
class TWorkThread : public TThread
{
private:
	 Bicycle::Process process;
	 TRichEdit* FLog;
protected:
	void __fastcall Execute();

	void __fastcall AddToLog(const String& ALine);
public:
	__fastcall TWorkThread(TRichEdit* ALog, bool CreateSuspended);

	void __fastcall Cancel();
};
//---------------------------------------------------------------------------
#endif
