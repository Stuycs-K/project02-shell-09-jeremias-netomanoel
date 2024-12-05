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

char * interpreter(char ** args, char * path){
  if(strcmp(args[0], "exit\n") == 0){
    return "e";
  }
  else if (strcmp(args[0], "cd\n")!= 0){
    return "p";
  }
  else if(strcmp(args[0], "cd\n")== 0){
    return "/";
  }
  else{
    printf("%s\n",args[1]);
    return args[1];
  }
}
