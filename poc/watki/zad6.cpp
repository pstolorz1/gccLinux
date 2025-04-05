 #include <stdio.h>
 #include <math.h>
 #include <fstream>
 #include <thread>
 #include <chrono>
 #include <mutex>
 #include <iostream>
 #include <omp.h>

 #define MAX_THREAD 4

 using namespace std;

 const int iXmax = 8192;
 const int iYmax = 8192;
 /* world ( double) coordinate = parameter plane*/
 double Cx,Cy;
 const double CxMin=-2.5;
 const double CxMax=1.5;
 const double CyMin=-2.0;
 const double CyMax=2.0;
 /* */
 double PixelWidth=(CxMax-CxMin)/iXmax;
 double PixelHeight=(CyMax-CyMin)/iYmax;
 /* color component ( R or G or B) is coded from 0 to 255 */
 /* it is 24 bit color RGB file */
 const int MaxColorComponentValue=255;

 unsigned char color[iYmax][iXmax][3];
 //unsigned char color[800][800][800];

 FILE * fp;
 const char *filename="new1.ppm";
 const char *comment="# ";/* comment should start with # */

 /* Z=Zx+Zy*i  ;   Z0 = 0 */
 double Zx, Zy;
 double Zx2, Zy2; /* Zx2=Zx*Zx;  Zy2=Zy*Zy  */
 /*  */
 int Iteration;
 const int IterationMax=200;
 /* bail-out value , radius of circle ;  */
 const double EscapeRadius=2;
 double ER2=EscapeRadius*EscapeRadius;


 int main(){

 double Cy, Cx, Zx, Zy, Zx2, Zy2, start, end;
int iX, iY, Iteration, id;

int tab[4] = {0};

  start = omp_get_wtime();
  #pragma omp parallel private(id) num_threads(4)
  {
    id = omp_get_thread_num();
    #pragma omp for private(Cy, Cx, Zx, Zy, Zx2, Zy2, iX, iY, Iteration) schedule(dynamic)
    for (iY=0; iY<iYmax; iY++) {
     Cy = CyMin + iY*PixelHeight;
        if (abs(Cy) < PixelHeight/2) Cy = 0.0;
            for (iX=0; iX<iXmax; iX++ ) {
                Cx = CxMin + iX*PixelWidth;
                Zx = 0.0;
                Zy = 0.0;
                Zx2 = Zx*Zx;
                Zy2 = Zy*Zy;

                for (Iteration=0; Iteration<IterationMax && ((Zx2+Zy2)<ER2); Iteration++)
                {

                    Zy = 2*Zx*Zy + Cy;
                    Zx = Zx2-Zy2 + Cx;
                    Zx2 = Zx*Zx;
                    Zy2 = Zy*Zy;
                };
                tab[id]+=Iteration;
                if (Iteration==IterationMax)
                {
                    color[iY][iX][0] = 0;
                    color[iY][iX][1] = 0;
                    color[iY][iX][2] = 0;
                }
                else {
                   color[iY][iX][0] = (id+1)*20+MAX_THREAD%255;
                   color[iY][iX][1] = (id+1)*100+MAX_THREAD%255;
                   color[iY][iX][2] = (id+1)*200+MAX_THREAD%255;
                };
            }
    }
  }
  end = omp_get_wtime();

  printf("%.3f\n", end-start);

  for(int i = 0; i < 4; i++){
    cout << tab[i] << endl;
  }
        /*create new file,give it a name and open it in binary mode  */
        fp= fopen(filename,"wb"); /* b -  binary mode */

        /*write ASCII header to the file*/
        fprintf(fp,"P6\n %s\n %d\n %d\n %d\n",comment,iXmax,iYmax,MaxColorComponentValue);
        /* compute and write image data bytes to the file*/




        /*write color to the file*/
      	for(int i=0;i < iXmax; i++){
      		for(int j=0;j< iYmax; j++){
      			fwrite(color[i][j],1,3,fp);
      		}
      	}
        fclose(fp);
        return 0;
 }
