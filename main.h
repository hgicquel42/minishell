/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:08:18 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/04 13:53:16 by hgicquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_state
{
	bool	exit;
	bool	retval;
}	t_state;

char	*ft_getcwd(void);

int		ft_strcmp(char *a, char *b);

bool	ft_putchr(char c);

size_t	ft_strlen(char *s);

bool	ft_putstr(char *s);

char	**ft_split(char *s, char c);

int		ft_split_count(char *s, int *r, char c);

void	ft_split_copy(char *s, char *w, char c);

bool	ft_echo(char **args);

#endif