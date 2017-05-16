//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UWorkThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
class TLogNotify: public TIdNotify
{
public:
	TLogNotify(const String& ALine,TStrings* ALog)
		:FLine(ALine),FLog(ALog)
	{
	}
protected:
	virtual void __fastcall DoNotify()
	{
		FLog->Add(FLine );
	}
private:
	String FLine;
	TStrings* FLog;
};
//---------------------------------------------------------------------------

__fastcall TWorkThread::TWorkThread(TRichEdit* ALog,
                                    bool CreateSuspended)
	: TThread(CreateSuspended),
	  FLog(ALog)
{
}
//---------------------------------------------------------------------------
void __fastcall TWorkThread::Execute()
{
	typedef AnsiStringT<866> OEMString;

	using namespace std;
	try
	{
		process.setShowWindow(SW_HIDE);
		process.setInheritHandle(true);
		process.setSecurityInheritHandle(true);
		process.usePipes(true);
		process.start(L"",L"ping google.com");
		process.stdOut().setTimeOut(30000);

		// Используем поток для чтения из пайпа построчно
		Bicycle::TextStream stream(&process.stdOut());
		while(!Terminated)
		{
			string line = stream.readLine();
			AddToLog( OEMString(line.c_str()) );
		}
	}
	catch(const Bicycle::Exception& e)
	{
		String Msg= e.message().c_str();
		AddToLog("["+Msg.Trim()+"]");
	}
}
//---------------------------------------------------------------------------
void __fastcall TWorkThread::AddToLog(const String& ALine)
{
	(new TLogNotify(ALine,FLog->Lines))->Notify();
}
//---------------------------------------------------------------------------
void __fastcall TWorkThread::Cancel()
{
	process.cancel();
	Terminate();
}
//---------------------------------------------------------------------------
