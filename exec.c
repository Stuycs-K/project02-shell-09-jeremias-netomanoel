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
#include <pwd.h>

void parseInput(char * line, char * path, char * info){

  //init stuff here

  char * input[40];
  char edit[100];
  char * out;
  int cntr = 0;
  int stdout2;
  int stdin2;

  //setup for pipes down the line

  dup2(stdout2, STDOUT_FILENO);
  dup2(stdin2, STDIN_FILENO);

  int tempfile = open("tempfile.txt", O_CREAT | O_TRUNC | O_RDWR);

  //setup for home directory finding

  const char *homedir;
  if ((homedir = getenv("HOME")) == NULL) {
      homedir = getpwuid(getuid())->pw_dir;
  }

  //removing "/n" from line (stdin to shell) (idk why it needs to be done in this roundabout way but im pretty sure its related to const char * somehow)
  //if it isnt here i get a bad memory address error (i took me way too long to figure this out)

  strcpy(edit, line);
  edit[strcspn(edit, "\n")] = 0;
  char * in = edit;

  //strsep out ; for sep prompts on same line

  while (out = strsep(&in, ";")){
      input[cntr] = out;
      cntr++;
  }
  int loop = cntr;
  int haspipe = 0;

  //strsep out pipes so that i can do the stdin and stdout of the input side and the output side of the pipe

  for (int i = 0; i < loop; i +=1){
    char * linein = input[i];
    char * lineline[100];
    int counter = 0;

//the actual strsep

    while (out = strsep(&linein, "|")){
      lineline[counter] = out;
      counter++;
    }
    if(counter == 2){
      haspipe = 1;
    }
    for(int l = 0; l < counter; l ++){

      //there are 3 case: no pipe, pipe (on the left side of |) and pipe (on the right side of |)
      //this just dup2s either stdin or out to tempfile depending on which one, or does nothing if there is no pipe

      if(haspipe == 1 && l == 0){
        dup2(tempfile, STDOUT_FILENO);
      }
      if(haspipe == 1 && l == 1){
        dup2(tempfile, STDIN_FILENO);
      }

      //for each prompt strsep'd out, strsep again for " " to get an args array

      char * in = lineline[l];
      char * programline[100];
      cntr = 0;
      while (out = strsep(&in, " ")){
        programline[cntr] = out;
        cntr++;
      }

      //set the end \0 (just in case) idk it breaks without this (but only sometimes)

      programline[cntr] = 0;

      //if it says exit, quit (thats whats break is for)

      if (strcmp(programline[0], "exit") == 0){
        strcpy(info, "e");
        break;
      }

      //if cd, then depending on how many args were strsep'd with " " as the delimiter, has 3 behaviors

      else if(strcmp(programline[0], "cd") == '\0'){
        //cd code here
        if(cntr>2){
          //too many args
          printf("MANNYSHELL: Too many arguments\n");
          fflush(stdout);
        }
        else if(cntr<2){
          //goes to homedirectory
          chdir(homedir);
        }
        else if(cntr == 2){
          //tries to go to directory in cd's args, and yells at you if it doesnt exist
          if(chdir(programline[1]) == -1){
            printf("MANNYSHELL: No such file or directory\n");
            fflush(stdout);
          }
        }
      }

      //execvp and killing children part:

      else{
        if(programline[0] != NULL){

          //checking for < and > (and hopefully redirecting stdin / out into or out of them)

          int in2 = 0;
          int out2 = 0;
          for (int k = 0; k < cntr; k ++){
            if (strcmp(programline[k], "<")==0){
              in2 = open(programline[k+1], O_CREAT | O_TRUNC | O_RDWR);
              dup2(in2, STDIN_FILENO);
              programline[k] = 0;
            }
            if (strcmp(programline[k], ">")==0){
              out2 = open(programline[k+1], O_CREAT | O_TRUNC | O_RDWR);
              dup2(out2, STDOUT_FILENO);
              programline[k] = 0;
            }
          }

          //init stuff for forking

          int * stats;
          pid_t forking;

          //forking activity (and waiting for it to execvp stuff)

          forking = fork();
          if(forking<0){ //failure
            perror("fork fail");
            exit(1);
          }
          else if (forking == 0){ //child
            execvp(programline[0], programline);
            perror("execvp fail");
            exit(1);
          }
          else{ //parent
            wait(stats);
          }
        }
      }
    }
  }
  //at the end, reset stdin and out just in case, as well as close tempfile
  dup2(stdin2, STDIN_FILENO);
  dup2(stdout2, STDOUT_FILENO);
  close(tempfile);
}
