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

int			check_bin_for_exe(t_mini *mini)
{
	char	*bin_path;
	char	**envs;
	int		check;

	bin_path = ft_strjoin("/bin/", mini->av[0]);
	check = is_exe(bin_path);
	if (check == TRUE)
	{
		envs = env_to_list(mini->env);
		run_exe(bin_path, mini->av, envs);
		if (envs)
			free_list(&envs);
	}
	if (bin_path)
		free(bin_path);
	return (check);
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
	else if (ft_strcmp(mini->av[0], "env") == 0)
		mini_env(mini->env);
	else if (mini->ac == 3 && ft_strcmp(mini->av[1], "=") == 0)
		env_set(mini);
	else if (ft_strcmp(mini->av[0], "unset") == 0 && mini->ac == 2)
		env_unset(mini);
	else if (ft_strncmp(mini->av[0], "./", 2) == 0)
		mini_run(mini);
	else if (check_bin_for_exe(mini) == FALSE)
		ft_printf("command: %s: not found\n", mini->av[0]);
	free_list(&(mini->av));
}

static int	get_ac(t_mini *mini)
{
	int		ac;

	ac = 0;
	while (mini->av[ac] != NULL)
		ac++;
	return (ac);
}

void		mini_loop(t_mini *mini)
{
	mini->name = ft_strdup("🐢");
	update_cd(mini);
	while (1)
	{
		ft_printf("$ %s \033[36m%s\e\033[m %s >> ", mini->name, mini->cd, mini->name);
		get_next_line(1, &mini->raw_input);
		if (ft_strcmp(mini->raw_input , "\0") == 0 || only_spaces(mini->raw_input) == 1)
			continue ;
		mini->av = ft_strsplit(mini->raw_input, ' ');
		mini->ac = get_ac(mini);
		commands(mini);
		free(mini->raw_input);
	}
}

void		minishell(char *envp[])
{
	ft_printf("Starting tutrleshell\n");
	t_mini	mini;

	ft_bzero(&mini, sizeof(t_mini));
	env_init(&(mini.env), envp);
	mini_loop(&mini);
}
