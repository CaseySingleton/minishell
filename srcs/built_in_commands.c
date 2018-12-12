#include "minishell.h"

void		run_exe(const char *exe_path, char **args, char **envs)
{
	pid_t	child;

	if (is_exe(exe_path) == FALSE || ft_strlen(exe_path) == 2)
	{
		ft_printf("Invalid binary: %s\n", exe_path);
		return ;
	}
	child = fork();
	if (child < 0)
		ft_printf("Fork error\n");
	else if (child == 0)
		execve(exe_path, args, envs);
	else
		wait(&child);
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

void		mini_env(t_env *env)
{
	t_env	*cur;

	cur = env;
	int i = -1;
	while (cur != NULL)
	{
		ft_printf("%d: %s=%s\n", cur->position + 1, cur->name, cur->value);
		cur = cur->next;
	}
}
