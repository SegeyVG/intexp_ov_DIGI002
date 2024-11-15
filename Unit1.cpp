//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <math.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

#define H 576
#define W 1100

int inH, inW;

struct rgb
{
  Byte b;
  Byte g;
  Byte r;
//  Byte a;
};
struct rgb32
{
  Byte b;
  Byte g;
  Byte r;
  Byte a;
};
Byte Mem1[H][W][3];
Byte Mem2[H][W][3];
Byte InMem[H][W][3];
Byte OutMem[H][W][3];
Byte TempMem[H][W][3];
int R1[1024];
int R2[1024];
double FI[1024];


TImage *InImage1;
TImage *InImage2;

  Graphics::TBitmap *inbmp1;
  Graphics::TBitmap *inbmp2;
  Graphics::TBitmap *showbmp_in;
  Graphics::TBitmap *showbmp_out;
  Graphics::TBitmap *tempbmp;
  Graphics::TBitmap *outbmp;

  AnsiString fname;


  int DinL, DinNum, DinD;
  int DinY= 50;
  int MetrMicNum,DiagLeft,DiagRight, GradStep, MetrMicRad;
  int Freq;
  int PointsX[2048];
  int PointsY[2048];
  int PointsFi0[2048];

  int PointsNum=0;

  int DiagFi[2048];
  int DiagLevel[2048];
  int DiagNum=0;

  int SignalOutBuf0[2048];
  int SignalOutBuf1[2048];

  int SpectrOutBuf0[2048];
  int SpectrOutBuf1[2048];

  int SpectrPorog;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
   inbmp1 = new Graphics::TBitmap;
   inbmp2 = new Graphics::TBitmap;
      showbmp_in = new Graphics::TBitmap;
   showbmp_out = new Graphics::TBitmap;
   outbmp = new Graphics::TBitmap;
   tempbmp = new Graphics::TBitmap;
   outbmp->Height=H;
   outbmp->Width=W;
   outbmp->PixelFormat=pf24bit;

   for(int i=0;i<H;i++)
   {
     struct rgb *ptr= (struct rgb*)outbmp->ScanLine[i];
     for(int j=0;j<W;j++)
     {
       ptr[j].r=128;
       ptr[j].g=128;
       ptr[j].b=128;

     }
   }
    Image1->Picture->Graphic=outbmp;

    for(int i=0;i<1024;i++)  {
     SpectrOutBuf0[i]=0;
     SpectrOutBuf1[i]=0;
    }

    ShowSignals();

}
//---------------------------------------------------------------------------
double x1[2048], x2[2048];
double Corr(int* x, int *y, int N)
{
  double E=0; int i; double s;
  for(i=0;i<N;i++)  E+=x[i]; E/=N;
  for(i=0;i<N;i++) x1[i]=x[i]-E;
  s=0; for(i=0;i<N;i++) s+= x1[i]*x1[i]; s/=N; s=sqrt(s);
  if(s==0) return 0;
  for(i=0;i<N;i++) x1[i]/=s;
  E=0;
  for(i=0;i<N;i++)  E+=y[i]; E/=N;
  for(i=0;i<N;i++) x2[i]=y[i]-E;
  s=0; for(i=0;i<N;i++) s+= x2[i]*x2[i]; s/=N; s=sqrt(s);
    if(s==0) return 0;
  for(i=0;i<N;i++) x2[i]/=s;

  double R=0;
  for(i=0;i<N;i++) R+= x1[i]*x2[i];   R/=N;

  return R;

}

int LeftPos=38;
int Spectr0PosY=272;
int Spectr1PosY=560;
int WinLinePosY=288;
int Oscill0PosY=144;
int Oscill1PosY=432;

