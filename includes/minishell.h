#include <unistd.h>

#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"

#ifndef MINISHELL_H
# define MINISHELL_H

# define TRUE 1
# define FALSE 0
# define ERROR -1

/*
**	¯\\_(ツ)_/¯
*/

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_mini
{
	char			**av;
	int				ac;
	t_env			*env;
	char			*name;
	char			*raw_input;
	char			*cd;
	char			*pwd;
	char			expansion;
}					t_mini;

/*
**	minishell.c
*/

void				mini_loop(t_mini *mini);
void				minishell(char **ev);

/*
**	built_in_commands.c
*/

void				run_exe(const char *exe_path, char **args, char **envs);
void				mini_run(t_mini *mini);
void				mini_echo(char *str);
int					mini_env(t_env *env);
void				mini_cd(char *path, t_mini *mini);

/*
**	cd_command.c
*/

void				mini_cd(char *path, t_mini *mini);

/*
**	extra_commands.c
*/

void				hostname(t_mini *mini);

/*
**	environment.c
*/

void				update_pwd(t_env *env);
void				update_cd(t_mini *mini);
void				env_set(t_mini *mini);
void				env_unset(t_mini *mini);

/*
**	interface.c
*/

void				mini_pwd(void);

/*
**	list_function.c
*/

t_env				*env_new_node(char *name, char *value);
void				env_push(t_env **list, t_env *to_add);
void				env_free_node(t_env **node);
void				env_free(t_env **list);
void				env_init(t_env **env, char *envp[]);
char				*env_search(t_env *env, char *name);

/*
**	utils.c
*/

int					is_exe(const char *exe_path);
int					is_dir(char *dir);
char				*last_word_delim(char *str, int delim);
char				**env_to_list(t_env *env);
void				print_list(char **list);
char				**ft_lstdup(char **list);
void				free_list(char ***list);

#endif
