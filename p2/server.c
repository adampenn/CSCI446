/* Authors:
 *  Adam Penn
 *  Thomas Greenman
 * Class:
 *  CSCI446-01
 *  Spring 2016
 */

/* This code is an updated version of the sample code from "Computer Networks: A Systems
 * Approach," 5th Edition by Larry L. Peterson and Bruce S. Davis. Some code comes from
 * man pages, mostly getaddrinfo(3). */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LINE 1000000
#define MAX_PENDING 5

int main(int argc, char *argv[])
{
  // declare varibales
  struct addrinfo hints;
  struct addrinfo *rp, *result;
  char buf[MAX_LINE];
  char *port;
  int s, new_s;

  // check number of command line args
  if(argc == 2)
  {
    port = argv[1];
    //printf("port = %s\n", port);
  }
  else
  {
    fprintf(stderr, "usage: %s port\n", argv[0]);
    exit(1);
  }


  /* Build address data structure */
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  hints.ai_protocol = 0;
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;

  /* Get local address info */
  if ((s = getaddrinfo(NULL, port, &hints, &result)) != 0 )
  {
    fprintf(stderr, "%s: getaddrinfo: %s\n", argv[0], gai_strerror(s));
    exit(1);
  }

  /* Iterate through the address list and try to perform passive open */
  for (rp = result; rp != NULL; rp = rp->ai_next)
  {
    if ((s = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1 )
    {
      continue;
    }

    if (!bind(s, rp->ai_addr, rp->ai_addrlen))
    {
      break;
    }

    close(s);
  }
  if (rp == NULL)
  {
    perror("stream-talk-server: bind");
    exit(1);
  }
  if (listen(s, MAX_PENDING) == -1)
  {
    perror("stream-talk-server: listen");
    close(s);
    exit(1);
  }


  // Wait for connection, then receive and print text 
  while(1)
  {
    if ((new_s = accept(s, rp->ai_addr, &(rp->ai_addrlen))) < 0)
    {
      perror("stream-talk-server: accept");
      close(s);
      exit(1);
    }
    
    if ((recv(new_s, buf, 255, 0)) == -1) {
      printf("Error: never recived file name");
    }
    
    //printf("Received filename: %s from client\n", buf);

    // create file pointer and buffer
    char file_text[MAX_LINE];
    FILE *fp = fopen(buf,"r");
    if(fp == NULL)
    {
      //fprintf(stderr, "File does not exist\n");
      int network_byte_order = htonl(-1);
      write(new_s, &network_byte_order,sizeof(-1));
      exit(1);
    }

    // Fill buffer
    char c;
    while(1)
    {
      c = fgetc(fp);
      if( feof(fp) )
      { 
        break ;
      }
      strcat(file_text,&c);
    }
    int text_size  = strlen(file_text);
    int network_byte_order = htonl(text_size);

    write(new_s, &network_byte_order,sizeof(network_byte_order));

    send(new_s,file_text,strlen(file_text),0);

    fclose(fp);
    close(new_s);
    break;
  }

  freeaddrinfo(result);
  close(s);
  close(new_s);

  return 0;
}
