/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:08:18 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/07 15:00:35 by hgicquel         ###   ########.fr       */
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

typedef struct s_tuple
{
	int	i;
	int	o;
}	t_tuple;

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

int		ft_free(void *p);

int		ft_strcmp(char *a, char *b);

bool	ft_putchr(char c);

size_t	ft_strlen(char *s);

bool	ft_putstr(char *s);

void	ft_strcpy(char *s, char *r, char (*f)(char));

void	ft_strlcpy(char *s, char *r, int l, char (*f)(char));

char	*ft_strdup(char *s, char (*f)(char));

char	*ft_strldup(char *s, int l, char (*f)(char));

char	*ft_getcwd(void);

bool	ft_isenvchr(char c);

t_env	*ft_envlst(char **envp);

t_env	*ft_findenv(t_env *start, char *key);

char	**ft_split(char *s, char c);

bool	ft_freel(char **p, int k);

char	**ft_ssplit(t_state *state, char *s, char c);

t_tuple	ft_ssplit2(t_state *g, char *s, char *r, char c);

t_tuple	ft_ssplit2_dollar(t_state *g, t_tuple t, char *s, char *r);

void	ft_chrcpy(char *r, int i, char c);

char	*ft_strjoin2(char *a, char *b);

char	*ft_strjoin3(char *a, char *b, char *c);

bool	ft_echo(char **args);

int		ft_exec(t_state *s, char **args);

char	ft_chrid(char c);

char	ft_chrup(char c);

#endif