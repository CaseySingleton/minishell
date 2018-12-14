#include "minishell.h"

t_env		*env_new_node(char *name, char *value)
{
	t_env	*new_node;

	if (!(new_node = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

void		env_push(t_env **list, t_env *to_add)
{
	t_env	*cur;

	if (*list == NULL)
	{
		*list = to_add;
		return ;
	}
	cur = *list;
	to_add->next = *list;
	*list = to_add;
}

void		env_free_node(t_env **node)
{
	t_env	*cur;

	cur = *node;
	free(cur->name);
	free(cur->value);
	free(cur);
	cur = NULL;
}

void		env_free(t_env **list)
{
	t_env	*cur;

	cur = *list;
	if (cur == NULL)
		return ;
	env_free(&cur->next);
	free(cur);
}

char		*env_search(t_env *env, char *name)
{
	t_env	*cur;

	cur = env;
	while (cur != NULL)
	{
		if (ft_strcmp(cur->name, name) == 0)
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}
