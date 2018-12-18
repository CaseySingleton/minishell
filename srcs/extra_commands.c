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
	char	*usr_bin_path;
	char	**envs;
	int		bin_check;
	int		usr_bin_check;

	bin_path = ft_strjoin("/bin/", mini->av[0]);
	usr_bin_path = ft_strjoin("/usr/bin/", mini->av[0]);
	bin_check = is_exe(bin_path);
	usr_bin_check = is_exe(usr_bin_path);
	if (bin_check == TRUE || usr_bin_check == TRUE)
	{
		envs = env_to_list(mini->env);
		if (bin_check == TRUE)
			run_exe(bin_path, mini->av, envs);
		else if (usr_bin_check == TRUE)
			run_exe(usr_bin_path, mini->av, envs);
		if (envs)
			free_list(&envs);
	}
	free(bin_path);
	free(usr_bin_path);
	return (bin_check || usr_bin_check);
}

void		easter_eggish_thing(t_mini *mini)
{
	if (mini->name)
		free(mini->name);
	if (ft_strcmp(mini->av[0], "turtle") == 0)
		mini->name = ft_strdup("🐢");
	else if (ft_strcmp(mini->av[0], "taco") == 0)
		mini->name = ft_strdup("🌮");
	else if (ft_strcmp(mini->av[0], "avocado") == 0)
		mini->name = ft_strdup("🥑");
	else if (ft_strcmp(mini->av[0], "party") == 0)
		mini->name = ft_strdup("🎉🎊🎉");
}
