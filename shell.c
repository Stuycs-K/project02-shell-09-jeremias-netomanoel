#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include "exec.h"


int main(int argc, char const *argv[]) {
  char path[100];
  char input[100];
  char info[4];
  getcwd(path, sizeof(path));
  printf("WELCOME TO MANNYSHELL, THE WORST SHELL AROUND!\n");
  printf("root:%s$ ", path);
  while(fgets(input,100,stdin) != 0){
    //do everything here
    parseInput(input, path, info);
    fflush(stdout);
    if(info != NULL && strcmp(info, "e") == 0){
      printf("Thank you for using MANNYSHELL!\n");
      break;
    }
    getcwd(path, sizeof(path));
    printf("root:%s$ ", path);
  }
  return 0;
}
