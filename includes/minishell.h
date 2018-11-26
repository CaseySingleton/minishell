#include <unistd.h>

#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"

#ifndef MINISHELL_H
# define MINISHELL_H

# define TRUE 1
# define FALSE 0

typedef struct	s_mini
{
	char	**av;
	int	ac;
	char	**ev;
	char	*name;
	char	*raw_input;
	char	*cd;
}		t_mini;

/*
**	minishell.c
*/

void		mini_loop(t_mini *mini);
void		minishell(char **ev);

/*
**	built_in_commands.c
*/

int		is_exe(const char *exe_path);
void		run_exe(const char *exe_path, char **args);
void		mini_echo(char *str);
void		mini_env(t_mini *mini);
void		mini_cd(char *path, t_mini *mini);

/*
**	cd_command.c
*/

void		mini_cd(char *path, t_mini *mini);

/*
**	extra_commands.c
*/

void		hostname(t_mini *mini);

/*
**	interface.c
*/

char		*current_directory(char *str);

/*
**	utils.c
*/

int		is_dir(char *dir);
void		print_list(char **list);
char		**ft_lstdup(char **list);

#endif
