#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int a[2];
  pipe(a);

  int pid = fork();
  if(pid == 0){
    char ch;
    read(a[0], &ch, 1);
    //printf("%d: receive ping\n", getpid());
    if(ch == 0xF){
      printf("%d: received ping\n", getpid());
    }
    else{
      printf("%d: received rong ping\n", getpid());
    }

    write(a[1], &ch, 1);
    close(a[0]);
    close(a[1]);
  }
  else{
    char ch1 = 0xF;
    write(a[1], &ch1, 1);
    wait(&pid);

    read(a[0], &ch1, 1);
    close(a[0]);
    close(a[1]);
    //printf("%d: receive pong\n", getpid());

    if(ch1 == 0xF){
      printf("%d: received pong\n", getpid());
    }
    else{
      printf("%d: received wrong pong\n", getpid());
    }
  }

  exit(0);
}