void  TForm1::ShowSignals()
{
   struct rgb *ptr;
   int count=0;
   int Mode=0;
   if(SpectrView->Checked) Mode=1; else Mode=0;
// Очищаем экран
  for(int i=0;i<H;i++)
   {
     struct rgb *ptr= (struct rgb*)outbmp->ScanLine[i];
     for(int j=0;j<W;j++)
     {
       ptr[j].r=128;
       ptr[j].g=128;
       ptr[j].b=128;

     }
   }
// Линия раздела на области для входа и выхода
   ptr= (struct rgb*)outbmp->ScanLine[WinLinePosY];
     for(int j=0;j<W;j++)
     {
         ptr[j].r=255;
         ptr[j].g=255;
         ptr[j].b=255;
     }
     
  if(Mode==1) // Spectral Mode
  {

// Горизонтальная ось спектра входного сигнала
    ptr= (struct rgb*)outbmp->ScanLine[Spectr0PosY];
     for(int j=0;j<1024;j++)
     {
         ptr[LeftPos+j].r=0;
         ptr[LeftPos+j].g=255;
         ptr[LeftPos+j].b=255;
     }
// Вертикальная ось спектра входного сигнала
  for(int i=0;i<256;i++)
   {
     struct rgb *ptr= (struct rgb*)outbmp->ScanLine[Spectr0PosY-i];

       ptr[LeftPos].r=0;
       ptr[LeftPos].g=255;
       ptr[LeftPos].b=255;
   }
// Горизонтальная ось спектра выходного сигнала
    ptr= (struct rgb*)outbmp->ScanLine[Spectr1PosY];
     for(int j=0;j<1024;j++)
     {
         ptr[LeftPos+j].r=0;
         ptr[LeftPos+j].g=255;
         ptr[LeftPos+j].b=255;
     }
// Вертикальная ось спектра выходного сигнала
  for(int i=0;i<256;i++)
   {
     struct rgb *ptr= (struct rgb*)outbmp->ScanLine[Spectr1PosY-i];

       ptr[LeftPos].r=0;
       ptr[LeftPos].g=255;
       ptr[LeftPos].b=255;
   }
// Cпектр входного сигнала
   for(int j=0;j<1024;j++) {
     int n=SpectrOutBuf0[j];
     for(int i=0;i<n;i++)
     {
       struct rgb *ptr= (struct rgb*)outbmp->ScanLine[Spectr0PosY-i];

       ptr[LeftPos+j].r=255;
       ptr[LeftPos+j].g=255;
       ptr[LeftPos+j].b=255;
     }

   }
// Cпектр выходного сигнала
   for(int j=0;j<1024;j++) {
     int n=SpectrOutBuf1[j];
     int r,g,b;

     if(SpectrOutBuf1[j]<SpectrPorog)
     {
        r=255; g=255; b=255;
     }
     else
     {
        r=255; g=0; b=0;  count ++;
     }
     for(int i=0;i<n;i++)
     {
       struct rgb *ptr= (struct rgb*)outbmp->ScanLine[Spectr1PosY-i];

       ptr[LeftPos+j].r=r;
       ptr[LeftPos+j].g=g;
       ptr[LeftPos+j].b=b;
     }

   }

   HarmNumWin->Text=count;
   double seff=1024./count;
   char buf[128]; sprintf(buf,"%.1f",seff);
   SpectrEffWin->Text = buf;
   double FD=12000; // 10 HHz  Sampling
   double dW= FD/2048.;
   double dP=dW/11.1111; // 540 W/ 6000 MHz
   sprintf(buf,"%.1f",dP*count);
   PowerWin->Text = buf;
   sprintf(buf,"%.1f",dP*1024);
   Power0Win->Text=buf;
   double SR=Corr(SpectrOutBuf0,SpectrOutBuf1,1024);
   sprintf(buf,"%.3f",SR);
   SCorrWin->Text=buf;


  }
  else   // Oscill Mode
  {

// Горизонтальная ось входного сигнала
    ptr= (struct rgb*)outbmp->ScanLine[Oscill0PosY];
     for(int j=0;j<1024;j++)
     {
         ptr[LeftPos+j].r=0;
         ptr[LeftPos+j].g=255;
         ptr[LeftPos+j].b=255;
     }
// Вертикальная ось  входного сигнала
  for(int i=0;i<256;i++)
   {
     struct rgb *ptr= (struct rgb*)outbmp->ScanLine[Spectr0PosY-i];

       ptr[LeftPos].r=0;
       ptr[LeftPos].g=255;
       ptr[LeftPos].b=255;
   }
// Горизонтальная ось  выходного сигнала
    ptr= (struct rgb*)outbmp->ScanLine[Oscill1PosY];
     for(int j=0;j<1024;j++)
     {
         ptr[LeftPos+j].r=0;
         ptr[LeftPos+j].g=255;
         ptr[LeftPos+j].b=255;
     }
// Вертикальная ось  выходного сигнала
  for(int i=0;i<256;i++)
   {
     struct rgb *ptr= (struct rgb*)outbmp->ScanLine[Spectr1PosY-i];

       ptr[LeftPos].r=0;
       ptr[LeftPos].g=255;
       ptr[LeftPos].b=255;
   }
// Осциллограмма входного сигнала
   for(int j=0;j<128;j++) {
     int n=SignalOutBuf0[j];
       struct rgb *ptr= (struct rgb*)outbmp->ScanLine[Oscill0PosY-n];

       ptr[LeftPos+j*8].r=255;
       ptr[LeftPos+j*8].g=255;
       ptr[LeftPos+j*8].b=255;
   }
// Осциллограмма выходного сигнала
   for(int j=0;j<128;j++) {
     int n=SignalOutBuf1[j];

       struct rgb *ptr= (struct rgb*)outbmp->ScanLine[Oscill1PosY-n];

       ptr[LeftPos+j*8].r=255;
       ptr[LeftPos+j*8].g=255;
       ptr[LeftPos+j*8].b=255;
   }

  }
   double TR=Corr(SignalOutBuf0,SignalOutBuf1,1024);
   char buf[128];
   sprintf(buf,"%.3f",TR);
   TCorrWin->Text=buf;

    Image1->Picture->Graphic=outbmp; 
}

