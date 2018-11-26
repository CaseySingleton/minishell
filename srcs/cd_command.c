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

static void	update_cd(t_mini *mini)
{
	if (mini->cd)
		free(mini->cd);
	mini->cd = current_directory(mini->ev[10]);
}

static void	previous_directory(t_mini *mini)
{
	char	*prev;

	prev = ft_strndup((mini->ev[10] + 4), ft_strlen(mini->ev[10] + 4) - ft_strlen(mini->cd) - 1);
	mini->ev[10] = ft_strjoin("PWD=", prev);
	chdir(mini->ev[10] + 4);
	free(prev);
	update_cd(mini);
}

static void	next_directory(char *dir, t_mini *mini)
{
	char	*temp;

	temp = ft_strdup(dir);
	if (temp[0] != '/')
		temp = ft_strjoin("/", temp);
	mini->ev[10] = ft_strjoin(mini->ev[10], temp);
	chdir(mini->ev[10] + 4);
	update_cd(mini);
}

void		mini_cd(char *path, t_mini *mini)
{
	if (path == NULL || ft_strcmp(path, ".") == 0)
		return ;
	if (ft_strcmp(path, "..") == 0)
		previous_directory(mini);
	else if (is_dir(path))
		next_directory(path, mini);
}
