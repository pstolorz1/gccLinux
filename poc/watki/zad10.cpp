#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <tbb/tbb.h>
#include <tbb/task_group.h>

using namespace std;

typedef struct {
     unsigned char red, green, blue;
} PPMPixel;

typedef struct {
     int x, y;
     PPMPixel *data;
     unsigned char ***color;
} PPMImage;

#define RGB_COMPONENT_COLOR 255

static PPMImage *readPPM(const char *filename)
{
     char buff[16];
     PPMImage *img;
     FILE *fp;
     int c, rgb_comp_color;
     //open PPM file for reading
     fp = fopen(filename, "rb");
     if (!fp) {
          fprintf(stderr, "Unable to open file '%s'\n", filename);
          exit(1);
     }

     //read image format
     if (!fgets(buff, sizeof(buff), fp)) {
          perror(filename);
          exit(1);
     }

    //check the image format
    if (buff[0] != 'P' || buff[1] != '6') {
         fprintf(stderr, "Invalid image format (must be 'P6')\n");
         exit(1);
    }

    //alloc memory form image
    img = (PPMImage *)malloc(sizeof(PPMImage));
    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    //check for comments
    c = getc(fp);
    while (c == '#') {
    while (getc(fp) != '\n') ;
         c = getc(fp);
    }

    ungetc(c, fp);
    //read image size information
    if (fscanf(fp, "%d %d", &img->x, &img->y) != 2) {
         fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
         exit(1);
    }

    //read rgb component
    if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
         fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filename);
         exit(1);
    }

    //check rgb component depth
    if (rgb_comp_color!= RGB_COMPONENT_COLOR) {
         fprintf(stderr, "'%s' does not have 8-bits components\n", filename);
         exit(1);
    }

    while (fgetc(fp) != '\n') ;
    //memory allocation for pixel data
    img->data = (PPMPixel*)malloc(img->x * img->y * sizeof(PPMPixel));

    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    //read pixel data from file
    if (fread(img->data, 3 * img->x, img->y, fp) != img->y) {
         fprintf(stderr, "Error loading image '%s'\n", filename);
         exit(1);
    }

	img->color = new unsigned char** [img->y];
	for (int i = 0; i < img->y; i++)
	{
		img->color[i] = new unsigned char*[img->x];
		for (int j = 0; j < img->x; j++)
		{
			img->color[i][j] = new unsigned char[3];
		}
	}

	for (int x = 0; x < img->x; x++)
	{
		for (int y = 0; y < img->y; y++)
		{
			img->color[y][x][0] = img->data[x + y * img->x].red;
			img->color[y][x][2] = img->data[x + y * img->x].blue;
			img->color[y][x][1] = img->data[x + y * img->x].green;
		}
	}
	
    fclose(fp);
    return img;
}

void writePPM(const char *filename, PPMImage *img)
{
    FILE *fp;
    //open file for output
    fp = fopen(filename, "wb");
    if (!fp) {
         fprintf(stderr, "Unable to open file '%s'\n", filename);
         exit(1);
    }

    //image format
    fprintf(fp, "P6\n");

    //image size
    fprintf(fp, "%d %d\n",img->x,img->y);

    // rgb component depth
    fprintf(fp, "%d\n",RGB_COMPONENT_COLOR);

    // pixel data
    fwrite(img->data, 3 * img->x, img->y, fp);
    fclose(fp);
}

void filter1_3D(int shift, PPMImage *img)
{
	tbb::parallel_for(tbb::blocked_range2d<size_t>(0, img->x, 0, img->y),
	[=](const tbb::blocked_range2d<size_t>& r){
	
		for (size_t x=r.rows().begin(); x!=r.rows().end(); x++)
		{
			for (size_t y=r.cols().begin(); y!=r.cols().end(); y++)
			{
				if (x > shift && x < img->x - shift)
				{
					img->data[y * img->x + x].red = img->color[y][x - shift][0];
					img->data[y * img->x + x].green = 0;
					img->data[y * img->x + x].blue = img->color[y][x + shift][2];
				}
			}
		}

	});
}

void filter2_3D(int shift, PPMImage *img)
{
	tbb::parallel_for(tbb::blocked_range2d<size_t>(0, img->x, 0, img->y),
	[=](const tbb::blocked_range2d<size_t>& r){
	
		for (size_t x=r.rows().begin(); x!=r.rows().end(); x++)
		{
			for (size_t y=r.cols().begin(); y!=r.cols().end(); y++)
			{
				if (x > shift && x < img->x - shift)
				{
					img->data[y * img->x + x].red = img->color[y][x - shift][0];
					img->data[y * img->x + x].green = img->color[y][((x - shift) + (x + shift)) / 2][1];
					img->data[y * img->x + x].blue = img->color[y][x + shift][2];
				}
			}
		}

	});
}

void filter3_3D(int shift, PPMImage *img)
{
	tbb::parallel_for(tbb::blocked_range2d<size_t>(0, img->x, 0, img->y),
	[=](const tbb::blocked_range2d<size_t>& r){
	
		for (size_t x=r.rows().begin(); x!=r.rows().end(); x++)
		{
			for (size_t y=r.cols().begin(); y!=r.cols().end(); y++)
			{
				if (x > shift && x < img->x - shift)
				{
					img->data[x + y * img->x].red = img->color[y][x - shift][0];
					img->data[x + y * img->x].green = img->color[y][x + shift][1];
					img->data[x + y * img->x].blue = img->color[y][x + shift][2];
				}
			}
		}

	});
}

int main()
{
	PPMImage *img1;
	PPMImage *img2;

	img1 = readPPM("color.ppm");
	img2 = readPPM("blackwhite.ppm");

	tbb::task_scheduler_init init(2);
	tbb::task_group g;
	
	g.run([&]{filter3_3D(5, img1);});
	g.run([&]{filter3_3D(5, img2);});
	g.wait();

	writePPM("img1.ppm",img1);
	writePPM("img2.ppm",img2);

	return 0;
}
