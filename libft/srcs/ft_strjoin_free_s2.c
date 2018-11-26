/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_s2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:16:28 by csinglet          #+#    #+#             */
/*   Updated: 2018/04/20 17:16:34 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free_s2(char const *s1, char *s2)
{
	char	*new_str;
	int		len;
	int		index;

	if (s1 == NULL || s2 == NULL)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	new_str = ft_strnew(len);
	new_str[len] = '\0';
	index = 0;
	while (index < len)
	{
		if (*s1)
			new_str[index] = *s1++;
		else if (*s2)
			new_str[index] = *s2++;
		index++;
	}
	free(s2);
	return (new_str);
}
