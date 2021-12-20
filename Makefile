NAME = minishell

INPUT = \
	main.c \

OUTPUT = ${INPUT:.c=.o}

all: ${NAME}

.c.o:	
	gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o} -lreadline

${NAME}: ${OUTPUT}
	gcc -Wall -Wextra -Werror ${OUTPUT} -o ${NAME} -lreadline

clean:
	rm -f ${OUTPUT}

fclean:	clean
	rm -f ${NAME}

re:		fclean all