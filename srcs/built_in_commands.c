#include "minishell.h"

void		run_exe(const char *exe_path, char **args)
{
	pid_t	pid;
	int		status;

	if (is_exe(exe_path) == FALSE)
		return ;
	pid = fork();
	if (pid == 0)
	{
		ft_printf("running: %s\n", exe_path);
		execve(exe_path, args, NULL);
	}
	wait(&pid);
	ft_printf("closing: %s\n", exe_path);
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
