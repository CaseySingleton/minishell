/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 21:04:00 by csinglet          #+#    #+#             */
/*   Updated: 2018/12/13 21:04:00 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_direcotry_and_update_info(char *path, t_mini *mini)
{
	chdir(path);
	update_pwd(mini);
	update_cd(mini);
}

void		mini_cd(char *path, t_mini *mini)
{
	char	*test;
	char	*fixed_path;

	test = NULL;
	if (path == NULL)
	{
		test = env_search(mini->env, "HOME");
		if (test == NULL)
		{
			ft_printf("no valid directory\n");
			return ;
		}
		fixed_path = ft_strdup(test);
	}
	else
		fixed_path = ft_strdup(path);
	if (is_dir(fixed_path) == TRUE)
		change_direcotry_and_update_info(fixed_path, mini);
	else
		ft_printf("%s: not a valid directory\n", fixed_path);
	free(fixed_path);
}
