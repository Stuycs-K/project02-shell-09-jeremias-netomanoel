#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>


void parseInput(char * line, char * path, char * info){
  //init stuff here
  char * input[40];
  char * in = line;
  char * out;
  int cntr = 0;
  while (out = strsep(&in, ";")){
      input[cntr] = out;
      cntr++;
  }
  for (int i = 0; i < cntr; i ++){
    in = input[i];
    char * programline[100];
    cntr = 0;
    while (out = strsep(&in, " ")){
      out[strcspn(out, "\n")] = 0;
      programline[cntr] = out;
      cntr++;
    }
    if (strcmp(programline[0], "exit") == 0){
      strcpy(info, "e");
      break;
    }
    else if(strcmp(programline[0], "cd") == 0){
      //cd code here
      printf("%s\n", "cd");
    }
    else{
      //execvp
      printf("%s\n", "execvp");
    }
  }
}
