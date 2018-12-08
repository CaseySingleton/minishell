#include "minishell.h"

void		update_pwd(t_env *env)
{
	t_env	*cur;

	cur = env;
	while (cur != NULL)
	{
		if (ft_strcmp(cur->name, "PWD") == 0)
		{
			free(cur->value);
			cur->value = getcwd(NULL, 0);
		}
		cur = cur->next;
	}
}

void		update_cd(t_mini *mini)
{
	if (mini->cd)
		free(mini->cd);
	mini->cd = last_word_delim(env_search(mini->env, "PWD"), '/');
	if (mini->cd == NULL)
		mini->cd = ft_strdup("/");
}

void		env_init(t_env **env, char *envp[])
{
	char	**params;
	int		i;

	i = -1;
	while (envp[++i] != NULL)
	{
		params = ft_strsplit(envp[i], '=');
		env_add_end(env, env_new_node(params[0], params[1], i));
		free_list(&params);
	}
}
