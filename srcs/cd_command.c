#include "minishell.h"

// Camp Erin - Something about more horses and supplies
// Merkshore - kinda remember the name but not much else

// Sourflask

// Cult info
//	- Name: The Hung
//	- 10 families thought to be involved
//	- Population ~300 people
//	- Growlrum family is powerful
//	- Under the skin of the neck there's an iron band
//		- Can not see it but it can be felt
//		- When prompted to give information abou the cult the band shrinks
//		  and kills the cult member
//	- Call their leader Nanny
//	- Communication between people of power and cultists is never direct
//	Bonus: While a cultist was being choked by the ring, called leader Nanny Noose
//	       8ft tall kinda grotesque

// Weird house North/East from camp
//	- Not sure what's going on but somethings happens there

// Carol's thing
//	- Residence is South/East from camp

// Lisa Parovich
//	- Dead?
//	- Lived after being stabbed
//	- Confirmed that brother tried to kill her

// Journal
//	- Uncle Brom
//	- Carol left to get paladins
//	- Last entry 4 days ago

// Growlrum Family
//	- Green Rock Manor
//	- Powerful family
//	- Built at the bottom of collapsed hillside
//	- Hillside leaks water forming a natural pool

// Merkshore
//	- Docking town
//	- Basic town

static void	explicit_directory(char *path, t_mini *mini)
{
	chdir(path);
	update_pwd(mini->env);
	update_cd(mini);
}

static void	previous_directory(t_mini *mini)
{
	chdir("..");
	update_pwd(mini->env);
	update_cd(mini);
}

static void	next_directory(char *dir, t_mini *mini)
{
	char	*next;

	next = ft_strjoin("./", dir);
	chdir(next);
	free(next);
	update_pwd(mini->env);
	update_cd(mini);
}

void		special(t_mini *mini)
{
	char	*path_complete;

	path_complete = NULL;
	if (mini->av[1] == NULL)
		return ;
	else if (mini->av[1][0] == '~')
	{
		if (mini->av[1][1] != '\0')
			path_complete = ft_strjoin(env_search(mini->env, "HOME"), mini->av[1] + 1);
		else
			path_complete = ft_strdup(env_search(mini->env, "HOME"));
	}
	else if (is_dir(mini->av[1]) == TRUE)
		path_complete = ft_strdup(mini->av[1]);
	if (is_dir(path_complete) == TRUE)
	{
		explicit_directory(path_complete, mini);
		free(path_complete);
	}
	else
		ft_printf("%s: not a valid directory\n", path_complete);
}

void		mini_cd(char *path, t_mini *mini)
{
	if (path == NULL || ft_strcmp(path, ".") == 0)
		return ;
	else if (path[0] == '~' || ft_strcmp(path, "/tmp") == 0)
		special(mini);
	else if (ft_strcmp(path, "..") == 0)
		previous_directory(mini);
	else if (is_dir(path))
		next_directory(path, mini);
	else
		ft_printf("%s: not a valid directory\n", path);
}
