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

static int	only_spaces(char **str)
{
	char	*temp;
	int		i;
	int		ret;

	i = -1;
	ret = TRUE;
	while ((*str)[++i] != '\0')
	{
		if ((*str)[i] == '\t')
			(*str)[i] = ' ';
		if (ret == TRUE && (*str)[i] != ' ')
			ret = FALSE;
	}
	temp = ft_strtrim(*str);
	free(*str);
	*str = temp;
	return (ret);
}

static void	commands(t_mini *mini)
{
	if (check_built_in_commands(mini) == TRUE)
		return ;
	else if (check_env_commands(mini) == TRUE)
		return ;
	else if (ft_strcmp(mini->av[0], "cd") == 0 && is_dir(mini->av[1]) == TRUE)
		mini_cd(mini->av[1], mini);
	else if (is_exe(mini->av[0]) == TRUE)
		mini_run(mini);
	else if (mini->ac == 2 && ft_strcmp(mini->av[1], "time") == 0)
		easter_eggish_thing(mini);
	else if (check_bins(mini) == FALSE)
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
			only_spaces(&(mini->raw_input)) == 1)
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

	ft_printf("🐢 \e[5;30;30mStarting TutrleShell\e[m 🐢\n");
	ft_bzero(&mini, sizeof(t_mini));
	env_init(&(mini.env), envp);
	mini_loop(&mini);
}
