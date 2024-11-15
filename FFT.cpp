//-----------------------------------------------------------------
//
//-----------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <alloc.h>
#include <math.h>

//void  coef(float *Rcoef, float *Icoef, int M);
//void  fft (float *Rdat, float *Idat,
//	   float *Rcoef,float *Icoef, int M, int N, int Key);

void  FFT(float *, float *, int, int, int);

void  Get_Power_spectrum(float *Rdat, float *Idat, float *Power, int N);

void  Count_modul_phaze(float *Rdat, float *Idat,
			float *Modul,float *Phaze, int N);
void  Count_real_imag(float *Modul,float *Phaze,
		      float *Rdat, float *Idat, int N);

void   Set_data(float *Rdat, float *Idat, int N, char Key);
void  Comp(float *R1, float *R2, float *I1, float *I2, int N);
void  Round(float *Arr, int N, int K);



int xm, ym;

#define POINTS  32

/*
void main()
{
   int    i, Log;
   static float Rcoef[32], Icoef[32], *R1, *I1, *R2, *I2;

   R1 = (float *) farcalloc(POINTS, sizeof(float));
   R2 = (float *) farcalloc(POINTS, sizeof(float));
   I1 = (float *) farcalloc(POINTS, sizeof(float));
   I2 = (float *) farcalloc(POINTS, sizeof(float));
   if((R1==0)||(R2==0)||(I1==0)||(I2==0))
(  {puts("MEMORY!!!"); putchar(7); return;}

puts(" Log Coef");
   for(Log=0, i=1; i<POINTS; i*=2, Log++);
   coef(Rcoef, Icoef, 30);

puts(" Set Data");
   Set_data(R1, I1, POINTS, 'n');
   Set_data(R2, I2, POINTS, 'n');

puts(" FFT     ");
   fft(R1, I1, Rcoef, Icoef, Log, POINTS, -1);
puts(" D_FFT   ");
   FFT(R2, I2, POINTS, Log, -1);

   puts("\n\n\n\n");
   for(i=0; i<POINTS; i++)
   printf("%10.7f   %10.7f   %10.7f   %10.7f\n", R1[i], R2[i], I1[i], I2[i]);
   puts("-------------------------------------------------\n");

   Comp(R1, R2, I1, I2, POINTS);
   getch();


}
*/

//=======================================================================
//	Fast Fourier Transform - Быстрое преобразование Фурье
//-----------------------------------------------------------------------
//	Rdat - Действительная часть сигнала (или спектра)
//	Idat - Мнимая         часть сигнала (или спектра)
//      N    - Размер массивов  Rdat  и  Idat
//      M    - Двоичный логарифм размера N
//	Key  - Ключ: Key = -1 - прямое FFT, Key = 1 - обратное FFT
//=======================================================================
//	ВНИМАНИЕ!!!   N  и  M  могут принимать значения только :
//  N=  4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384;
//  M=  2, 3,  4,  5,  6,   7,   8,   9,   10,   11,   12,   13,    14;
//=======================================================================
void  FFT(float *Rdat, float *Idat, int N, int M, int Key)
{
   unsigned int  i, j, n, k, io, ie, in, nn;
   float         ru, iu, rtp, itp, rtq, itq, rw, iw, sr;

   static float Rcoef[14] =
   { -1.0000000000000000,  0.0000000000000000,  0.7071067811865475,
      0.9238795325112867,  0.9807852804032304,  0.9951847266721969,
      0.9987954562051724,  0.9996988186962042,  0.9999247018391445,
      0.9999811752826011,  0.9999952938095761,  0.9999988234517018,
      0.9999997058628822,  0.9999999264657178};

   static float Icoef[14] =
   {  0.0000000000000001, -1.0000000000000000, -0.7071067811865474,
     -0.3826834323650897, -0.1950903220161282, -0.0980171403295606,
     -0.0490676743274180, -0.0245412285229122, -0.0122715382857199,
     -0.0061358846491544, -0.0030679567629659, -0.0015339801862847,
     -0.0007669903187427, -0.0003834951875714};

   nn = N / 2;
   ie = N;
   for(n=1; n<=M; n++)
   {
      in = ie / 2;
      ru = 1.;
      iu = 0.;
      for(j=0; j<in; j++)
      {
	 for(i=j; i<N; i+=ie)
	 {
	    io  = i + in;
	    rtp = Rdat[i] + Rdat[io];
	    itp = Idat[i] + Idat[io];
	    rtq = Rdat[i] - Rdat[io];
	    itq = Idat[i] - Idat[io];
	    Rdat[io] = rtq * ru - itq * iu;
	    Idat[io] = itq * ru + rtq * iu;
	    Rdat[i]  = rtp;
	    Idat[i]  = itp;
	 }
	 rw = Rcoef[M-n];
	 iw = Icoef[M-n];
	 if(Key == 1) iw = -iw;
	 sr = ru;
	 ru = ru * rw - iu * iw;
	 iu = iu * rw + sr * iw;
      }
      ie = ie / 2;
   }
   for(j=i=1; i<N; i++)
   {
      io = i - 1;
      in = j - 1;
      if(i < j)
      {
	 rtp      = Rdat[in];
	 itp      = Idat[in];
	 Rdat[in] = Rdat[io];
	 Idat[in] = Idat[io];
	 Rdat[io] = rtp;
	 Idat[io] = itp;
      }
      k = nn;
      while(k < j)
      {
	 j = j - k;
	 k = k / 2;
      }
      j = j + k;
   }
   if(Key == 1) return;
   for(i=0; i<N; i++)
   {
      Rdat[i] = Rdat[i] / N;
      Idat[i] = Idat[i] / N;
   }
}


