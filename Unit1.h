//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TOpenPictureDialog *OpenPictureDialog1;
        TSaveDialog *SaveDialog1;
        TButton *SaveResult;
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TEdit *SinNumWin;
        TGroupBox *GroupBox3;
        TEdit *MaxFreWin;
        TGroupBox *GroupBox4;
        TEdit *MaxAmpWin;
        TButton *Test;
        TRadioButton *OscilView;
        TRadioButton *SpectrView;
        TGroupBox *GroupBox5;
        TEdit *NoisLevWin;
        TCheckBox *NewSigCheck;
        TGroupBox *GroupBox6;
        TEdit *SPorogWin;
        TGroupBox *GroupBox7;
        TEdit *HarmNumWin;
        TGroupBox *GroupBox8;
        TEdit *SpectrEffWin;
        TGroupBox *GroupBox9;
        TEdit *PowerWin;
        TEdit *Power0Win;
        TGroupBox *GroupBox10;
        TComboBox *ProcSelBox;
        TGroupBox *GroupBox11;
        TEdit *SCorrWin;
        TEdit *TCorrWin;
        TLabel *Label1;
        TLabel *Label2;
        void __fastcall OpenImage2Click(TObject *Sender);
        void __fastcall SaveResultClick(TObject *Sender);
        void __fastcall TestClick(TObject *Sender);
        void __fastcall OscilViewClick(TObject *Sender);
        void __fastcall SpectrViewClick(TObject *Sender);

        
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
         void ShowSignals();
         void ProcSignals();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
