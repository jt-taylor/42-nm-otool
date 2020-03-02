/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstart_w_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 18:17:15 by jtaylor           #+#    #+#             */
/*   Updated: 2019/08/09 13:52:41 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strstart_w_str(char *str, char *s)
{
	int		i;

	i = 0;
	if (str == NULL || s == NULL)
		return (0);
	while (s[i])
	{
		if (str[i] != s[i])
			break ;
		i++;
	}
	if (s[i] == '\0')
		return (1);
	return (0);
}
