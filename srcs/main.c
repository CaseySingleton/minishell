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
**	  - Still need to do the thing with ENV variables
**	  - Add some cool extra stuff. Like maybe a game of some sort
*/

int	main(int argc, char *argv[], char *envp[])
{
	minishell(envp);
	while (1)
		;
	return (0);
}
