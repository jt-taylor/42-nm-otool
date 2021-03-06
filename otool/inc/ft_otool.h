/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:49:56 by jtaylor           #+#    #+#             */
/*   Updated: 2020/03/10 21:17:46 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

/*
** # include <fcntl.h> //open
** # include <sys/mman.h> //mmap
** # include <sys/stat.h>//fstat
** # include <mach-o/fat.h> //for fat binarys
** # include <mach-o/loader.h> // mach-o
** # include <mach-o/nlist.h> //for bsd / see the actual .h file
** # include <ar.h> // if we wanna handle arhive'x
*/

# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <mach-o/fat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <ar.h>

# include "libft.h"
# include "ft_printf.h"
# include "shared_func.h"

# define INV_ARGS 0x01
# define FT_OTOOL_USG "A usefull help message"
# define FT_OTOOL_TEXT "Contents of (__TEXT,__text) section"

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

extern uint8_t		g_to_print_flag;

/*
** structs ---------------------------------------------------------------------
*/

typedef struct		s_ft_otool
{
	void		*data;
	size_t		len;
	char		*file_name;
	char		to_print;
}					t_ft_otool;

/*
** prototypes ------------------------------------------------------------------
*/

void				handle_mach_o_64(t_ft_otool *o, char *file_name,
						int swap_end);
void				handle_mach_o_32(t_ft_otool *o, char *file_name,
						int swap_end);
int					otool_handle(void		*data, size_t len, char *file_name);
int					handle_fat_binary(t_ft_otool *o, char *file_name);
int					handle_archive(t_ft_otool *o, char *file_name);

#endif
