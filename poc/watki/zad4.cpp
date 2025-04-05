#include <iostream>
#include <stdio.h>
#include <math.h>
#include <thread>
#include <chrono>

using namespace std;

const int image_size = 1001;
unsigned char image[image_size][image_size][3];
const int MaxColorComponentValue=255; 

int ulam_get_map(int x, int y, int n)
{
	x -= (n - 1) / 2;
	y -= n / 2;
	int mx = abs(x), my = abs(y);
	int l = 2 * max(mx, my);
	int d = y >= x ? l * 3 + x + y : l - x - y;
	return pow(l - 1, 2) + d;
}

int is_prime(int n)
{
	int p;
	for (p = 2; p*p <= n; p++)
	if (n%p == 0)
		return 0;
	return n > 2;
}

void draw_sequence()
{
 	for (int i = 0; i < image_size; i++)
    {
        for (int j = 0; j < image_size; j++)
        {
			if(is_prime(ulam_get_map(i, j, image_size)))
			{
				image[i][j][0] = 0;
				image[i][j][1] = 0;
				image[i][j][2] = 0;
			}
			else
			{
				image[i][j][0] = 255;
				image[i][j][1] = 255;
				image[i][j][2] = 255;
			}
        }
    }
}

void set_values(int &x_start, int &x_stop, int &y_start, int &y_stop, int i)
{
	if(i == 0)
	{
		x_start = (image_size + 1) / 2;
		x_stop = image_size;
		y_start = 0;
		y_stop = (image_size + 1) / 2;
	}
	
	if(i == 1)
	{
		x_start = 0;
		x_stop = (image_size + 1) / 2;
		y_start = 0;
		y_stop = (image_size + 1) / 2;
	}
	
	if(i == 2)
	{
		x_start = 0;
		x_stop = (image_size + 1) / 2;
		y_start = (image_size + 1) / 2;
		y_stop = image_size;
	}
	
	if(i == 3)
	{
		x_start = (image_size + 1) / 2;
		x_stop = image_size;
		y_start = (image_size + 1) / 2;
		y_stop = image_size;
	}
}

int main()
{
	FILE *fp;
    char *filename = "new1.ppm";
    char *comment = "# ";
    fp = fopen(filename, "wb");
    fprintf(fp, "P6\n %s\n %d\n %d\n %d\n", comment, image_size, image_size, MaxColorComponentValue);
    
    auto start = std::chrono::steady_clock::now();
    
	//draw_sequence();
    
    thread spiral[4];
	
	int x_start, x_stop, y_start, y_stop;
	
	for (int t_num = 0; t_num < 4; t_num++)
	{
		set_values(x_start, x_stop, y_start, y_stop, t_num);
		spiral[t_num] = thread([ x_start, x_stop, y_start, y_stop ]()
						{
							for (int i = x_start; i < x_stop; i++)
							{
								for (int j = y_start; j < y_stop; j++)
								{
									if(is_prime(ulam_get_map(i, j, image_size)))
									{
										image[i][j][0] = 0;
										image[i][j][1] = 0;
										image[i][j][2] = 0;
									}
									else
									{
										image[i][j][0] = 255;
                						image[i][j][1] = 255;
                						image[i][j][2] = 255;
                					}
								}
							}
						});
	}
	
	for(int t_num = 0; t_num < 4; t_num++)
	{
		spiral[t_num].join();
	}

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "CZAS: "<< elapsed_seconds.count() << "s\n";
	
	fwrite(image, 1, 3 * image_size * image_size, fp);
	fclose(fp);
	
	return(0);
}

