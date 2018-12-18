/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:20:38 by csinglet          #+#    #+#             */
/*   Updated: 2018/12/14 15:20:42 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# define TRUE 1
# define FALSE 0
# define ERROR -1

/*
**	¯\_(ツ)_/¯
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
	char			*expanded_input;
	char			*cd;
	char			expansion;
}					t_mini;

/*
**	minishell.c
*/

void				minishell(char **ev);

/*
**	expansion.c
*/

char				*expand_env_vars(t_mini *mini, char *src);

/*
**	command_parsing.c
*/

int					check_built_in_commands(t_mini *mini);
int					check_env_commands(t_mini *mini);

/*
**	built_in_commands.c
*/

void				run_exe(const char *exe_path, char **args, char **envs);
void				mini_run(t_mini *mini);
void				mini_echo(char *str);
void				mini_pwd(void);
int					mini_env(t_env *env);

/*
**	cd_command.c
*/

void				explicit_directory(char *path, t_mini *mini);
void				mini_cd(char *path, t_mini *mini);
void				cd_special(t_mini *mini);

/*
**	extra_commands.c
*/

void				hostname(t_mini *mini);
int					check_bin_for_exe(t_mini *mini);
void				easter_eggish_thing(t_mini *mini);

/*
**	environment.c
*/

void				update_pwd(t_mini *mini);
void				update_cd(t_mini *mini);
void				env_init(t_env **env, char *envp[]);
void				env_set(t_mini *mini);
void				env_unset(t_mini *mini);

/*
**	list_function.c
*/

t_env				*env_new_node(char *name, char *value);
void				env_push(t_env **list, t_env *to_add);
void				env_free_node(t_env **node);
void				env_free(t_env **list);
char				*env_search(t_env *env, char *name);

/*
**	utils.c
*/

int					is_dir(char *dir);
int					is_exe(const char *exe_path);
char				**env_to_list(t_env *env);
char				*last_word_delim(char *str, int delim);
void				free_list(char ***list);

#endif
