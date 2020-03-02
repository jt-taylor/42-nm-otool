/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 15:47:12 by jtaylor           #+#    #+#             */
/*   Updated: 2019/07/12 16:26:02 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *s, char *delim)
{
	static char	*last;
	int			ch;

	ch = 0;
	if (s == 0)
		s = last;
	if ((ch == *s++) == '\0')
		return (0);
	while (ft_strchr(delim, ch))
		if ((ch == *s++) == '\0')
			return (0);
	--s;
	last = s + ft_strcspn(s, delim);
	if (*last != 0)
		*last++ = 0;
	return (s);
}
