/*
 * Student Adam J. Penn
 * Student Thomas Greenman
 * CSCI 446
 * Spring 2016
 *
 * This template provides the framework you need for program 1. Complete the functions
 * defined and create any you feel are neccessary. stream-talk-client.c on Learn will
 * prove useful.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>



#define SERVER_NAME "www.ecst.csuchico.edu"
#define SERVER_PORT "80"
#define REQUEST "GET /~ehamouda/file.html HTTP/1.0\n\n"


/***************************************************************
 * Arguments: same as recv(2)
 * Return:-1 on error or bytes received
 *
 * Receive len bytes of data into array buf from socket sockfd. Always receive len bytes
 * of data unless the socket closes. The return value will fall into one of three cases:
 *   (1) on success the return value equals len
 *   (2) on error the return value equals -1
 *   (3) if the socket closes without receiving len bytes, then return the number
 *       actually received, which may be zero
 ***************************************************************/
ssize_t readchunk( int sockfd, void *buf, size_t len );


int main( int argc, char *argv[] ) 
{
  if(argc < 3)
  {
    printf("Usage: ./executable chunk_size tag\n");
    printf("chunk_size must be greater than 0 and less than 1000\n");
    printf("Tag must be 'socket', '<p>', '<i>', '<b>'\n");
    return 1;
  }
  /* The value of <c> can be:
   * "socket"
   * "<p>"
   * "<i>"
   * "<b>"
   */
  
  int chunk_size = atoi(argv[1]);
  printf("Chunk size = %d\n", chunk_size);
  if(chunk_size > 1000 || chunk_size <= 0)
  {
    printf("Chunk size must be greater than 0 and less than 1000\n");
    return 1;
  }
  
  char* tag = argv[2];
  printf("Tag = %s\n", tag);
  if((strcmp(tag,"socket") != 0) && (strcmp(tag,"<p>") != 0) && (strcmp(tag,"<i>") != 0) && (strcmp(tag,"<b>") != 0))
  {
    printf("Tag must be 'socket', '<p>', '<i>', '<b>'\n");
    return 1;
  }
  

	/* Call readchunck in here ... */

  struct addrinfo hints, *result, *rp;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  int s;
  /* Use getaddrinfo to find an address */
  if((s = getaddrinfo(SERVER_NAME, SERVER_PORT, &hints, &result)) != 0)
  {
    printf("ERROR: %s: getaddrinfo: %s\n", argv[0], gai_strerror(s));
    exit(1);
  }

  /* Iterate through addresses and try to connect */
  /* Literally got this code from the example, not sure if it works */
  for(rp = result; rp != NULL; rp->ai_next)
  {
    if((s = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol))== -1)
    {
      continue;
    }
    if(connect(s,rp->ai_addr, rp->ai_addrlen) != -1)
    {
      break;
    }
    close(s);
  }

  if(rp == NULL)
  {
    printf("ERROR: count not connect\n");
    return 1;
  }

  freeaddrinfo(result);
  
  char* buffer;
  int result = readchunk(s,buffer,chunk_size);
  if(result == -1)
  {
    printf("ERROR: Bytes received\n");
  }
  printf("lol\n");
  return 0;

}

ssize_t readchunk( int sockfd, void *buf, size_t len ) 
{

	/* Define readchunck to return exactly len bytes unless an error occurs or the socket closes. 
*/
  return 0;
}
