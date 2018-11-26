#include "minishell.h"

char		*current_directory(char *str)
{
	char	*cd;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i - 1] == '/')
			j = 0;
		i++;
		j++;
	}
	cd = ft_strndup(str + (i - j), j);
	return (cd);
}
