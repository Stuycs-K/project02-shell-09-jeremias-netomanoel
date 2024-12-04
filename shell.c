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
#include "commands.h"
#include "parse.h"

int main(int argc, char const *argv[]) {
  char path[1000];
  char input[255];
  getcwd(path, sizeof(path));
  printf("WELCOME TO MANNYSHELL, THE BEST SHELL AROUND!\n");
  printf("path: %s $ ", path);
  while(fgets(input,255,stdin) != 0){
    //do everything here
    char * args[40];
    parse_args(input, args);
    char out[100];
    printf
    interpreter(args, path, out);
    if (strcmp(out, "exit")==0){
      printf("We thank you for using MANNYSHELL, goodbye!");
      break;
    }
    else if (strcmp(out, "program")!=0){
      strcpy(path, out);
    }
    //reset
    printf("path: %s $ ", path);
  }
  return 0;
}
