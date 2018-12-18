/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 21:03:27 by csinglet          #+#    #+#             */
/*   Updated: 2018/12/13 21:03:30 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Notes:
**	  - Unset is broken because of env var expansion. Can't search for the
**		name anymore, gotta search for the value I guess? Or make a rule for
**		unset;
*/

int	main(int argc, char *argv[], char *envp[])
{
	minishell(envp);
	return (0);
}
