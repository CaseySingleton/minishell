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
		env_push(env, env_new_node(params[0], params[1]));
		free_list(&params);
	}
}

int			mini_env(t_env *env)
{
	int		i;

	if (env == NULL)
		return (0);
	i = mini_env(env->next) + 1;
	ft_printf("%d: %s=%s\n", i, env->name, env->value);
	return (i);
}

void		env_set(t_mini *mini)
{
	int		i;

	i = -1;
	while (mini->av[0][++i] != '\0')
	{
		if (mini->av[0][i] < 'A' || mini->av[0][i] > 'Z')
		{
			ft_printf("%s: Invalid syntax\n", mini->av[0]);
			return ;
		}
	}
	env_push(&mini->env, env_new_node(mini->av[0], mini->av[2]));
}

void		env_unset(t_mini *mini)
{
	t_env	*cur;
	t_env	*next;
	t_env	*prev;

	cur = mini->env;
	prev = NULL;
	while (cur != NULL)
	{
		if (ft_strcmp(cur->name, mini->av[1]) == 0)
		{
			next = cur->next;
			env_free_node(&cur);
			if (prev == NULL)
				mini->env = next;
			else
				prev->next = next;
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
	ft_printf("unset: %s: Invalid environment variable\n", mini->av[1]);
}
