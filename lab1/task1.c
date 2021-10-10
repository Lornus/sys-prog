#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

ssize_t processFile(int buffCount, int asciiShift, int fIn, int fOut);


int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    fprintf(stderr, "Too few arguments\n");
    exit(1);
  }
  if (argc > 3)
  {
    fprintf(stderr, "Too much arguments\n");
    exit(1);
  }
  char *fileToRead = argv[1];
  char *fileToWright = argv[2];

  int fIn = open(fileToRead, O_RDONLY);

  if (fIn == -1)
  {
    fprintf(stderr, "Can't open file :( '%s'\n", fileToRead);
    return EXIT_FAILURE;
  }

  int fOut = open(fileToWright, O_CREAT | O_WRONLY, 0644);

  if (fOut == -1)
  {
    fprintf(stderr, "Can't open file :( '%s'\n", fileToWright);
    close(fIn);
    return EXIT_FAILURE;
  }

  int buffCount = 512;
  int asciiShift = -32;

  ssize_t changedBytes = processFile(buffCount, asciiShift, fIn, fOut);


  printf("Bytes changed in file: %li \n", changedBytes);
  close(fOut);

  close(fIn);
}

ssize_t processFile(int buffCount, int asciiShift, int fIn, int fOut)

{
  char buff[++buffCount];
  ssize_t bytesRead = 0;
  ssize_t changedBytes = 0;

  do
  {
    bytesRead = read(fIn, buff, buffCount);
    for (ssize_t i = 0; i <= buffCount; i++)
    {
      if (buff[i] >= 'a' && buff[i] <= 'z')
      {
        buff[i] += asciiShift;
        changedBytes++;
      }
    }
    write(fOut, buff, bytesRead);
  } while (bytesRead == buffCount);

  return changedBytes;
}