compile runme: shell.o parse.o
	@gcc -o shell shell.o parse.o -lm
shell.o: shell.c parse.h
	@gcc -c shell.c -lm
parse.o: parse.c parse.h
	@gcc -c parse.c -lm
clean:
	@rm *.o
	@rm shell
