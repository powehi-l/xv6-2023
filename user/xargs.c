#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

char* readline(char* buf, int* count){
  char* buffer = buf;
  while(read(0, buffer, 1) != 0 && *buffer != '\n' && *count > 0)
    buffer++, (*count)--;
  //printf("%s, %c\n", buf, *buffer);
  *buffer = 0;
  return (buffer == buf) ? 0 : buf;
}

int
main(int argc, char *argv[])
{
  //int arg_counts = argc, i;
  int i;
  char buf[512];
  char *xargs_argv[MAXARG], *buf_temp = buf;
  int freespace = 512;

  if(argc < 2){
    fprintf(2, "Usage: xargs echo\n");
    exit(0);
  }
  for(i = 0; i < argc - 1 && i < MAXARG; ++i)
    xargs_argv[i] = argv[i + 1];
  
  while((xargs_argv[i++] = readline(buf_temp, &freespace)) != 0)
    buf_temp += strlen(xargs_argv[i-1]) + 1;

  //for(int j = 0; xargs_argv[j] != 0; j++){
  //  printf("xargs_argv[%d]: %s\n", j, xargs_argv[j]);
  //}

  int pid = fork();
  if(pid == 0){
    exec(argv[1], xargs_argv);
  }
  else{
    wait(&pid);
  }
  exit(0);
}
