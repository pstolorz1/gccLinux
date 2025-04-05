#include "matplotlibcpp.h"
#include <cmath>
#include <math.h>

namespace plt = matplotlibcpp;
using namespace std;

int main() 
{
	//ZAD 1 i ZAD 2
    int f=20;
    float fi=-2*M_PI;
    int fs=600;
    int T = 2;
    vector<float> x(fs*T), y(fs*T), z(fs*T), v(fs*T);
    for(int n=0; n<(fs*T); n++) 
	{
   		x[n] = (0.45/(n+20)) * cos(2*M_PI*f*(n*1.0/fs)+fi);
		y[n] = pow(2*x[n],2);
		z[n] = (2.0/3) * (sin(2*M_PI*7*(n*1.0/fs))*x[n] - 0.2*y[n]);
		v[n] = pow(x[n],(-1.0/0.2)) * (y[n] - 2.1*x[n]);
	}	
	plt::figure_size(1280, 720);
    plt::plot(x);
	plt::title("zad. 1 x(n)");
	plt::show();

	plt::figure_size(1280, 720);
    plt::plot(z);
	plt::title("zad. 2 z(n)");
	plt::show();

	plt::figure_size(1280, 720);
	plt::plot(v);
	plt::title("zad. 2 v(n)");
    plt::show();
	
	//ZAD 3
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
	plt::figure_size(1280, 720);
	plt::plot(u);
	plt::title("zad. 3 u(n)");
	plt::show();

	//ZAD 4
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

	plt::figure_size(1280, 720);
	plt::plot(g1);
	plt::title("zad. 4A g(t)");
	plt::show();

	plt::figure_size(1280, 720);
	plt::plot(g2);
	plt::title("zad. 4B g(t)");
	plt::show();

	plt::figure_size(1280, 720);
	plt::plot(g3);
	plt::title("zad. 4C g(t)");
	plt::show();
	return(0);
}