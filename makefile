compile runme: shell.o parse.o commands.o
	@gcc -o shell shell.o parse.o commands.o -lm
shell.o: shell.c parse.h commands.h
	@gcc -c shell.c -lm
parse.o: parse.c parse.h
	@gcc -c parse.c -lm
commands.o: commands.c commands.h
	@gcc -c commands.c commands.h
clean:
	@rm *.o
	@rm shell
