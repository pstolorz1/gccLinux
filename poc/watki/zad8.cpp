#include <iostream>
#include <stdio.h>
#include <math.h>
#include <tbb/tbb.h>

using namespace std;

const int image_size = 5001;
unsigned char image[image_size][image_size][3];

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

int main()
{
	FILE *fp;
    char *filename = "new1.ppm";
    char *comment = "# ";
    fp = fopen(filename, "wb");
    fprintf(fp, "P6\n %s\n %d\n %d\n %d\n", comment, image_size, image_size, 255);
	
	tbb::tick_count t0 = tbb::tick_count::now();
	
	tbb::parallel_for(tbb::blocked_range2d<size_t>(0, image_size, 0, image_size),
	[=](const tbb::blocked_range2d<size_t>& r)
	{
		for (size_t i = r.rows().begin(); i != r.rows().end(); i++)
		{
			for (size_t j = r.cols().begin(); j != r.cols().end(); j++)
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
	
	tbb::tick_count t1 = tbb::tick_count::now();
	std::cout << "CZAS: "<< (t1-t0).seconds() << "s\n";
	
	fwrite(image, 1, 3 * image_size * image_size, fp);
	fclose(fp);
	
	return(0);
}

