#include "minishell.h"

int		is_dir(char *dir)
{
	struct stat s;

	stat(dir, &s);
	return (S_ISDIR(s.st_mode));
}

int		is_exe(const char *exe_path)
{
	struct stat s;

	stat(exe_path, &s);
	return ((((s.st_mode & S_IXUSR) > 0) ? TRUE : FALSE));
}

void		print_list(char **list)
{
	int	i;

	i = -1;
	while (list[++i] != NULL)
		ft_printf("%d: %s\n", i + 1, list[i]);
}

char		*last_word_delim(char *str, int delim)
{
	char	*cd;
	int	i;
	int	j;

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

void		free_list(char ***list)
{
	char	**temp;
	int		i;

	temp = *list;
	i = -1;
	while (temp[++i] != NULL)
		free(temp[i]);
	free(temp);
}
