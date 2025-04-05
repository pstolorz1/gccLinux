#include <stdio.h>
#include <math.h>
#include <iostream>
#include <tbb/tbb.h>

using namespace std;

const int iXmax = 4096; 
const int iYmax = 4096;
const double CxMin=-2.5;
const double CxMax=1.5;
const double CyMin=-2.0;
const double CyMax=2.0;
double PixelWidth=(CxMax-CxMin)/iXmax;
double PixelHeight=(CyMax-CyMin)/iYmax;
const int MaxColorComponentValue=255; 
unsigned char image[iXmax][iYmax][3];
const int IterationMax=200;
const double EscapeRadius=2;
double ER2=EscapeRadius*EscapeRadius;
int iX, iY;
double Cx,Cy;
double Zx, Zy;
double Zx2, Zy2;
int Iteration;
 
void draw()
{
	static tbb::affinity_partitioner ap;
	tbb::parallel_for(tbb::blocked_range2d<size_t>(0, iXmax, 0, iYmax),
	[=](const tbb::blocked_range2d<size_t>& r){
	
		for(size_t iY = r.rows().begin(); iY != r.rows().end(); iY++)
		{
			Cy=CyMin + iY*PixelHeight;
			if (fabs(Cy)< PixelHeight/2) Cy=0.0;
			for(size_t iX = r.cols().begin(); iX != r.cols().end(); iX++)
			{         
				Cx=CxMin + iX*PixelWidth;
				Zx=0.0;
				Zy=0.0;
				Zx2=Zx*Zx;
				Zy2=Zy*Zy;
				for (Iteration=0;Iteration<IterationMax && ((Zx2+Zy2)<ER2);Iteration++)
				{
					Zy=2*Zx*Zy + Cy;
					Zx=Zx2-Zy2 +Cx;
					Zx2=Zx*Zx;
					Zy2=Zy*Zy;
				};
				if (Iteration==IterationMax)
				{ 
					image[iX][iY][0]=0;
					image[iX][iY][1]=0;
					image[iX][iY][2]=0;                           
				}
			 	else 
				{ 
					image[iX][iY][0]=255;
					image[iX][iY][1]=255;
					image[iX][iY][2]=255;
				};
			}
		}
		
		ap; });
}
 
int main()
{
	FILE * fp;
	char *filename="new1.ppm";
	char *comment="# ";
	fp= fopen(filename,"wb");
	fprintf(fp,"P6\n %s\n %d\n %d\n %d\n",comment,iXmax,iYmax,MaxColorComponentValue);

	tbb::tick_count t0 = tbb::tick_count::now();

	draw();
	
	tbb::tick_count t1 = tbb::tick_count::now();
	std::cout << "CZAS: "<< (t1-t0).seconds() << "s\n";

	for(int iY=0;iY<iYmax;iY++)
	{
		for(int iX=0;iX<iXmax;iX++)
		{         
			fwrite(image[iX][iY],1,3,fp);
		}
	}

	fclose(fp);
	return 0;
}

