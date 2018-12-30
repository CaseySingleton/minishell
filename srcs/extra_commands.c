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

static int	check_bin(t_mini *mini, char *path, char *binary, char **envp)
{
	char	*full_path;
	int		status;

	full_path = ft_strjoin(path, "/");
	full_path = ft_strjoin_free_s1(full_path, binary);
	if ((status = is_exe(full_path)) == TRUE)
		run_exe(full_path, mini->av, envp);
	if (full_path != NULL)
		free(full_path);
	return (status);
}

int			check_bins(t_mini *mini)
{
	char	*path;
	char	**paths;
	char	**envp;
	int		ret;
	int		i;

	ret = FALSE;
	i = -1;
	if ((path = env_search(mini->env, "PATH")) == NULL)
		return (FALSE);
	paths = ft_strsplit(path, ':');
	envp = env_to_list(mini->env);
	while (paths[++i] != NULL && ret != TRUE)
		ret = check_bin(mini, paths[i], mini->av[0], envp);
	if (paths != NULL)
		free_list(&paths);
	if (envp != NULL)
		free_list(&envp);
	return (ret);
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
		mini->name = ft_strdup("🎉");
}
