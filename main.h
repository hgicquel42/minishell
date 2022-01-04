/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:08:18 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/04 17:17:34 by hgicquel         ###   ########.fr       */
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_state
{
	bool	exit;
	bool	retval;
	t_env	*envlst;
}	t_state;

int		ft_strcmp(char *a, char *b);

bool	ft_putchr(char c);

size_t	ft_strlen(char *s);

bool	ft_putstr(char *s);

char	*ft_getcwd(void);

bool	ft_isenvchr(char c);

t_env	*ft_envlst(char **envp);

t_env	*ft_findenv(t_env *start, char *key);

char	**ft_split(char *s, char c);

int		ft_split_free(char **r, int k);

char	**ft_ssplit(t_state *state, char *s, char c);

int		ft_ssplit_count2(t_state *state, char *s, int *r, char c);

void	ft_ssplit_copy2(t_state *state, char *s, char *w, char c);

char	*ft_strjoin2(char *a, char *b);

char	*ft_strdup(char *s, int l);

bool	ft_echo(char **args);

#endif