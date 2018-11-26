#include "minishell.h"

void		hostname(t_mini *mini)
{
	if (mini->av[1] == NULL)
		return ;
	if (mini->name)
		free(mini->name);
	mini->name = ft_strdup(mini->av[1]);
}
