/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 23:16:30 by csinglet          #+#    #+#             */
/*   Updated: 2018/12/14 23:16:31 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_env_var(char *str)
{
	int			i;

	i = -1;
	if (str[0] == '$' && str[1] == '(')
		while (str[++i] != '\0')
			if (str[i] == ')')
				return (TRUE);
	return (FALSE);
}

static char		*get_env_var(t_mini *mini, char *src)
{
	int			i;
	char		*value;
	char		*env_name;
	char		*test;

	i = 2;
	value = NULL;
	env_name = NULL;
	if (src[0] == '~' && (test = env_search(mini->env, "HOME")) != NULL)
		value = ft_strdup(test);
	else if (src[0] == '-' && (test = env_search(mini->env, "OLDPWD")) != NULL)
		value = ft_strdup(test);
	else if (is_env_var(src) == TRUE)
	{
		i += ft_copy_until(&env_name, src + 2, ')');
		if ((test = env_search(mini->env, env_name)) != NULL)
			value = ft_strdup(env_search(mini->env, env_name));
		if (env_name)
		{
			free(env_name);
			env_name = NULL;
		}
	}
	return (value);
}

static int		skip_env_var(char *src)
{
	int			i;

	i = 0;
	if (src[i] == '~')
		;
	else if (src[i] == '$' && src[i + 1] == '(')
	{
		while (src[i] != ')' && src[i] != '\0')
			i++;
		if (src[i] == '\0')
			return (0);
	}
	return (i + 1);
}

static void		append_env_var(char *src, char **expanded, char *env_value,
								int i)
{
	if (*expanded == NULL && i == 0)
		*expanded = ft_strdup(env_value);
	else if (*expanded == NULL && i > 0)
		*expanded = ft_strjoin_free_s1(ft_strndup(src, i), env_value);
	else
	{
		*expanded = ft_strjoin_free(*expanded, ft_strndup(src, i));
		*expanded = ft_strjoin_free_s1(*expanded, env_value);
	}
}

char			*expand_env_vars(t_mini *mini, char *src)
{
	int			i[3];
	char		*expanded;
	char		*env_value;

	ft_bzero(i, sizeof(int) * 3);
	expanded = NULL;
	while (src[i[0]] != '\0')
	{
		if (src[i[0]] == '"')
			i[2] = (i[2] == TRUE ? FALSE : TRUE);
		if (!i[2] && (env_value = get_env_var(mini, src + i[0])) != NULL)
		{
			append_env_var(src + i[1], &expanded, env_value, i[0] - i[1]);
			i[0] += skip_env_var(src + i[0]);
			free(env_value);
			i[1] = i[0];
		}
		else
			i[0]++;
	}
	if (expanded != NULL)
		expanded = ft_strjoin_free_s1(expanded, src + i[1]);
	else
		expanded = ft_strdup(src);
	return (expanded);
}
