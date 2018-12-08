#include "minishell.h"

int		only_spaces(char *str)
{
	int	i;

	i = -1;
	while(str[++i] != '\0')
		if (str[i] != ' ')
			return (0);
	return (1);
}

void		commands(t_mini *mini)
{
	if (ft_strcmp(mini->av[0], "exit") == 0)
		exit (0);
	else if (ft_strcmp(mini->av[0], "cd") == 0)
		mini_cd(mini->av[1], mini);
	else if (ft_strcmp(mini->av[0], "pwd") == 0)
		mini_pwd();
	else if (ft_strcmp(mini->av[0], "hostname") == 0)
		hostname(mini);
	else if (ft_strcmp(mini->av[0], "echo") == 0)
		mini_echo(mini->raw_input + 5);
	else if (ft_strcmp(mini->av[0], "ls") == 0)
		run_exe("/bin/ls", mini->av);
	else if (ft_strncmp(mini->av[0], "./", 2) == 0)
		run_exe(mini->av[0], mini->av);
	else if (ft_strcmp(mini->av[0], "env") == 0)
		mini_env(mini->env);
	else
		ft_printf("command: %s: not found\n", mini->av[0]);
	free_list(&(mini->av));
}

void		mini_loop(t_mini *mini)
{
	mini->name = ft_strdup("Casey");
	update_cd(mini);
	while (1)
	{
		ft_printf("$ %s \033[36m%s\e\033[m >> ", mini->name, mini->cd);
		get_next_line(1, &mini->raw_input);
		if (ft_strcmp(mini->raw_input , "\0") == 0 || only_spaces(mini->raw_input) == 1)
			continue ;
		mini->av = ft_strsplit(mini->raw_input, ' ');
		commands(mini);
		free(mini->raw_input);
	}
}

void		minishell(char *evnp[])
{
	t_mini	mini;

	mini.ev = evnp;
	ft_bzero(&mini, sizeof(t_mini));
	env_init(&(mini.env), evnp);
	mini_loop(&mini);
}
