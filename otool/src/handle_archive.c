/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_archive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:18:36 by jtaylor           #+#    #+#             */
/*   Updated: 2020/03/09 11:55:58 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

/*
** so archive files are just the header thens sequences of the obj files
** so we just need to go through the list in the archive and pass that to the
** mach-o parser and print the file_name
*/

int				handle_archive(t_ft_otool *o, char *file_name)
{
	(void)o;
	(void)file_name;
	return (0);
}
