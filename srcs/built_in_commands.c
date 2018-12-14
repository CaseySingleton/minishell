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
		exit (0);
	}
	else
		wait(&child);
}

void		mini_run(t_mini *mini)
{
	char	**envs;

	if (is_exe(mini->av[0]) == FALSE || ft_strcmp(mini->av[0], "./") == 0)
	{
		ft_printf("Invalid binary: %s\n", mini->av[0]);
		return ;
	}
	envs = env_to_list(mini->env);
	run_exe(mini->av[0], mini->av, envs);
	free_list(&envs);
}

void		mini_echo(char *str)
{
	char	*echo;

	if (str[0] == '"')
		ft_copy_until(&echo, str + 1, '"');
	else
		ft_copy_until(&echo, str, ' ');
	ft_printf("%s\n", echo);
	free(echo);
}
