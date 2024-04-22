#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p[2], temp[2], prime, pid, input_prime;

  prime = 2;

  pipe(p);
  for(int i = prime + 1; i <= 37; ++i){
    if(i % prime != 0){
      write(p[1], &i, 4);
      //printf("write %d\n", i);
    }
  }
  close(p[1]);
  printf("prime %d\n", prime);

  pid = fork();

  while(1){
    if(pid != 0){
      close(p[0]);
      wait(&pid);
      exit(0);
    }
    else{
      read(p[0], &prime, 4);
      //printf("prime: %d\n", prime);
      if(prime < 35){
        printf("prime %d\n", prime);
        pipe(temp);
        while(read(p[0], &input_prime, 4) != 0){
          if(input_prime % prime != 0){
            write(temp[1], &input_prime, 4);
            //printf("primm: %d\n", input_prime);
          }
        }
        close(p[0]);
        close(temp[1]);
        p[0] = temp[0];
        pid = fork(); 
      } 
      else{
        exit(0);
      }
    }
  }
  return 0;
}