//================================================================


void  coef(float *Rcoef, float *Icoef, int M )
{
   float z;
   int    i;

   for(z=3.14159265358979323846, i=0; i<M; i++)
   {
      Rcoef[i] =  cos(z);
      Icoef[i] = -sin(z);
      z /= 2.;
   }
}



void  fft(float *Rdat, float *Idat, float *Rcoef,
			 float *Icoef,
			 int M, int N, int Key )
{
	unsigned int i, j, l, io, ie, in, nn, k;
	float ru, iu, rtp, itp, rtq, itq, rw, iw, sr;

	nn = N / 2;
	ie = N * 2;
	for(l=1; l<=M; l++)
	 { ie = ie / 2;
		 in = ie / 2;
		 ru = 1.;
		 iu = 0.;
		 for(j=0; j<in; j++)
      {
			 for(i=j; i<N; i+=ie)
	 {
	   io  = i + in;
		 rtp = Rdat[i] + Rdat[io];
	   itp = Idat[i] + Idat[io];
	   rtq = Rdat[i] - Rdat[io];
		 itq = Idat[i] - Idat[io];
	   Rdat[io] = rtq * ru - itq * iu;
	   Idat[io] = itq * ru + rtq * iu;
	   Rdat[i]  = rtp;
	   Idat[i]  = itp;
	 }
	rw = Rcoef[M-l];
	iw = Icoef[M-l];
	if(Key == 1) iw = -iw;
	sr = ru;
	ru = ru * rw - iu * iw;
	iu = iu * rw + sr * iw;
      }
   }
	 j = 1;
   for(i=1; i<N; i++)
    { if(i < j)
			 { rtp     = Rdat[j-1];
	 itp     = Idat[j-1];
	 Rdat[j-1] = Rdat[i-1];
	 Idat[j-1] = Idat[i-1];
	 Rdat[i-1] = rtp;
	 Idat[i-1] = itp;
       }
      k = nn;
      while(k < j)
       { j = j - k;
				 k = k / 2;
			 }
      j = j + k;
    }
   if(Key == 1)return;
   for(i=0; i<N; i++)
    { Rdat[i] = Rdat[i] / N;
			Idat[i] = Idat[i] / N;
    }
   return;
}

//================================================================


void Get_Power_spectrum(float *Rdat, float *Idat, float *Power, int N)
{
   int i, j;

   for(j=N/2, i=0; i<j; i++)
       Power[i] = Rdat[i] * Rdat[i] + Idat[i] * Idat[i];
}

//----------------------------------------------------------------
void  Count_modul_phaze(float *Rdat, float *Idat,
			float *Modul,float *Phaze, int N)
{
   void Mod_ph(float r, float i, float *m, float *p);

   int i;
   for(i=0; i<N; i++) Mod_ph(Rdat[i], Idat[i], &(Modul[i]), &(Phaze[i]));
}
//----------------------------------------------------------------

void  Count_real_imag(float *Modul,float *Phaze,
		      float *Rdat, float *Idat, int N)
{
   void  Rea_im(float m, float p, float *r, float *i);
   int i;
   for(i=0; i<N; i++) Rea_im(Modul[i], Phaze[i], &(Rdat[i]), &(Idat[i]));
}

void Rea_im(float m, float p, float *r, float *i)
{
   *r = m * cos(p);
   *i = m * sin(p);
}

void Mod_ph(float r, float i, float *m, float *p)
{
   float x;

   *m = sqrt(r * r + i * i);

   if(r == 0.0)
   {
      if(i == 0.0)     *p = 0.;
      else if(i > 0.0) *p =  3.141592653589793 / 2;
      else             *p = -3.141592653589793 / 2;
      return;
   }

   x = atan(i / r);

   if(r > 0.0){ *p = x; return; }

   if(i > 0.0) *p =  3.141592653589793 + x;
   else        *p = -3.141592653589793 + x;
}

void   Set_data(float *Rdat, float *Idat, int N, char Key)
{
   static char c;
   static float *R, *I;
   float pi;
   int i;

   pi = 3.141592653589793 / 4;
   if(c == 0)
   {

   R = (float *) farcalloc(POINTS, sizeof(float));
   I = (float *) farcalloc(POINTS, sizeof(float));
   if((R==0)||(I==0))
   {puts("MEMORY!!!"); putchar(7); exit(0);}

      for(i=0; i<N; i++)
      {
	 if(Key == 'n')
	 {
	    Rdat[i] = R[i] = (float)rand()/RAND_MAX;
	    Idat[i] = I[i] = (float)rand()/RAND_MAX;
	 }
	 else
	 {
	    Rdat[i] = R[i] = sin(pi * i);
	    Idat[i] = I[i] = 0.;
	 }
      }
      c = 1;
   }
   else
   {
      for(i=0; i<N; i++)
      {
	 Rdat[i] = R[i];
	 Idat[i] = I[i];
      }
   }
}

void  Comp(float *R1, float *R2, float *I1, float *I2, int N)
{
   int i;

   Round(R1, N, 5);
   Round(R2, N, 5);
   Round(I1, N, 5);
   Round(I2, N, 5);

   for(i=0; i<N; i++)
   {
      if(   (R1[i] != R2[i]) || (I1[i] != I2[i])    )
      {
	 puts("BAD LUCK !!!\n");
	 putchar(7);
	 return;
      }
   }

   puts("\n               ======   OK   ======\n");
   return;
}

void Round(float *Arr, int N, int K)
{
   int  i;
   long k;

   k = (int)pow(10., (float)K);
   for(i=0; i<N; i++)
   {
     Arr[i] = (int)(Arr[i] * k);
     Arr[i] /= k;
   }
}
 