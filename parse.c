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
  printf("%d\n", cntr);
  for (int i = 0; i < cntr; i +=1){
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
      if(cntr>2){
        printf("MANNYSHELL: Too many arguments\n");
        getcwd(path, sizeof(path));
        continue;
      }
      else if(cntr<2){
        chdir("/");
        getcwd(path, sizeof(path));
        continue;
      }
      else{
        if(chdir(programline[1]) == -1){
          printf("MANNYSHELL: No such file or directory\n");
          getcwd(path, sizeof(path));
          continue;
        }
        continue;
      }
    }
    else{
      //execvp
      printf("%s\n", "execvp");
    }
  }
}
