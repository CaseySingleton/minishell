/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 21:03:07 by csinglet          #+#    #+#             */
/*   Updated: 2018/12/13 21:03:08 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_dir(char *dir)
{
	struct stat	s;

	stat(dir, &s);
	return (S_ISDIR(s.st_mode));
}

int				is_exe(const char *exe_path)
{
	struct stat	s;

	stat(exe_path, &s);
	return ((((s.st_mode & S_IXUSR) > 0) ? TRUE : FALSE));
}

char			**env_to_list(t_env *env)
{
	t_env		*cur;
	char		**list;
	int			len;

	cur = env;
	len = 0;
	while (cur != NULL)
	{
		cur = cur->next;
		len++;
	}
	if (!(list = (char **)malloc(sizeof(char *) * len + 1)))
		return (NULL);
	list[len] = NULL;
	cur = env;
	while (cur != NULL)
	{
		list[--len] = ft_strjoin(cur->name, "=");
		list[len] = ft_strjoin_free_s1(list[len], cur->value);
		cur = cur->next;
	}
	return (list);
}

char			*last_word_delim(char *str, int delim)
{
	char		*cd;
	int			i;
	int			j;

	cd = NULL;
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i - 1] == delim)
			j = 0;
		i++;
		j++;
	}
	if (i != 0)
		cd = ft_strndup(str + (i - j), j);
	return (cd);
}

void			free_list(char ***list)
{
	char		**temp;
	int			i;

	temp = *list;
	i = -1;
	while (temp[++i] != NULL)
		free(temp[i]);
	free(temp);
}
