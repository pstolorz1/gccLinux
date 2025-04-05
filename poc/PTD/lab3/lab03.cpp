#include "matplotlibcpp.h"
#include <cmath>
#include <math.h>
#include <complex>

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
	plt::figure_size(1280, 720);
	plt::plot(M);
	plt::title("wykres liniowy");	
	plt::show();

	plt::figure_size(1280, 720);
	plt::plot(M1);
	plt::title("wykres logarytmiczny");	
	plt::show();
}

int main() 
{
	int t=200;
	int fn=100;
	int fm=5;
	int fs=500;
	int Am=1;
	float ka=0.5;
	int kp=1;
	vector<double> m(t);

	//1	

	vector<double> za1(t), zp1(t);
	ka=0.5;
	kp=1;
    for(int n=0; n<t; n++) 
	{
   		m[n] = Am * sin(2*M_PI*fm*n/fs);
		za1[n] = (ka * m[n] + 1) * cos(2*M_PI*fn*n/fs);
		zp1[n] = cos(2*M_PI*fn*n/fs + kp*m[n]);
	}

	plt::figure_size(1280, 720);
    plt::plot(za1);
	plt::show();

	plt::figure_size(1280, 720);
	plt::plot(zp1);
    plt::show();

	//2

	vector<double> za2(t), zp2(t);
	ka=6;
	kp=2;
    for(int n=0; n<t; n++) 
	{
   		m[n] = Am * sin(2*M_PI*fm*n/fs);
		za2[n] = (ka * m[n] + 1) * cos(2*M_PI*fn*n/fs);
		zp2[n] = cos(2*M_PI*fn*n/fs + kp*m[n]);
	}

	plt::figure_size(1280, 720);
    plt::plot(za2);
	plt::show();

	plt::figure_size(1280, 720);
	plt::plot(zp2);
    plt::show();

	//3

	vector<double> za3(t), zp3(t);
	ka=30;
	kp=50;
    for(int n=0; n<t; n++) 
	{
   		m[n] = Am * sin(2*M_PI*fm*n/fs);
		za3[n] = (ka * m[n] + 1) * cos(2*M_PI*fn*n/fs);
		zp3[n] = cos(2*M_PI*fn*n/fs + kp*m[n]);
	}

	plt::figure_size(1280, 720);
    plt::plot(za3);
	plt::show();

	plt::figure_size(1280, 720);
	plt::plot(zp3);
    plt::show();
	
	DFT(za1, t, 1);
	DFT(zp1, t, 1);
	DFT(za2, t, 1);
	DFT(zp2, t, 1);
	DFT(za3, t, 1);
	DFT(zp3, t, 1);

	return 0;
}