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

static void	explicit_directory(char *path, t_mini *mini)
{
	chdir(path);
	update_pwd(mini);
	update_cd(mini);
}

static void	previous_directory(t_mini *mini)
{
	chdir("..");
	update_pwd(mini);
	update_cd(mini);
}

static void	next_directory(char *dir, t_mini *mini)
{
	char	*next;

	next = ft_strjoin("./", dir);
	chdir(next);
	free(next);
	update_pwd(mini);
	update_cd(mini);
}

void		cd_special(t_mini *mini)
{
	char	*path_complete;

	path_complete = NULL;
	if (mini->av[1] == NULL)
		return ;
	else if (mini->av[1][0] == '~')
	{
		if (mini->av[1][1] != '\0')
			path_complete = ft_strjoin(env_search(mini->env, "HOME"),
			mini->av[1] + 1);
		else
			path_complete = ft_strdup(env_search(mini->env, "HOME"));
	}
	else if (is_dir(mini->av[1]) == TRUE)
		path_complete = ft_strdup(mini->av[1]);
	if (is_dir(path_complete) == TRUE)
	{
		explicit_directory(path_complete, mini);
		free(path_complete);
	}
	else
		ft_printf("%s: not a valid directory\n", path_complete);
}

void		mini_cd(char *path, t_mini *mini)
{
	if (path == NULL || ft_strcmp(path, ".") == 0)
		return ;
	else if (path[0] == '~' || ft_strcmp(path, "/tmp") == 0 ||
			ft_strcmp(path, "/bin") == 0)
		cd_special(mini);
	else if (ft_strcmp(path, "..") == 0)
		previous_directory(mini);
	else if (is_dir(path))
		next_directory(path, mini);
	else
		ft_printf("%s: not a valid directory\n", path);
}
