#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//open include
#include <fcntl.h>

//readinclude
#include <unistd.h>
#define BCM_SYSLOG_MAX_LINE_SIZE      255
#define WEB_BUF_SIZE_MAX      4096
#define O_RDONLY       0x0000  /* open for reading only */
/** indicate first read */
#define BCM_SYSLOG_FIRST_READ            -2

/** indicates error */
#define BCM_SYSLOG_READ_BUFFER_ERROR     -1

/** indicates last line was read */
#define BCM_SYSLOG_READ_BUFFER_END       -3

/** indicates that something Brad added is not working */
#define BCM_SYSLOG_READ_2ND_BUFFER_ERROR -4

int cmsLog_readPartial(int ptr, char* buffer)
{
   return (oal_readLogPartial(ptr, buffer));
}



/*int oal_readLogPartial(const int ptr, char* buffer)
{
int fileHandle, length, returnValue;
int filePosition=0;
char theBuffer [WEB_BUF_SIZE_MAX];
int foundEndOfLine;
//char buffer[WEB_BUF_SIZE_MAX];

fileHandle = open("tew.log" , (O_RDONLY), 0666 );
    if (fileHandle != -1)
    {
        int tempPosition=0;
        int tempReadLength=0;
        tempPosition = lseek(fileHandle, filePosition, 0);
        printf("tempPosition=%d\n", tempPosition);

            tempReadLength = read (fileHandle, theBuffer,  WEB_BUF_SIZE_MAX);
            printf("tempReadLength=%d\n", tempReadLength);
            if (0 == tempReadLength)
            {printf("error length\n");}
            else
            {
              foundEndOfLine = 0;
              length         = 0;

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
 return (returnValue);
}*/


int oal_readLogPartial(const int ptr, char* buffer)
{
  int returnValue = BCM_SYSLOG_READ_BUFFER_ERROR;
  int fileHandle;
  int filePosition=0;
  int attemptToGetData;  /* really a bool */
  int foundEndOfLine;    /* really a bool */
  int length;
  char theBuffer [BCM_SYSLOG_MAX_LINE_SIZE];


  /*                                                       */
  /*  first...decode the first arguement...is it           */
  /*  a regular file position or some special, magic       */
  /*  broadcom value??                                     */
  /*  this decode results in setting some values           */
  /*    returnValue       what to return                   */
  /*    attemptToGetData  should we actually read the file */
  /*    filePosition      where should we start reading    */
  /*                                                       */
    printf("ptr=%d\n",ptr );

  switch (ptr)
    {
    case BCM_SYSLOG_FIRST_READ:
      attemptToGetData = 1;
      filePosition     = 0;
      break;
    case BCM_SYSLOG_READ_BUFFER_ERROR:
      attemptToGetData = 0;
      returnValue      = BCM_SYSLOG_READ_BUFFER_ERROR;
      break;
    case BCM_SYSLOG_READ_BUFFER_END:
      attemptToGetData = 0;
      returnValue      = BCM_SYSLOG_READ_BUFFER_END;
      break;
    case BCM_SYSLOG_READ_2ND_BUFFER_ERROR:
      attemptToGetData = 0;
      returnValue      = BCM_SYSLOG_READ_2ND_BUFFER_ERROR;
      break;
    default:
      attemptToGetData = 1;
      filePosition     = ptr;
      break;
    }
  printf("filePosition=%d\n",filePosition );


  if (1 == attemptToGetData)
    {
      fileHandle = open("tew.log" , (O_RDONLY), 0666 );
      if (fileHandle != -1)
	{
	  int tempPosition=0;
	  tempPosition = lseek(fileHandle, filePosition, 0);
	  printf("tempPosition=%d\n", tempPosition);

	  if (tempPosition != filePosition)
	    {
	      /*                                                    */
	      /*  the file seek went bad...this is a new error      */
	      /*                                                    */
          printf("tempPosition != filePosition\n");

	      returnValue     = BCM_SYSLOG_READ_2ND_BUFFER_ERROR;
	    }
	  else
	    {
	      /*                                                    */
	      /*  the file seek went well...try to read the file    */
	      /*  it is always nice to start with a clean buffer    */
	      /*                                                    */
	      int tempReadLength=0;
	      //for (tempReadLength = 0; tempReadLength < BCM_SYSLOG_MAX_LINE_SIZE; tempReadLength++)
	      //{
	      //  theBuffer [tempReadLength] = 0;
	      //}
	      tempReadLength = read (fileHandle, theBuffer,  BCM_SYSLOG_MAX_LINE_SIZE);
		  printf("tempReadLength=%d\n", tempReadLength);

	      if (0 == tempReadLength)
		{
		  /*                                                */
		  /* uh oh ....we are at the end of the file        */
		  /* set the return value and we are done           */
		  /*                                                */
		  returnValue     = BCM_SYSLOG_READ_BUFFER_END;
		}
	      else
		{
		  /*                                                */
		  /*  we are not at the end of the file....         */
		  /*  now we scan over the buffer looking for the   */
		  /*  end of line...coping the characters as we go  */
		  /*                                                */
		  foundEndOfLine = 0;     /* a bool found a \n      */
		  length         = 0;     /* number of char we got  */

		  while ( (!foundEndOfLine) && (length < tempReadLength))
		    {
		      if (theBuffer[length] != '\n')
				{
				  buffer [length] = theBuffer [length];
				  length++;
				  //returnValue     = length + filePosition + 1;
				  returnValue     = length - filePosition + 1;
				}
			      else
				{
				  foundEndOfLine = 1;
				  theBuffer [length] = 0;
				}
		    }
		}
	    }

	  close (fileHandle);
	}
      else
	{
	  /*                                                         */
	  /*  the file open went bad...this is a  new error          */
	  /*                                                         */
	  printf("else BCM_SYSLOG_READ_2ND_BUFFER_ERROR\n");
	  returnValue     = BCM_SYSLOG_READ_2ND_BUFFER_ERROR;
	}
    }
  return (returnValue);
}
int main()
{
    char data[WEB_BUF_SIZE_MAX], line[WEB_BUF_SIZE_MAX];
    int entries=0;

int readPtr = BCM_SYSLOG_FIRST_READ;
            while ((readPtr != BCM_SYSLOG_READ_BUFFER_ERROR) && (readPtr != BCM_SYSLOG_READ_BUFFER_END))
            {printf("readPtr=%d\n", readPtr);
                if ( entries++ > 39)
                {
                    printf("entries > %d\n", entries);
                    break;
                }

                readPtr = cmsLog_readPartial(readPtr, line);
                //printf("readPtr=%d\n", readPtr);
                //printf("line=%s\n", line);

                if ( readPtr == BCM_SYSLOG_READ_BUFFER_ERROR ){
                    printf("readPtr == BCM_SYSLOG_READ_BUFFER_ERROR\n");
                    break;
                }
             }
    printf("Hello world!\n");
    return 0;
}