void __fastcall TForm1::OpenImage2Click(TObject *Sender)
{
   if(OpenPictureDialog1->Execute())
  {
   fname= OpenPictureDialog1->FileName;
  FILE *f=fopen(fname.c_str(),"r");
   if(f)
   {
    fclose(f);
    inbmp2->LoadFromFile(fname);

    inH=inbmp2->Height;
    inW=inbmp2->Width;

    for(int i=0;i<inH;i++)
    {
       struct rgb32 *ptr= (struct rgb32*)inbmp2->ScanLine[i];

      for(int j=0;j<inW;j++)
     {
      Mem2[i][j][0]=ptr[j].r;
      Mem2[i][j][1]=ptr[j].g;
      Mem2[i][j][2]=ptr[j].b;
     }
    }


 //   Image2->Picture->Graphic=inbmp2;
    }
  }
}
double XPos1, YPos1;
double XPos2, YPos2;
//---------------------------------------------------------------------------
float s_in[2048];
float s_out[2048];
float AmpSpe_in[2048];
float AmpSpe_out[2048];
float Re[2048];
float Im[2048];
int cod0[2048];
int cod1[2048];
float ds[2048];




void __fastcall TForm1::SaveResultClick(TObject *Sender)
{

  if(SaveDialog1->Execute())
  {
   fname= SaveDialog1->FileName;
  FILE *f=fopen(fname.c_str(),"w");
   if(f)
   {
    for(int i=0;i<1024;i++) fprintf(f,"%d\t%d\t%d\t%d\t%d\t%f\t%d\t%d\n",i,SignalOutBuf0[i],SignalOutBuf1[i],cod0[i],cod1[i],ds[i],SpectrOutBuf0[i],SpectrOutBuf1[i]);
    fclose(f);
   }
  }
}
//---------------------------------------------------------------------------


double ProcessLevel(int x1, int y1)
{

   double c=30000; // скорость свука см./с
   double dt=0.01/Freq; // 100 отсчетов на период
   double t,s,r;
   double sum=0;
   double e=0;
   double arg;
   for(int i=0;i<10000;i++) //100 периодов
   {
     sum=0;
     for(int j=0;j<PointsNum;j++)
     {
       int x2=PointsX[j]; int y2=PointsY[j];
        r=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
        t=r/c;
//         arg = 2*3.1415*(t+i*dt+PointsFi0[j])*Freq;
         arg = 2*3.1415*(t+i*dt)*Freq;
        s=sin(arg);
       sum+=s;
     }
     e+= sum*sum;
   }
   return(sqrt(e));
}





