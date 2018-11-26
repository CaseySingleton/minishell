/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 20:36:34 by csinglet          #+#    #+#             */
/*   Updated: 2018/04/16 20:36:36 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_toupper(int letter)
{
	if (letter >= 'a' && letter <= 'z')
	{
		letter -= 32;
	}
	return (letter);
}
