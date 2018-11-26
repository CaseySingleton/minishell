#include "minishell.h"

int		is_exe(const char *exe_path)
{
	struct stat s;

	stat(exe_path, &s);
	return ((((s.st_mode & S_IXUSR) > 0) ? TRUE : FALSE));
}

void		run_exe(const char *exe_path, char **args)
{
	int	pid;
	int	status;

	if (is_exe(exe_path) == FALSE)
		return ;
	pid = fork();
	if (pid == 0)
		execve(exe_path, args, NULL);
	waitpid(pid, &status, 0);
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

void		mini_env(t_mini *mini)
{
	if (mini->ev == NULL)
		ft_printf("no list\n");
	print_list(mini->ev);
}
