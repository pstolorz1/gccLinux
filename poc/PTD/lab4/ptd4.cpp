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
			DFT[t] += (x[n] * cos(-kat), x[n] * sin(-kat));
		}
    }

	vector<double> M(fs*T);
	vector<double> M1(fs*T);
	for(int i = 0; i<fs*T/2; i++)
	{
		M[i]=sqrt(( pow(real(DFT[i]), 2) + pow(imag(DFT[i]), 2)));
		M1[i]=10*log10(M[i]);
	}
	plt::figure_size(1280*2, 720);
	plt::plot(M);
	plt::title("widmo");	
	plt::show();
}

void ASK(double A1, double A2, double fn, int t1, vector<double> m)
{
	std::vector<double> t(t1*100);
    std::vector<double> x(t.size());

    for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		if(m[t[i]]==0)
			x[i] = A1*sin(2*M_PI*fn*t[i]);
		else if(m[t[i]]==1)
			x[i] = A2*sin(2*M_PI*fn*t[i]);
    }

	plt::figure_size(1280*2, 720);
    plt::plot(t, x);
	plt::title("ASK");
    plt::show();
	DFT(x, t.size(), 1);
}

void FSK(double fn1, double fn2, int t1, vector<double> m)
{
	std::vector<double> t(t1*100);
    std::vector<double> x(t.size());

	for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		if(m[t[i]]==0)
			x[i] = sin(2*M_PI*fn1*t[i]);
		else if(m[t[i]]==1)
			x[i] = sin(2*M_PI*fn2*t[i]);
    }

	plt::figure_size(1280*2, 720);
    plt::plot(t, x);
	plt::title("FSK");
    plt::show();
	DFT(x, t.size(), 1);
}

void PSK(double fn, int t1, vector<double> m)
{
	std::vector<double> t(t1*100);
    std::vector<double> x(t.size());

	for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		if(m[t[i]]==0)
			x[i] = sin(2*M_PI*fn*t[i]);
		else if(m[t[i]]==1)
			x[i] = sin(2*M_PI*fn*t[i]+M_PI);
    }

	plt::figure_size(1280*2, 720);
    plt::plot(t, x);
	plt::title("PSK");
    plt::show();
	DFT(x, t.size(), 1);
}

int main() 
{
	srand(3);
	int t=20;
	int Tb=1;
	float A1 = 1;
	float A2 = 3;
	int N=2;
	float fn=N*pow(Tb, -1);
	float fn1 = (N+1)/Tb;
	float fn2 = (N+2)/Tb;
	vector<double> m(t);
	for(int i=0; i<t; i++)
	{
		m[i]=rand()%2;
	}
	ASK(A1, A2, fn, t, m);
	FSK(fn1, fn2, t, m);
	PSK(fn, t, m);
	return 0;
}
