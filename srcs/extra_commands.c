/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 21:03:48 by csinglet          #+#    #+#             */
/*   Updated: 2018/12/13 21:03:48 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		hostname(t_mini *mini)
{
	if (mini->av[1] == NULL)
		return ;
	if (mini->name)
		free(mini->name);
	mini->name = ft_strdup(mini->av[1]);
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
