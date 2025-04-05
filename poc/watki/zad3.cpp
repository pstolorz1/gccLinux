#include <iostream>
#include <stdio.h>
#include <math.h>
#include <thread>

using namespace std;

const int x_max = pow(2, 10);
const int y_max = pow(2, 10);
const int level_max = 8;
const int MaxColorComponentValue=255; 
unsigned char triangle[x_max][y_max][3];

void draw(int x, int y, int level)
{
    int length = x_max / pow(2, level);
    
    for (int i = y; i < y + length; i++)
    {
        for (int j = x; j < x + length; j++)
        {
            if (i == y + length - 1 || j == x || i == j - x + y)
            {
                triangle[i][j][0] = 255; //R
                triangle[i][j][1] = 255; //G
                triangle[i][j][2] = 255; //B
            }
        }
    }
    
    if (level < level_max)
    {
		level++;
		thread triangles[3];
		triangles[0] = thread(draw, x, y, level);
		triangles[1] = thread(draw, x, y + length / 2, level);
		triangles[2] = thread(draw, x + length / 2, y + length / 2, level);
		triangles[0].join();
		triangles[1].join();
		triangles[2].join();
    }
}

int main()
{
    FILE *fp;
    char *filename = "new1.ppm";
    char *comment = "# ";
    fp = fopen(filename, "wb");
    fprintf(fp, "P6\n %s\n %d\n %d\n %d\n", comment, x_max, y_max, MaxColorComponentValue);

    draw(0, 0, 0);
 
	for(int iX = 0; iX < x_max; iX++)
	{
		for(int iY=0; iY < y_max; iY++)
		{         
			fwrite(triangle[iX][iY], 1, 3, fp);
		}
	}
    fclose(fp);
    
    return 0;
}

