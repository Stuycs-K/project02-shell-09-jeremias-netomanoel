[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Tfg6waJb)
# Systems Project2 - MyShell

# MEMBERS: 
  Manoel Jeremias-Neto

# TEAM NAME:
  MANNYSHELL

# IMPLEMENTATION
  REDIRECTS ✅
  PIPES ✅
  CD ✅
  EXEC ✅
  EXIT ✅

# ISSUES
  when inputing a file for the shell to use as stdin (replacing user input), at the end you end up with 3 stacked prompts, no clue why. doesnt seem to affect functionality, just visual.

# shell.c 
  (the main shell)
  the one with the main in it that loops forever until either exit or ctrl+d happens

# exec.c
  (does literally everything else)
  i was having issues transfering arrays of char arrays around (for some reason) so i just did everything in one function so at least it works
  this does mean there are only two functions (not very modular design)
  there are however very clear "sections" of code which with comments should be understandable

# FUNCTION HEADERS
  #ifndef EXEC_H
  #define EXEC_H
  void parseInput(char * line, char * path, char * info);
  #endif

