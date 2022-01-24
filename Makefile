NAME = minishell

INPUT = \
	main.c \
	split.c \
	xsplit.c \
	ssplit.c \
	ssplit2.c \
	psplit.c \
	utils.c \
	utils2.c \
	utils3.c \
	utils4.c \
	utils5.c \
	utils6.c \
	envlst.c \
	envlst2.c \
	envlst3.c \
	echo.c \
	exec.c \
	loop.c \
	convert.c \
	env.c \
	cmdio.c \
	exit.c \
	run.c \
	sort.c \

OUTPUT = ${INPUT:.c=.o}

all: ${NAME}

.c.o:	
	gcc -Wall -Wextra -Werror -g -c $< -o ${<:.c=.o} -lreadline

${NAME}: ${OUTPUT}
	gcc -Wall -Wextra -Werror -g ${OUTPUT} -o ${NAME} -lreadline

clean:
	rm -f ${OUTPUT}

fclean:	clean
	rm -f ${NAME}

re:		fclean all