void  FFT(float *, float *, int, int, int);


void __fastcall TForm1::TestClick(TObject *Sender)
{
  int i; double Max=0;
    for(int i=0;i<1024;i++)  {
     SpectrOutBuf0[i]=0;
     SpectrOutBuf1[i]=0;
    }

   ProcSignals();

  for(i=0;i<2048;i++)  {
    Re[i]=s_in[i];
    Im[i]=0;
  }
   FFT(Re, Im, 2048, 11, -1);
   Max=0;
  for(i=0;i<2048;i++)  {
      AmpSpe_in[i]=sqrt(Re[i]*Re[i]+Im[i]*Im[i]);
      if(AmpSpe_in[i]>Max) Max=AmpSpe_in[i];
  }
  for(i=0;i<2048;i++)
  SpectrOutBuf0[i]=  255*AmpSpe_in[i]/Max;

  for(i=0;i<2048;i++)  {
    Re[i]=s_out[i];
    Im[i]=0;
  }
   FFT(Re, Im, 2048, 11, -1);
   Max=0;
  for(i=0;i<2048;i++)  {
      AmpSpe_out[i]=sqrt(Re[i]*Re[i]+Im[i]*Im[i]);
      if(AmpSpe_out[i]>Max) Max=AmpSpe_out[i];
  }
  for(i=0;i<2048;i++)
  SpectrOutBuf1[i]= 255*AmpSpe_out[i]/Max;
  double sigma=0;  for(i=0;i<2048;i++) sigma+= SpectrOutBuf1[i]; sigma/=2048;
  sigma = sqrt(sigma);
  SpectrPorog= SPorogWin->Text.ToInt()*sigma;

  ShowSignals();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OscilViewClick(TObject *Sender)
{
  ShowSignals();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpectrViewClick(TObject *Sender)
{
    ShowSignals();
}
//---------------------------------------------------------------------------
  double Amp[128];   double Fre[128];   double Fi[128];

double nois(double sigma)
{
  int i; double x=0; int M=12;

  for(i=0;i<M;i++) x+= (random(200)/100.-1);
  x /= M; x*=sqrt(12)/2; x*= sigma;
  return x;
}


void Process0()
{
  for(int i=0;i<2048;i++)  {
    if(s_in[i]>0) {
        s_out[i]= 1; cod0[i]=1; cod1[i]=0;
      }
      else{
          s_out[i]= -1; cod0[i]=-1; cod1[i]=0;
      }
  }
}

void Process1()
{
  int i;
// Кодирование
  for(i=0;i<2048;i++)  {
    if(s_in[i]>0) {
        cod0[i]= 1;
      }
      else{
          cod0[i]= -1;
      }
  }
  cod1[0]=0;
  for(i=1;i<2048;i++)  {
    if(s_in[i]>s_in[i-1]) {
        cod1[i]= 1;
      }
      else{
          cod1[i]= -1;
      }
  }

// Восстановление

  int i1, i2, m,n,j, k, count_L, count_R, L,R;
  int nullpoint[2048]; for(i=0;i<2048;i++) nullpoint[i]=0;
  double s= 0;
  double S1, S2, Q;
  for(i=0;i<2047;i++) {
    i1=i;
    for(i2=i1+1;i2<2048;i2++,i++)  if((cod0[i1]*cod0[i2])<0) break;
      L=i2-i1;
      if(L<2)
        { s_out[i1]=0; s=0;}
      if(L==3)
         { s_out[i1]=0; s=s_out[i1+1]=cod0[i1+1]; }
      if(L>3) {
        nullpoint[i2]=1;
        for(k=i1;k<i2;k++) {
            for(count_L=0;count_L<k; count_L++)  if((cod1[k-count_L]*cod1[k])<0) break;
            for(count_R=0;count_R<2048-k; count_R++)  if((cod1[k+count_R]*cod1[k])<0) break;
            R=(count_R>count_L)? count_L: count_R;
            ds[k]=R*cod1[k];
        }
        S1=S2=0;  double Amp;
        for(k=i1;k<i2;k++) {
          if(ds[k]>0) S1+= ds[k]; else S2+= ds[k];
        }
       if(S2!=0)  Q=-1*S1/S2;  else Q=1;
       Amp=sqrt(S1*(-1)*S2); if(Amp==0) Amp=1;     //???????
        for(k=i1;k<i2;k++) {
          if(ds[k]<0) {   ds[k]*=Q/Amp;}
          else        {  ds[k]/=Amp;  }
        }

        double S3=0; S1=0; S2=0;
        for(k=i1;k<i2;k++) {
          if(ds[k]>0) S1+= ds[k]; else S2+= ds[k];
          S3+= ds[k];
        }

        for(k=i1;k<i2;k++) {
          if(nullpoint[k]) s=ds[k];
          else s+= ds[k];
          s_out[k]=s;
        }

      }
    i1=i2;
  }
  int testcod[2048];   float diff[2048]; int difcode[2048];
  int WSize=3;
for(m=0;m<600;m++)
{
  for(i=0;i<2048;i++) {
    if(s_out[i]>0) {
        testcod[i]= 1;
      }
      else{
          testcod[i]= -1;
      }
  }
  for(i=0;i<2048;i++) {
     difcode[i]=cod0[i]-testcod[i];
  }
  int err=0; for(i=0;i<2048;i++) err+=abs(difcode[i]);
  for(i1=5;i1<2048;i1++) if(difcode[i1]!=0) break;

  if(err==0) break;

  for(i=0;i<2048;i++) {
    s=0; n=0;
    if(i==i1)
      n=0;
    for(k=i-WSize;k<=i+WSize;k++) {
     if((k>=0)&&(k<2048)) { n++; s+= difcode[k];}
    }
    s/=n; diff[i]=s;
  }


  int x1=s_out[i1];
  float x2=diff[i1];
  int x5=cod0[i1];
  int x3=testcod[i1];
  int x4=difcode[i1];

  for(i=0;i<2048;i++) {
   s_out[i]+=diff[i]/5000;
  }
  n=0;
}
}
void TForm1::ProcSignals()
{
  int i,j; float sMax=0;
  float s;
  int SinNum=SinNumWin->Text.ToInt();
  float MaxFre=MaxFreWin->Text.ToInt()/100.;
  int MaxAmp=MaxAmpWin->Text.ToInt();

  float NoisLev=NoisLevWin->Text.ToInt();

  if(NewSigCheck->Checked) {
     for(i=0;i<SinNum;i++) Amp[i]=random(100*(MaxAmp-1))/100.+1;
     for(i=0;i<SinNum;i++) Fre[i]=random(100*MaxFre)/100.;
     for(i=0;i<SinNum;i++) Fi[i]=random(200*3.14159265)/100.;
  }
  double s0=0;

  for(i=0;i<2048;i++)  {

    s=0;  for(j=0;j<SinNum;j++) s+= Amp[j]*cos(2* 3.14159265*i*Fre[j]/2+Fi[j]);
    s+= NoisLev*nois(1.);
    s_in[i]=s;
  }
   int mode=ProcSelBox->ItemIndex;
   switch(mode) {
     case 0:  Process0(); break;
     case 1:  Process1(); break;
   }
   

  sMax=0; for(i=0;i<1024;i++) {
   float a =  fabs(s_in[i]); if(a>sMax) sMax=a;
  }
  if(sMax>0) for(i=0;i<1024;i++) SignalOutBuf0[i]=127*s_in[i]/sMax;

  sMax=0; for(i=0;i<1024;i++) {
   float a =  fabs(s_out[i]); if(a>sMax) sMax=a;
  }
  if(sMax>0) for(i=0;i<1024;i++) SignalOutBuf1[i]=127*s_out[i]/sMax;


}

