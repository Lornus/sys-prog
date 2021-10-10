#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>

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
  struct pollfd fds[1];
  int output, nread;
  char buff[BUFF_SIZE];

  while (1)
  {
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
    output = poll(fds, 1, 5000);
    switch (output)
    {
    case 0:
      fprintf(stderr, "Identifier '%s' got no input, type something or quit\n", identifier);
      break;
    case -1:
      fprintf(stderr, "Something went wrong with selection :(\n");
      exit(EXIT_FAILURE);
    default:
      nread = read(STDIN_FILENO, buff, BUFF_SIZE);
      if (buff[nread - 1] == '\n')
      {
        buff[nread - 1] = '\0';
      }
      fprintf(stderr, "%s processed input - '%s'\n", identifier, buff);
      break;
    }
  }
  return 0;
}