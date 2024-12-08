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

void parseInput(char * line, char * path, char * info){
  //init stuff here
  char * input[40];
  char edit[100];
  strcpy(edit, line);
  edit[strcspn(edit, "\n")] = 0;
  char * in = edit;
  char * out;
  int cntr = 0;
  while (out = strsep(&in, ";")){
      input[cntr] = out;
      cntr++;
  }
  int loop = cntr;
  int i = 0;
  for (i = 0; i < loop; i +=1){
    char * in = input[i];
    char * programline[100];
    cntr = 0;
    while (out = strsep(&in, " ")){
      programline[cntr] = out;
      cntr++;
    }
    programline[cntr] = '\0';
    if (strcmp(programline[0], "exit") == 0){
      strcpy(info, "e");
      break;
    }
    else if(strcmp(programline[0], "cd") == '\0'){
      //cd code here
      if(cntr>2){
        printf("MANNYSHELL: Too many arguments\n");
        fflush(stdout);
      }
      else if(cntr<2){
        chdir("/");
      }
      else if(cntr == 2){
        if(chdir(programline[1]) == -1){
          printf("MANNYSHELL: No such file or directory\n");
          fflush(stdout);
        }
      }
    }
    else{
      if(programline[0] != NULL){
        int * stats;
        pid_t forking;
        forking = fork();
        if(forking<0){
          perror("fork fail");//output to stderr instead of stdout
          exit(1);
        }
        else if (forking == 0){
          execvp(programline[0], programline);
          perror("execvp fail");
          exit(1);
        }
        else{
          wait(stats);
        }
      }
    }
  }
}
