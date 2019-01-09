/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 21:04:06 by csinglet          #+#    #+#             */
/*   Updated: 2019/01/05 16:35:21 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		run_exe(const char *exe_path, char **args, char **envs)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		ft_printf("Fork error\n");
	else if (child == 0)
	{
		execve(exe_path, args, envs);
		exit(0);
	}
	else
		wait(&child);
}

void		mini_run(t_mini *mini)
{
	char	**envp;

	envp = env_to_list(mini->env);
	run_exe(mini->av[0], mini->av, envp);
	if (envp != NULL)
		free_list(&envp);
}

void		mini_echo(char *str)
{
	int		i;
	int		j;
	char	*echo;

	i = 0;
	j = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '"')
	{
		while (str[i] == '"')
			i++;
		while (str[j + i] != '"' && str[j + i] != '\0')
			j++;
	}
	else
		while (str[i + j] != ' ' && str[i + j] != '"' && str[i + j] != '\0')
			j++;
	echo = ft_strndup(str + i, j);
	ft_printf("%s\n", echo);
	free(echo);
}

void		mini_pwd(void)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	ft_printf("%s\n", wd);
	free(wd);
}

int			mini_env(t_env *env)
{
	int		i;

	if (env == NULL)
		return (0);
	i = mini_env(env->next) + 1;
	ft_printf("%d: %s=%s\n", i, env->name, env->value);
	return (i);
}
