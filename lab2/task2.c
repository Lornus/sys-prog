#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

void parentProcess(int * fd);
void childProcess();

int main(void) {
    int fd;
    ssize_t bytes_output;
    pid_t forkId;

    fd = open("lab2.log", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
      printf("Error while opening log file for writing (initial)\n");
      return -1;
    }
    write(fd, "WRITING TO LOG FILE\n", strlen("WRITING TO LOG FILE\n"));

    forkId = fork();
    if (forkId < 0) {
        write(fd, "Error while trying to call fork()\n",
        strlen("Error while trying to call fork()\n"));
        close(fd);
    }
    else if (forkId == 0) {
        childProcess();
    }
    else {
        parentProcess(&fd);
    }

    return 0;
}

void parentProcess(int * fd) {
    write((* fd), "Child has been created\n",
    strlen("Child has been created\n"));
    exit(EXIT_SUCCESS);
}

void childProcess() {
    pid_t newSid;
    char buff[100];
    int buff_length;
    int pid;
    int i;
    int fd;

    newSid = setsid();
    if (newSid == -1) {
        printf("Error while calling setsid()\n");
    }
  
    if(chdir("/") == -1) {
        printf("Error while calling setsid()\n");
    }

    for(i = 0; i < 255; i++) {
        close(i);
    }

    open("/dev/null", O_RDWR);
    dup(0); 
    dup(0); 

    buff_length = sprintf(buff, "PID: %d, GID: %d, SID: %d\n", getpid(), getgid(), newSid);
    fd = open("./lab2.log", O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd == -1) {
      printf("Error while opening log file for writing (from daemon)\n");
      return;
    }
    
    while(1) {
        time_t cur = time(NULL);
        char * stime = ctime(&cur);
        buff_length = sprintf(buff, "PID: %d, Current time is: %s", getpid(), stime);
        write(fd, buff, buff_length);
        sleep(1);
    }
    close(fd);
}