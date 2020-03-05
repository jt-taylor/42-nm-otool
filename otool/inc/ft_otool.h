/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:49:56 by jtaylor           #+#    #+#             */
/*   Updated: 2020/03/04 16:27:03 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <mach-o/fat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <ar.h>

# include "libft.h"
# include "ft_printf.h"

# define INV_ARGS 0x01
# define FT_OTOOL_USG "A usefull help message" // fix me later

/*
** i didn't do malloc so im gonna try playing with the mmap munmap functions
*/

/*
** structs ---------------------------------------------------------------------
*/

typedef struct		s_ft_otool
{
	void		*data;
	size_t			len;
}					t_ft_otool;

/*
** prototypes ------------------------------------------------------------------
*/

#endif
