#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
              
int main(int argc, char* argv[]) {
  // Make sure enough arguments are provided
  if (argc != 2) {
    printf("Incorrect number of arguments provided\n");
    exit(1);
  }
  // Open the input file and make sure it opens correctly
  int ifd;
  if ((ifd = open(argv[1], O_RDONLY)) == -1) {
    printf("File opened incorrectly\n");
    exit(1);
  }
  // Remove the extention on the inputfile
  int i;
  for (i = 0; i < strlen(argv[1]); i++) {
    if (argv[1][i] == '.') {
      argv[1][i+1] = '\0';
    }
  }
  // Add the .up extention to the outputfile
  i = strlen(argv[1]);
  argv[1][i++] = 'u';
  argv[1][i++] = 'p';
  argv[1][i++] = '\0';
  // Open the output file and create buffer to write to from input
  int ofd;
  if ((ofd = open(argv[1], O_CREAT | O_RDWR)) == -1) {
    printf("File opened incorrectly\n");
    exit(1);
  }
  char buf[1];
  while (read(ifd, buf, 1)) {
    write(ofd, buf, 1);
  }

  return 0;
}
