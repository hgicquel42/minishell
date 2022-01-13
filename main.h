/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgicquel <hgicquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:08:18 by hgicquel          #+#    #+#             */
/*   Updated: 2022/01/13 18:24:27 by hgicquel         ###   ########.fr       */
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

typedef struct s_cmd
{
	char	**args;
	char	**envp;
	pid_t	pid;
	int		fdi;
	int		fdo;
	int		sts;
}	t_cmd;

typedef struct s_ldata
{
	char	**prts;
	t_cmd	**cmds;
	int		*pipes;
}	t_ldata;

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_state
{
	bool	cmd;
	int		exit;
	int		retval;
	t_env	*envlst;
}	t_state;

void	sigint(int sig);

int		ft_free(void *p);

int		ft_strcmp(char *a, char *b);

bool	ft_putchr(int fd, char c);

size_t	ft_strlen(char *s);

bool	ft_putstr(int fd, char *s);

int		ft_strcpy(char *s, char *r, char (*f)(char));

int		ft_strlcpy(char *s, char *r, int l, char (*f)(char));

char	*ft_strdup(char *s, char (*f)(char));

char	*ft_strldup(char *s, int l, char (*f)(char));

char	*ft_getcwd(void);

bool	ft_isenvchr(char c);

bool	ft_isenvstr(char *s);

bool	ft_fillenv(t_env **start, char **envp);

t_env	*ft_findenv(t_env *start, char *key);

char	**ft_split(char *s, char c);

int		ft_freep(void **p);

int		ft_freel(void **p, int k);

char	**ft_xsplit(
			t_state *g, char *s,
			t_tuple (*f)(t_state *g, char *s, char *r));

t_tuple	ft_psplit(t_state *g, char *s, char *r);

t_tuple	ft_ssplit(t_state *g, char *s, char *r);

t_tuple	ft_ssplit_dollar(t_state *g, t_tuple t, char *s, char *r);

void	ft_chrcpy(char *r, int i, char c);

char	*ft_strjoin2(char *a, char *b);

char	*ft_strjoin3(char *a, char *b, char *c);

int		ft_route_fork(t_state *s, t_cmd *cmd);

int		ft_echo(char **args, char **envp);

int		ft_exec(t_state *g, t_cmd *cmd);

pid_t	ft_run(t_state *s, t_cmd *cmd);

char	ft_chrid(char c);

char	ft_chrup(char c);

bool	ft_loop(t_state *g);

t_cmd	**ft_convertall(t_state *g, char **prts, int l);

char	**ft_envtostr(t_env *start);

int		ft_env(char **args, char **envp);

bool	ft_addenv(t_env **start, char *key, char *val);

void	ft_remenv(t_env **start, char *key);

void	ft_freeenv(t_env *envn);

bool	ft_setenv(t_env **start, char *key, char *val);

int		ft_unset(t_state *g, char **args, char **envp);

int		ft_export(t_state *g, char **args, char **envp);

bool	ft_route_cmd_io(t_ldata d, int i, int *s, bool *p);

int		ft_exit(t_state *g, char **args, char **envp);

#endif