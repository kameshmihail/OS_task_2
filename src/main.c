#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include <stdbool.h>
  
int main() 
{ 
    int fd1[2]; 
    int fd2[2]; 
    int fd3[2];
    int firstcoordinate;
    int secondcoordinate;
    pid_t p; 
    if (pipe(fd1)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    if (pipe(fd2)==-1) 
    {
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    p = fork(); 
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        return 1; 
    } 
    else if (p > 0) 
    {
        if (scanf("%d %d", &firstcoordinate, &secondcoordinate)!=2)
          {
            printf("Failed to read, exiting\n");
            return 1;
          }
        int result; 
        close(fd1[0]);
	close(fd3[0]);
        write(fd1[1], &firstcoordinate, 100); 
        close(fd1[1]);
	write(fd3[1], &secondcoordinate, 100);
	close(fd3[1]);
        wait(NULL); 
        close(fd2[1]);
	close(fd3[1]); 
        read(fd2[0], &result, 100); 
        printf("Point lies in quarter %d\n", result);
        close(fd2[0]);	
    } 
    else
    { 
        close(fd1[1]);
	close(fd3[1]);
	bool i = true;
	int calcresult;
        int result = 0; 
        read(fd1[0], &calcresult, 10);
	if (calcresult < 0)
	  {i = false;}
	read(fd3[0], &result, 10);
	if (result < 0 && i == false)
	  {result = 3;}
	else if (result < 0 && i == true)
	  {result = 4;}
	else if (result >= 0 && i == true)
	  {result = 1;}
	else if (result >= 0 && i == false)
	  {result = 2;}
        close(fd1[0]);
	close(fd3[0]);
        close(fd2[0]); 
        write(fd2[1], &result, 100); 
        close(fd2[1]); 
        exit(0); 
    } 
} 

