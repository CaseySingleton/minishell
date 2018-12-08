#include "minishell.h"

void		mini_pwd(void)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	ft_printf("%s\n", wd);
}
