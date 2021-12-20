#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void print_ids(void);
void parentProcess(void);
void childProcess(void);


int main(void) {
  pid_t pId, gId, sId;
  pId = getpid(); 
  gId = getgid(); 
  sId = getsid(pId);

  if (sId == -1) {
    printf("Error while getting sid of process");
  }
  printf("BEFORE FORKING:\nPID: %d\nGID: %d\nSID: %d\n", pId, gId, sId);
  printf("~~~~~~~~~~~~~~~\n");
  pid_t fork_id = fork();
  printf("AFTER FORKING:\n");
  switch (fork_id){
    case -1:
      printf("Error while trying to call fork()"); 
      return 1; 
    case 0:
      childProcess();
      printf("\nCHILD PROCESS ENDED quiting\n");
    default:
      parentProcess();
      printf("\nPARENT PROCESS ENDED, quiting\n");
  }
  return 0;
}

void print_ids(void) {
  int i;
  printf("~~~~~~~~~~~~~~~\n");
  for (i = 0; i < 4; i++) {
    pid_t pid, gid, sid;
    pid = getpid();
    gid = getgid();
    sid = getsid(pid);
    printf("ITERATION: %d:\nPID: %d\nGID: %d\nSID: %d\n", i, pid, gid, sid);
  printf("~~~~~~~~~~~~~~~\n");}
 
}

void parentProcess(void) {
  int waitResultInfo;
  print_ids();
  wait(&waitResultInfo);
}

void childProcess(void) {
  print_ids();
}