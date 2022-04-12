#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

struct timeval time1,time2;
char file_content[300] = "Hey There...! I'm Sidhdharth Pandya from MS in CS. This is my assignment no 7";
int file_sizes[6] = { 2, 16, 128, 1024, 8192,65536 };

int file_write(int total_test)
	{
		int i,j,size;
		char fn[128];
		long total_time;	
		for (i=0; i<total_test ; i++)
		{
			size = file_sizes[i];
			j=0;
			gettimeofday(&time1, NULL);
			while (j<10)    //for repeating 10 times
			{
				sprintf(fn,"C:/Users/STSC/Desktop/OSD/Assignment 7",j);
				int fp = open(fn, O_CREAT | O_WRONLY);
				write(fp, file_content, size);
				close(fp);
				j++;
			}
			gettimeofday(&time2, NULL);
			total_time = ((time2.tv_sec*1000000 + time2.tv_usec) - (time1.tv_sec*1000000 + time1.tv_usec));
		
			printf("Total time for writing  %d-bytes files : %ld usec.\n",size,total_time);

		}
	}

int file_fwrite(int total_test)
	{
		int i,j,size;
		char fn[128];
		long total_time;	
		for (i=0; i<total_test ; i++)
		{
			size = file_sizes[i];
			j=0 ;
			gettimeofday(&time1, NULL);
			while (j<10)
			{
				sprintf(fn,"C:/Users/STSC/Desktop/OSD/Assignment 7",j);
				FILE  *fp = fopen(fn,"w");
				fwrite(file_content , 1 , size , fp);
				fclose(fp);
				j++;
			}
			gettimeofday(&time2, NULL);
			total_time = ((time2.tv_sec*1000000 + time2.tv_usec) - (time1.tv_sec*1000000 + time1.tv_usec));
		
			printf("Total time for writing %d-bytes files : %ld usec.\n",size,total_time);

		}
	}

int main()
	{
		int tests = 6;
		file_write(tests);
		file_fwrite(tests);
		return 0;
	}		
		
   			
   			
   			


