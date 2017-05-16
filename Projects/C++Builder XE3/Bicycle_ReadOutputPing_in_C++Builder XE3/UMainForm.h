//---------------------------------------------------------------------------

#ifndef UMainFormH
#define UMainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include "UWorkThread.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *PanelBottom;
	TButton *ButtonPing;
	TRichEdit *RichEditOutput;
	TButton *ButtonCancel;
	void __fastcall ButtonPingClick(TObject *Sender);
	void __fastcall ButtonCancelClick(TObject *Sender);
private:	// User declarations
	TWorkThread* FWorkThread;

	void __fastcall ThreadTerminate(TObject *Sender);

public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
