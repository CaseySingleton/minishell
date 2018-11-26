#include "minishell.h"

int		is_dir(char *dir)
{
	struct stat s;

	stat(dir, &s);
	return (S_ISDIR(s.st_mode));
}

void		print_list(char **list)
{
	int	i;

	i = -1;
	while (list[++i] != NULL)
		ft_printf("%d: %s\n", i + 1, list[i]);
}

char		**ft_lstdup(char **list)
{
	char	**list_cpy;
	int	i;

	i = -1;
	while (list[++i] != NULL)
		;
	if (!(list_cpy = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	list_cpy[i] = NULL;
	i = -1;
	while (list[++i] != NULL)
		list_cpy[i] = ft_strdup(list[i]);
	return (list_cpy);
}
