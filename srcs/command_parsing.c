/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 22:20:16 by csinglet          #+#    #+#             */
/*   Updated: 2018/12/14 22:20:16 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_built_in_commands(t_mini *mini)
{
	int		check;

	check = 1;
	if ((check = ft_strcmp(mini->av[0], "exit")) == 0)
		exit(0);
	else if ((check = ft_strcmp(mini->av[0], "cd")) == 0)
		mini_cd(mini->av[1], mini);
	else if ((check = ft_strcmp(mini->av[0], "pwd")) == 0)
		mini_pwd();
	else if ((check = ft_strcmp(mini->av[0], "hostname")) == 0)
		hostname(mini);
	else if ((check = ft_strcmp(mini->av[0], "echo")) == 0)
		mini_echo(mini->expanded_input + 5);
	return (check == 0 ? 1 : 0);
}

int			check_env_commands(t_mini *mini)
{
	int		check;

	check = 1;
	if ((check = ft_strcmp(mini->av[0], "env")) == 0)
		mini_env(mini->env);
	else if (mini->ac == 3 && (check = ft_strcmp(mini->av[1], "=")) == 0)
		env_set(mini);
	else if ((check = ft_strcmp(mini->av[0], "unset")) == 0 && mini->ac == 2)
		env_unset(mini);
	return (check == 0 ? 1 : 0);
}
