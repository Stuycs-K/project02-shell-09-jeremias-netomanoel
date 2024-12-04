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


void parse_args(char * line, char ** arg_ary ){
  char * in = line;
  char * out;
  char *** ptr = &arg_ary;
  while ((out = strsep(&in, " ")) != NULL) {
      **ptr = out;
      ptr++;
  }
}
