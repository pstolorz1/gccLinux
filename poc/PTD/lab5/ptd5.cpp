#include "matplotlibcpp.h"
#include <cmath>
#include <cstdio>
#include <math.h>
#include <complex>

namespace plt = matplotlibcpp;
using namespace std;

void ASK(double A1, double A2, double fn, int t1, vector<double> m)
{
	std::vector<double> t(t1*100);
    std::vector<double> x(t.size());
	std::vector<double> za(t.size());
	std::vector<double> z(t.size());
	std::vector<double> p(t.size());
	std::vector<double> m1(t.size());
	int n;
	n=-1;

    for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		if(m[t[i]]==0)
			x[i] = A1*sin(2*M_PI*fn*t[i]);
		else if(m[t[i]]==1)
			x[i] = A2*sin(2*M_PI*fn*t[i]);
    }

	for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		za[i] = A2*sin(2*M_PI*fn*t[i]);
    }

	for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		z[i] = x[i]*za[i];
    }

	for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		//zamiast calki moze byc suma
		p[i] = z[i] + p[i-1];
		if(i%100==0)
			p[i]=0;
    }

	for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		if(i%100==0)
			n=n+100;

		if(p[n]<100)
			m1[i]=0;
		else if(p[n]>200)
			m1[i]=1;
    }

	plt::figure_size(1280*2, 720);
    plt::plot(t, x);
	plt::title("ASK za(t)");
	plt::show();

	plt::figure_size(1280*2, 720);
	plt::plot(t, z);
	plt::title("ASK x(t)");
    plt::show();
	plt::figure_size(1280*2, 720);
	plt::plot(p);
	plt::title("ASK p(t)");
    plt::show();
	plt::figure_size(1280*2, 720);
	plt::plot(t, m1);
	plt::title("ASK m(t)");
    plt::show();
}

void PSK(double fn, int t1, vector<double> m)
{
	std::vector<double> t(t1*100);
    std::vector<double> x(t.size());
	std::vector<double> za(t.size());
	std::vector<double> z(t.size());
	std::vector<double> p(t.size());
	std::vector<double> m1(t.size());
	int n;
	n=-1;

	for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		if(m[t[i]]==0)
			x[i] = sin(2*M_PI*fn*t[i]);
		else if(m[t[i]]==1)
			x[i] = sin(2*M_PI*fn*t[i]+M_PI);
    }

	for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		za[i] = sin(2*M_PI*fn*t[i]+M_PI);
    }

	for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		z[i] = x[i]*za[i];
    }

	for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		//zamiast calki moze byc suma
		p[i] = z[i] + p[i-1];
		if(i%100==0)
			p[i]=0;
    }

	for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		if(i%100==0)
			n=n+100;
		if(p[n]<-40)
			m1[i]=0;
		else if(p[n]>40)
			m1[i]=1;
    }
	plt::figure_size(1280*2, 720);
    plt::plot(t, x);
	plt::title("PSK zp(t)");
	plt::show();
	plt::figure_size(1280*2, 720);
	plt::plot(t, z);
	plt::title("PSK x(t)");
    plt::show();
	plt::figure_size(1280*2, 720);
	plt::plot(p);
	plt::title("PSK p(t)");
    plt::show();
	plt::figure_size(1280*2, 720);
	plt::plot(t, m1);
	plt::title("PSK m(t)");
    plt::show();
}

void FSK(double fn1, double fn2, int t1, vector<double> m)
{
	std::vector<double> t(t1*100);
    std::vector<double> x(t.size());
	std::vector<double> zf1(t.size());
	std::vector<double> zf2(t.size());
	std::vector<double> z1(t.size());
	std::vector<double> z2(t.size());
	std::vector<double> p(t.size());
	std::vector<double> p1(t.size());
	std::vector<double> p2(t.size());
	std::vector<double> m1(t.size());
	int n;
	n=-1;

	for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		if(m[t[i]]==0)
			x[i] = sin(2*M_PI*fn1*t[i]);
		else if(m[t[i]]==1)
			x[i] = sin(2*M_PI*fn2*t[i]);
    }

	for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		zf1[i] = sin(2*M_PI*fn1*t[i]);
    }

	for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		z1[i] = x[i]*zf1[i];
    }

	for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		zf2[i] = sin(2*M_PI*fn2*t[i]);
    }

	for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		z2[i] = x[i]*zf2[i];
    }

	for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		//zamiast calki moze byc suma
		p1[i] = z1[i] + p1[i-1];
		if(i%100==0)
			p1[i]=0;
    }

	for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		//zamiast calki moze byc suma
		p2[i] = z2[i] + p2[i-1];
		if(i%100==0)
			p2[i]=0;
    }

	for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		p[i] = p1[i] - p2[i];
    }

	for(size_t i = 0; i < t.size(); i++) 
	{
		t[i] = i / 100.0;
		if(i%100==0)
			n=n+100;
		if(p[n]<-40)
			m1[i]=1;
		else if(p[n]>40)
			m1[i]=0;
    }

	plt::figure_size(1280*2, 720);
    plt::plot(t, x);
	plt::title("PSK zf(t)");
	plt::show();

	plt::figure_size(1280*2, 720);
	plt::plot(t, z1);
	plt::title("PSK x1(t)");
    plt::show();

	plt::figure_size(1280*2, 720);
	plt::plot(t, z2);
	plt::title("PSK x2(t)");
    plt::show();

	plt::figure_size(1280*2, 720);
	plt::plot(p);
	plt::title("PSK p(t)");
    plt::show();

	plt::figure_size(1280*2, 720);
	plt::plot(t, m1);
	plt::title("PSK m(t)");
    plt::show();
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
	PSK(fn, t, m);
	FSK(fn1, fn2, t, m);

	return 0;
}
