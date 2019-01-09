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

static void		append_env_var(char **dest, char *addition)
{
	if (*dest == NULL)
		*dest = ft_strdup(addition);
	else
		*dest = ft_strjoin_free_s1(*dest, addition);
	free(addition);
	addition = NULL;
}

static int		ft_copy_until_env_var(char **dest, char *src)
{
	int			i;
	int			quote_flag;

	i = 0;
	quote_flag = 0;
	while (src[i] != '\0')
	{
		if (src[i] == '"')
		{
			while (src[i] == '"')
				i++;
			quote_flag ^= (1 << 0);
		}
		if (quote_flag == 0 && (src[i] == '$' || src[i] == '~'))
			break ;
		i++;
	}
	*dest = ft_strndup(src, i);
	return (i);
}

static int		get_var_name(char **dest, char *src)
{
	int			i;

	i = 0;
	if (*src == '~')
	{
		*dest = ft_strdup("~");
		i = 1;
	}
	else if (*src == '$')
	{
		while (src[i] != ' ' && src[i] != '\0')
			i++;
		*dest = ft_strndup(src, i);
	}
	return (i);
}

static char		*get_env_value(t_mini *m, char *name)
{
	int			i;
	char		*value;
	char		*test;

	i = 2;
	value = NULL;
	if (*name == '~' && (test = env_search(m->env, "HOME")) != NULL)
		value = ft_strdup(test);
	else if (name[1] == '-' && (test = env_search(m->env, "OLDPWD")) != NULL)
		value = ft_strdup(test);
	else if ((test = env_search(m->env, name + 1)) != NULL)
		value = ft_strdup(env_search(m->env, name + 1));
	else
		value = ft_strdup(name);
	free(name);
	name = NULL;
	return (value);
}

char			*expand_env_vars(t_mini *mini, char *src)
{
	int			bytes_copied;
	char		*expanded;
	char		*env_var_name;
	char		*env_var_value;
	char		*cut;

	bytes_copied = 0;
	expanded = NULL;
	env_var_name = NULL;
	env_var_value = NULL;
	cut = NULL;
	while (src[bytes_copied] != '\0')
	{
		bytes_copied += ft_copy_until_env_var(&cut, src + bytes_copied);
		append_env_var(&expanded, cut);
		if (src[bytes_copied] != '\0')
		{
			bytes_copied += get_var_name(&env_var_name, src + bytes_copied);
			env_var_value = get_env_value(mini, env_var_name);
			append_env_var(&expanded, env_var_value);
		}
	}
	return (expanded);
}
