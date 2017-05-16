
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "UMainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner),
	 FWorkThread(0)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ButtonPingClick(TObject *Sender)
{
	if(!FWorkThread)
	{
		ButtonPing->Enabled= false;
   	ButtonCancel->Enabled= true;

		RichEditOutput->Clear();

		FWorkThread= new TWorkThread(RichEditOutput,true);
		FWorkThread->FreeOnTerminate= true;
		FWorkThread->OnTerminate= ThreadTerminate;
		FWorkThread->Start();
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ThreadTerminate(TObject *Sender)
{
	FWorkThread= 0;
	ButtonPing->Enabled= true;
	ButtonCancel->Enabled= false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ButtonCancelClick(TObject *Sender)
{
	if(FWorkThread)
	  FWorkThread->Cancel();
}
//---------------------------------------------------------------------------

