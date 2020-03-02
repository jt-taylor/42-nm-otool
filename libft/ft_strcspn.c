/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 15:56:40 by jtaylor           #+#    #+#             */
/*   Updated: 2019/07/12 16:01:18 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcspn(char *string, char *lim)
{
	char	c;
	char	*p;
	char	*s;

	s = string;
	c = *s;
	while (c != 0)
	{
		p = lim;
		while (*p != 0)
		{
			if (c == *p)
				return (s - string);
			p++;
		}
		s++;
		c = *s;
	}
	return (s - string);
}
