#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>

//open include
#include <fcntl.h>

//readinclude
#include <unistd.h>


#define O_RDONLY       0x0000  /* open for reading only */

struct sockaddr_in antelope;
char *some_addr;

typedef enum{
  All,
  January,
  February,
  March,
  April,
  May
}month;

month Month;
int mon;

int main()
{
int fileHandle, length, returnValue;
int filePosition=0;
char theBuffer [255];
int foundEndOfLine;    /* really a bool */
char buffer[4096] = {0};

fileHandle = open("tew.log" , (O_RDONLY), 0666 );
if (fileHandle != -1)
{
    int tempPosition=0;
    int tempReadLength=0;
    tempPosition = lseek(fileHandle, filePosition, SEEK_END);
    printf("tempPosition=%d\n", tempPosition);

	      tempReadLength = read (fileHandle, theBuffer,  255);
		  printf("tempReadLength=%d\n", tempReadLength);
	    if (0 == tempReadLength)
		{printf("error length\n");}
		else{
		  foundEndOfLine = 0;     /* a bool found a \n      */
		  length         = 0;     /* number of char we got  */

		  while ( (!foundEndOfLine) && (length < tempReadLength))
		    {
		      if (theBuffer[length] != '\n')
				{
				  buffer [length] = theBuffer [length];
				  length++;
				  returnValue     = length + filePosition + 1;
				  //returnValue     = length - filePosition + 1;
				}
			      else
				{
				  foundEndOfLine = 1;
				  theBuffer [length] = 0;
				}
		    }
		}
printf("buffer=%s\n", buffer);
printf("theBuffer=%s\n", theBuffer);
printf("returnValue=%d\n", returnValue);
close (fileHandle);
}
else
{
  printf("BCM_SYSLOG_READ_2ND_BUFFER_ERROR");
}
//=================================*
/*  printf("enter number 1~5\n");
  scanf("%d",&mon);

  switch(mon){
      case January:
          printf("a\n"); break;
      case February:
          printf("b\n"); break;
      case March:
          printf("c\n"); break;
      case April:
          printf("d\n"); break;
      case May:
          printf("e\n"); break;
      default:
          printf("fail input\n");
  }*/
//=================================*
/*    inet_aton("10.0.0.1", &antelope.sin_addr);
    some_addr = inet_ntoa(antelope.sin_addr); // ¶Ç¦^ IP
    printf("%s\n", some_addr); // ¿é¥X "10.0.0.1"*/
/*
    char *ipAddr = "192:168:0:22";
    char *test;
    test = strchr(ipAddr, ':');
    printf("%s\n", test);*/
//=================================*
/*char* DMZHost=NULL;
if(DMZHost && (strlen(DMZHost) ==0))
{
    printf("DMZHost=%s\n", DMZHost);
    printf("sizeof(DMZHost)=%d\n",sizeof(DMZHost));
}
printf("DMZHost=%s\n", DMZHost);
printf("sizeof(DMZHost)=%d\n",sizeof(DMZHost));*/
//=================================*
/*  char line[1024]="abcd efgh ijklmnop";
    printf("line=%c\n", line[9]);*/
//=================================*
    printf("Hello world!\n");
    return 0;
}
