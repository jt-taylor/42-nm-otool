/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:49:56 by jtaylor           #+#    #+#             */
/*   Updated: 2020/03/05 16:09:59 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include <fcntl.h> //open
# include <sys/mman.h> //mmap
# include <sys/stat.h>//fstat
# include <mach-o/fat.h> //for fat binarys
# include <mach-o/loader.h> // mach-o
# include <mach-o/nlist.h> //for bsd / see the actual .h file
# include <ar.h> // if we wanna handle arhive'x

# include "libft.h"
# include "ft_printf.h"

# define INV_ARGS 0x01
# define FT_OTOOL_USG "A usefull help message" // fix me later

/*
** i didn't do malloc so im gonna try playing with the mmap munmap functions
*/

/*
** An incomplete list of the MACROS that we are going to use from the mach-o
** headers // archive header
**
** the magic // cigam being wheather the endienes(s?) is the same as the host
** see
** stackoverflow.com/questions/44579663/mach-o-magic-and-cigam-clarification
**
** AR_MAGIC
** AR_CIGAM
** MH_MAGIC
** MH_CIGAM
** MH_MAGIC_64
** MH_CIGAM_64
** FAT_MAGIC
** FAT_CIGAM
** FAT_MAGIC_64
** FAT_CIGAM_64
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