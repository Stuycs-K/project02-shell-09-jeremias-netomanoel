compile runme: shell.o exec.o
	@gcc -o shell shell.o exec.o -lm
shell.o: shell.c exec.h
	@gcc -c shell.c -lm
exec.o: exec.c exec.h
	@gcc -c exec.c -lm
clean:
	@rm *.o
	@rm shell
