compile runme: shell.o exec.o
	@gcc -o shell shell.o exec.o -lm -g
shell.o: shell.c exec.h
	@gcc -c shell.c -lm -g
exec.o: exec.c exec.h
	@gcc -c exec.c -lm -g
clean:
	@rm *.o
	@rm shell
