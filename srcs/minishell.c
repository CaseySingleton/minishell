/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 21:03:38 by csinglet          #+#    #+#             */
/*   Updated: 2018/12/13 21:03:39 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	only_spaces(char *str)
{
	int		i;

	i = -1;
	while (str[++i] != '\0')
		if (str[i] != ' ')
			return (0);
	return (1);
}

static void	commands(t_mini *mini)
{
	if (check_built_in_commands(mini) == TRUE)
		return ;
	else if (check_env_commands(mini) == TRUE)
		return ;
	else if (ft_strncmp(mini->av[0], "/", 1) == 0)
		mini_cd(mini->av[0], mini);
	else if (mini->ac == 2 && ft_strcmp(mini->av[1], "time") == 0)
		easter_eggish_thing(mini);
	else if (ft_strncmp(mini->av[0], "./", 2) == 0)
		mini_run(mini);
	else if (check_bin_for_exe(mini) == FALSE)
		ft_printf("command: %s: not found\n", mini->av[0]);
}

static int	get_ac(t_mini *mini)
{
	int		ac;

	ac = 0;
	while (mini->av[ac] != NULL)
		ac++;
	return (ac);
}

static void	mini_loop(t_mini *mini)
{
	mini->name = ft_strdup("🐢");
	update_cd(mini);
	while (1)
	{
		ft_printf("$ %s \033[36m%s\e\033[m %s >> ", mini->name, mini->cd,
				mini->name);
		get_next_line(1, &mini->raw_input);
		if (ft_strcmp(mini->raw_input, "\0") == 0 ||
			only_spaces(mini->raw_input) == 1)
		{
			free(mini->raw_input);
			continue ;
		}
		mini->expanded_input = expand_env_vars(mini, mini->raw_input);
		mini->av = ft_strsplit(mini->expanded_input, ' ');
		mini->ac = get_ac(mini);
		commands(mini);
		free_list(&(mini->av));
		free(mini->raw_input);
		free(mini->expanded_input);
	}
}

void		minishell(char *envp[])
{
	t_mini	mini;

	ft_printf("🐢🐢🐢🐢🐢🐢🐢🐢🐢🐢🐢🐢🐢\n");
	ft_printf("🐢 \e[5;30;30mStarting TutrleShell\e[m 🐢\n");
	ft_printf("🐢🐢🐢🐢🐢🐢🐢🐢🐢🐢🐢🐢🐢\n");
	ft_bzero(&mini, sizeof(t_mini));
	env_init(&(mini.env), envp);
	mini_loop(&mini);
}
