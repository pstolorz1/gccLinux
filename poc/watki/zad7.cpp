#include <stdio.h>
#include <math.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <vector>
#include <omp.h>

using namespace std;

const int image_size = 101;
unsigned char image[image_size][image_size][3];
const int MaxColorComponentValue=255;

unsigned int original_maze[image_size][image_size];
int thread_count = 1;

//mutex mutex_maze_array[image_size][image_size];
//mutex thread_id;
omp_lock_t maze_lock[image_size][image_size];
omp_lock_t thread_id;

void read_maze() 
{
  	string line;
  	ifstream file("original_maze.txt");
  	int rowIndex = 0;
  	while(!file.eof() && rowIndex < image_size) 
  	{
    	getline(file, line);
    	for (int i = 0; i<image_size; i++) 
    	{
		  	if (line.at(i) == '*') 
		  	{
		    	original_maze[rowIndex][i] = -1;
		  	} 
		  	else 
		  	{
		    	original_maze[rowIndex][i] = 0;
		  	}
    	}
    rowIndex++;
  	}	
}

void draw_original_maze()
{
	for (int i = 0; i < image_size; i++)
    {
        for (int j = 0; j < image_size; j++)
        {
			if(original_maze[i][j] == -1)
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

void save_maze(int x, int y, int thread_value)
{
	//mutex_maze_array[x][y].lock();
	omp_set_lock(&maze_lock[x][y]);
	if (original_maze[x][y] == 0) 
  	{
    	original_maze[x][y] = thread_value;
    	image[x][y][0] = 10 * thread_value;
    	image[x][y][1] = 20 * thread_value;
    	image[x][y][2] = 30 * thread_value;
  	} 
  	omp_unset_lock(&maze_lock[x][y]);
  	//mutex_maze_array[x][y].unlock();
}

void run_maze(int x, int y)
{
	bool run = true;
	
	int thread_val = 0;
	
	omp_set_lock(&thread_id);
	thread_count++;
	thread_val = thread_count;
    omp_unset_lock(&thread_id);
    
	//thread_id.lock();
	//thread_count++;
	//int thread_val = thread_count;
	//thread_id.unlock();

	//vector<thread> thread_vec;
	
	while(run) 
	{
		save_maze(x, y, thread_val);

		vector<pair<int, int>> available_moves;
		
		if (x-1 >= 0 && original_maze[x-1][y] == 0)
			available_moves.push_back(make_pair(x-1, y+0));	

		if (x+1 < image_size && original_maze[x+1][y] == 0)
			available_moves.push_back(make_pair(x+1, y+0));

		if (y-1 >= 0 && original_maze[x][y-1] == 0)
			available_moves.push_back(make_pair(x+0, y-1));

		if (y+1 < image_size && original_maze[x][y+1] == 0)
			available_moves.push_back(make_pair(x+0, y+1));

		int available_moves_length = available_moves.size();
		
		if(available_moves_length == 0) 
		{
			run = false;
		}
		else if (available_moves_length == 1) 
		{
			x = available_moves.at(0).first;
			y = available_moves.at(0).second;
		}
		else 
		{
			x = available_moves.at(0).first;
			y = available_moves.at(0).second;
			for (int i = 1; i <available_moves_length; i++) 
			{
				int x_new = available_moves.at(i).first;
				int y_new = available_moves.at(i).second;
				//thread_vec.push_back(thread(run_maze, x_new, y_new));
				#pragma omp task
        		run_maze(x_new, y_new);
			}
		}
	}

	//for(int i = 0; i < thread_vec.size(); i++)
		//thread_vec[i].join();
 	#pragma omp taskwait
}

int main()
{

 	for (int i=0; i<image_size; i++) 
  	{
   		for (int j=0; j<image_size; j++) 
      	{
        	omp_init_lock(&maze_lock[i][j]);
      	}
    }
    
    omp_init_lock(&thread_id);
    
    read_maze();
    draw_original_maze();
    
    FILE *fp;
    char *filename = "new1.ppm";
    char *comment = "# ";
    fp = fopen(filename, "wb");
    fprintf(fp, "P6\n %s\n %d\n %d\n %d\n", comment, image_size, image_size, MaxColorComponentValue);

    //thread main_thread(run_maze, 1, 1);
    //main_thread.join();

    #pragma omp parallel
    {
   		#pragma omp single
      	{
        	run_maze(1, 1);
      	}
    }

    fwrite(image, 1, 3 * image_size * image_size, fp);
    fclose(fp);
    
    omp_destroy_lock(&thread_id);
    
   	for (int i=0; i<image_size; i++) 
   	{
    	for (int j=0; j<image_size; j++) 
    	{
        	omp_destroy_lock(&maze_lock[i][j]);
      	}
    }
    
    return 0;
}

