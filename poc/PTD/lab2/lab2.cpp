#include "matplotlibcpp.h"
#include <cmath>
#include <math.h>
#include <complex>
#include <complex.h>
#include "kiss_fft.h"
#include <fftw3.h>
#include "FftComplex.hpp"
#include "fft.h"
#include <time.h>

namespace plt = matplotlibcpp;
using namespace std;

void DFT(vector<double>x, int fs, int T)
{
	vector<complex<double>> DFT(fs*T);
	for(int t=0; t<(fs*T); t++) 
	{
		for(int n=0; n<(fs*T); n++)
		{
			double kat = (2*M_PI*n*t) / (fs*T);
			DFT[t] += (x[t] * cos(-kat), x[t] * sin(-kat));
		}
    }

	vector<double> M(fs*T);
	vector<double> M1(fs*T);
	for(int i = 0; i<fs*T; i++)
	{
		M[i]=sqrt(( pow(real(DFT[i]), 2) + pow(imag(DFT[i]), 2)));
		M1[i]=10*log10(M[i]);
	}
	/*plt::figure_size(1280, 720);
	plt::plot(M);
	plt::title("wykres liniowy");	
	plt::show();

	plt::figure_size(1280, 720);
	plt::plot(M1);
	plt::title("wykres logarytmiczny");	
	plt::show();*/
}

void FFT(vector<double>x, int fs, int T)
{
	int N = fs*T;
	fftw_complex *in, *out;
	fftw_plan p;

	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
	p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

	fftw_execute(p); 

	//repeat as needed

	fftw_destroy_plan(p);
	fftw_free(in); fftw_free(out);
}

int main() 
{
	//ZAD 1 i ZAD 2

    int f=20;
    float fi=-2*M_PI;
    int fs=600;
    int T = 2;
    vector<double> x(fs*T), y(fs*T), z(fs*T), v(fs*T);
    for(int n=0; n<(fs*T); n++) 
	{
   		x[n] = (0.45/(n+20)) * cos(2*M_PI*f*(n*1.0/fs)+fi);
		y[n] = pow(2*x[n],2);
		z[n] = (2.0/3) * (sin(2*M_PI*7*(n*1.0/fs))*x[n] - 0.2*y[n]);
		v[n] = pow(x[n],(-1.0/0.2)) * (y[n] - 2.1*x[n]);
	}	

	clock_t begin, end;
    double time_spent;

	//WYKRES 1
	begin = clock();
	DFT(x, fs, T);
	end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("DFT1 = %f\n", time_spent);

	begin = clock();
	FFT(x, fs, T);
	end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("FFT1 = %f\n", time_spent);

	//WYKRES 2
	begin = clock();
	DFT(z, fs, T);
	end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("DFT2 = %f\n", time_spent);

	begin = clock();
	FFT(z, fs, T);
	end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("FFT2 = %f\n", time_spent);

	//WYKRES 3
	begin = clock();
	DFT(v, fs, T);
	end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("DFT3 = %f\n", time_spent);

	begin = clock();
	FFT(v, fs, T);
	end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("FFT3 = %f\n", time_spent);
	
	fs=7000;
	T=2;
	vector<double> u(fs*T);

	for(int n=0; n<2100; n++) 
	{
		float PI=3;
		u[n] = pow(n, 0.8)*sin(12*PI*n);
    }

	for(int n=2100; n < 4550; n++) 
	{
		u[n] = 1.2*n + log2(2*n);
    }
	
	for(int n=4550; n < (fs*T); n++) 
	{
		u[n] = pow(n, 0.662) + 0.1*sin(8*n);
    }

	//WYKRES 4
	begin = clock();
	DFT(u, fs, T);
	end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("FFT4 = %f\n", time_spent);

	begin = clock();
	FFT(u, fs, T);
	end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("DFT4 = %f\n", time_spent);

	fs=10000;
	T=1;
	vector<double> g1(fs*T);
	vector<double> g2(fs*T);
	vector<double> g3(fs*T);
	vector<double> temp1(fs*T);
	vector<double> temp2(fs*T);
	vector<double> temp3(fs*T);

	int H=2;
	for(int t=0; t<(fs*T); t++) 
	{
		for(int n=1; n<=H; n++)
		{
			temp1[t]+=cos(18.9*n*t);
		}
		g1[t] = 2/M_PI - (4/M_PI)*temp1[t];
    }

	H=20;
	for(int t=0; t<(fs*T); t++) 
	{
		for(int n=1; n<=H; n++)
		{
			temp2[t]+=cos(18.9*n*t);
		}
		g2[t] = 2/M_PI - (4/M_PI)*temp2[t];
    }

	H=80;
	for(int t=0; t<(fs*T); t++) 
	{
		for(int n=1; n<=H; n++)
		{
			temp3[t]+=cos(18.9*n*t);
		}
		g3[t] = 2/M_PI - (4/M_PI)*temp3[t];
    }

	//WYKRES 5
	begin = clock();
	DFT(g1, fs, T);
	end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("DFT5 = %f\n", time_spent);

	begin = clock();
	FFT(g1, fs, T);
	end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("FFT5 = %f\n", time_spent);

	//WYKRES 6
	begin = clock();
	DFT(g2, fs, T);
	end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("DFT6 = %f\n", time_spent);

	begin = clock();
	FFT(g2, fs, T);
	end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("DFT6 = %f\n", time_spent);

	//WYKRES 7
	begin = clock();
	DFT(g3, fs, T);
	end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("DFT7 = %f\n", time_spent);

	begin = clock();
	FFT(g3, fs, T);
	end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("DFT7 = %f\n", time_spent);


	
    return 0;
}