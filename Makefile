NAME = minishell

INPUT = \
	main.c \
	split.c \
	ssplit.c \
	ssplit2.c \
	ssplit3.c \
	utils.c \
	utils2.c \
	utils3.c \
	utils4.c \
	utils5.c \
	envlst.c \
	envlst2.c \
	echo.c \
	exec.c \

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