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

void interpreter(char ** args, char * path, char * out){
  char * output;
  char ** ptr = &out;
  if(strcmp(args[0], "exit") == 0){
    strcpy(*ptr, "exit");
  }
  strcpy(*ptr, "program");


}
