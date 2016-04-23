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
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define SERVER_PORT "5432"
#define MAX_LINE 256

int
main(int argc, char *argv[])
{
	struct addrinfo hints;
	struct addrinfo *rp, *result;
  char *port;
	char *host;
  char *filename;
	char buf[MAX_LINE];
	int s;
	int len;

	if (argc==4)
	{
		host = argv[1];
    port = argv[2];
    filename = argv[3];
    printf("host = %s\n",host);
    printf("port = %s\n",port);
    printf("filename = %s\n", filename); 
	}
	else
	{
		fprintf(stderr, "usage: %s host port filename\n", argv[0]);
		exit(1);
	}

	/* Translate host name into peer's IP address */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	hints.ai_protocol = 0;

	if ((s = getaddrinfo(host, port, &hints, &result)) != 0 )
	{
		fprintf(stderr, "%s: getaddrinfo: %s\n", argv[0], gai_strerror(s));
		exit(1);
	}

	/* Iterate through the address list and try to connect */
	for (rp = result; rp != NULL; rp = rp->ai_next)
	{
		if ((s = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1 )
		{
      continue;
		}

		if (connect(s, rp->ai_addr, rp->ai_addrlen) != -1)
		{
<<<<<<< HEAD
	    while((send(s, filename, strlen(filename)+2, 0)) != -1);
      while ((len = recv(s, buf, sizeof(buf), 0)))
      {
        printf("Contents: %s\n", buf);
        /* Fills buf with file contents sent from server */
      }
=======
      printf("SOCKET S = %d.\n", s);
>>>>>>> d7202268b80b61a058977357c3ea2cebd67aa3a9
			break;
		}
		close(s);
	}
	if (rp == NULL)
	{
		perror("stream-talk-client: connect");
		exit(1);
	}
	freeaddrinfo(result);

<<<<<<< HEAD
//	send(s, filename, strlen(filename)+2, 0);
=======
	send(s, filename, strlen(filename)+2, 0);
  
  while ((len = recv(s, buf, sizeof(buf), 0)))
  {
    printf("%s", buf);
  }
>>>>>>> d7202268b80b61a058977357c3ea2cebd67aa3a9

  close(s);

	return 0;
}
