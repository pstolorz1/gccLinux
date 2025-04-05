/* 
c program:
--------------------------------
1. draws Mandelbrot set for Fc(z)=z*z +c
using Mandelbrot algorithm ( boolean escape time )
-------------------------------         
2. technique of creating ppm file is  based on the code of Claudio Rocchini
http://en.wikipedia.org/wiki/Image:Color_complex_plot.jpg
create 24 bit color graphic file ,  portable pixmap file = PPM 
see http://en.wikipedia.org/wiki/Portable_pixmap
to see the file use external application ( graphic viewer)
*/

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

const int iXmax = 8192; 
const int iYmax = 8192;

const double CxMin=-2.5;
const double CxMax=1.5;
const double CyMin=-2.0;
const double CyMax=2.0;

double PixelWidth=(CxMax-CxMin)/iXmax;
double PixelHeight=(CyMax-CyMin)/iYmax;
/* color component ( R or G or B) is coded from 0 to 255 */
/* it is 24 bit color RGB file */
const int MaxColorComponentValue=255; 

unsigned char color[iXmax][iYmax][3];
unsigned char color_theme[][3] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {127, 127, 127}};

const int IterationMax=200;
/* bail-out value , radius of circle ;  */
const double EscapeRadius=2;
double ER2=EscapeRadius*EscapeRadius;

 
void draw_fractal(int start, int end, int thread)
{
	/* screen ( integer) coordinate */
	int iX, iY;
	/* world ( double) coordinate = parameter plane*/
	double Cx,Cy;

	/* Z=Zx+Zy*i  ;   Z0 = 0 */
	double Zx, Zy;
	double Zx2, Zy2; /* Zx2=Zx*Zx;  Zy2=Zy*Zy  */
	/*  */
	int Iteration;

	for(iY=start;iY<end;iY++)
	{
		Cy=CyMin + iY*PixelHeight;
		if (fabs(Cy)< PixelHeight/2) Cy=0.0; /* Main antenna */
		for(iX=0;iX<iXmax;iX++)
		{         
			Cx=CxMin + iX*PixelWidth;
			/* initial value of orbit = critical point Z= 0 */
			Zx=0.0;
			Zy=0.0;
			Zx2=Zx*Zx;
			Zy2=Zy*Zy;
			/* */
			for (Iteration=0;Iteration<IterationMax && ((Zx2+Zy2)<ER2);Iteration++)
			{
				Zy=2*Zx*Zy + Cy;
				Zx=Zx2-Zy2 +Cx;
				Zx2=Zx*Zx;
				Zy2=Zy*Zy;
			};
			/* compute  pixel color (24 bit = 3 bytes) */
			if (Iteration==IterationMax)
			{ 
				/* interior of Mandelbrot set = black */
				color[iX][iY][0]=0;
				color[iX][iY][1]=0;
				color[iX][iY][2]=0;                           
			}
		 	else 
			{ 
				/* exterior of Mandelbrot set = white */
				color[iX][iY][0]=color_theme[thread][0]; /* Red */
				color[iX][iY][1]=color_theme[thread][1]; /* Green */ 
				color[iX][iY][2]=color_theme[thread][2]; /* Blue */
			};
		}
	}
}
 
int main()
{
	FILE * fp;
	char *filename="new1.ppm";
	char *comment="# ";/* comment should start with # */
	
	/*create new file,give it a name and open it in binary mode  */
	fp= fopen(filename,"wb"); /* b -  binary mode */
	/*write ASCII header to the file*/
	fprintf(fp,"P6\n %s\n %d\n %d\n %d\n",comment,iXmax,iYmax,MaxColorComponentValue);
	/* compute and write image data bytes to the file*/

	auto start = std::chrono::steady_clock::now();

	const int threads = 4; // max 4
	thread threadObj[threads];
	
	int part = iYmax/threads;

	for(int i = 0; i < threads; i++)
	{
		int start = i * part;
		int end = start + part;
		threadObj[i] = thread(draw_fractal, start, end, i);
	}

	for(int i = 0; i < threads; i++)
	{
		threadObj[i].join();
	}

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "CZAS: "<< elapsed_seconds.count() << "s\n";

	for(int iY=0;iY<iYmax;iY++)
	{
		for(int iX=0;iX<iXmax;iX++)
		{         
			//write color to the file
			fwrite(color[iX][iY],1,3,fp);
		}
	}

	fclose(fp);
	return 0;
}

