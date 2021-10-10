#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  size_t BUFF_SIZE = 1024;

  if (argc < 2)
  {
    fprintf(stderr, "Must be one identifier\n");
    exit(1);
  }

  if (argc > 2)
    {
      fprintf(stderr, "Too much identifiers, try again with one\n");
      exit(1);
    }

  char *identifier = argv[1];
  char buff[BUFF_SIZE];
  int output, nread;
  fd_set input, testfds;
  struct timeval timeout;
  FD_ZERO(&input);
  FD_SET(0, &input);

  while (1)
  {
    testfds = input;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    output = select(FD_SETSIZE, &testfds, (fd_set *)NULL, (fd_set *)NULL, &timeout);
    switch (output)
    {
    case 0:
      fprintf(stderr, "Identifier '%s' got no input, type something or quit\n", identifier);
      break;
    case -1:
      fprintf(stderr, "Something went wrong :(\n");
      exit(EXIT_FAILURE);
    default:
      nread = read(STDIN_FILENO, buff, BUFF_SIZE);
      if (buff[nread - 1] == '\n')
      {
        buff[nread - 1] = '\0';
      }
      fprintf(stderr, "%s processed input: '%s'\n", identifier, buff);
      break;
    }
  }
  return 0;
}