make: file.c main.c misc.c parser.c
	gcc -Werror -Wextra -Wall -o rush-02 file.c main.c misc.c parser.c
fclean: 
	rm *.o *.out
