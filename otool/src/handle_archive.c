/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_archive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:18:36 by jtaylor           #+#    #+#             */
/*   Updated: 2020/03/10 20:49:39 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

/*
** the archive format is in ar.h
** header file
**
** copy of the header struct from the header
** struct ar_hdr
** {
**   char ar_name[16];		// Member file name, sometimes / terminated. //
**   char ar_date[12];		// File date, decimal seconds since Epoch.  //
**   char ar_uid[6], ar_gid[6];	// User and group IDs, in ASCII decimal.  //
**   char ar_mode[8];		// File mode, in ASCII octal.  //
**   char ar_size[10];		// File size, in ASCII decimal.  //
**   char ar_fmag[2];		// Always contains ARFMAG.  //
** };
*/

/*
** so archive files are just the header thens sequences of the obj files
** so we just need to go through the list in the archive and pass that to the
** mach-o parser and print the file_name
*/

/*
** https://en.wikipedia.org/wiki/Ar_(Unix)
** because archive files handle the printing of the name differently
** than the other formats , we have to either pass a flag through
** the entire mach-o parser or introduce a global .
** becuase the scope of that flag is going to be global from the file_handling
** forwards we might as well just make it global
*/

int					handle_archive(t_ft_otool *o, char *file_name)
{
	void				*tmp;
	void				*tmp2;
	struct ar_hdr		*ar_header;
	uint64_t			i;

	g_to_print_flag = 0;
	tmp = o->data + SARMAG;
	ar_header = (struct ar_hdr *)tmp;
	//write(1, &header->ar_name[0], 16);
	while (tmp && (tmp += ft_atoi(ar_header->ar_size) + sizeof(struct ar_hdr)))
	{
		ar_header = tmp;
		if (((i = ft_atoi(ar_header->ar_size)) && !i) || (o->len - (tmp - o->data) <= 0))
			return (-1);//corrupt archive header
		tmp2 = (void *)ar_header + sizeof(struct ar_hdr);//correct offset for the obj_name but not the actual obj data
		i = ft_strlen((char *)tmp2);
		ft_printf("%s(%s):\n%s\n", file_name, (char *)tmp2, FT_OTOOL_TEXT);
		while (*(char *)tmp2)
			tmp2++;
		while (!*(char *)tmp2)
			tmp2++;
		otool_handle(tmp2, (o->len - (tmp2 - o->data)), file_name);
	}
	g_to_print_flag = 1;
	return (0);
}
