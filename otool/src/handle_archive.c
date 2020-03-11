/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_archive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:18:36 by jtaylor           #+#    #+#             */
/*   Updated: 2020/03/10 18:57:20 by jtaylor          ###   ########.fr       */
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
** this version is very broken ,
** im moving the pointers by the wrong offset so im just gonna rewrite this
** func because that's gonna be faster than finding whats broken
int				handle_archive(t_ft_otool *o, char *file_name)
{
//	(void)o;
//	(void)file_name;
	struct ar_hdr		*ar_header;
	void				*tmp;
	size_t				i;

	ft_printf("Archive : %s\n", file_name);
	ar_header = o->data + SARMAG;//archive header starts after the magic
									//SARMAGIC == sizeof AR_MAGIC
	tmp = ar_header;//move to the end of the header
	//ft_printf("ar_header->ar_name ::%s\n", ar_header->ar_name);
	while ((struct ar_hdr *)tmp && (tmp += ft_atoi(((struct ar_hdr *)tmp)->ar_size) + sizeof(struct ar_hdr)))//go throught the archive headers
	{
		ft_printf("inside\n");
		ar_header = (struct ar_hdr *)tmp;
		if ((i = ft_atoi(ar_header->ar_size) && !i))
			return (-1);//exit invalid archive size
		if ((void *)tmp + i + sizeof(struct ar_hdr) > o->data + o->len)
			return (-1);//would read out of the file array
		ft_printf("%s(%s)\n", file_name, (char *)((struct ar_hdr *)tmp)->ar_name - 8);// this is the wrong offset
		otool_handle(ft_atoi(((struct ar_hdr *)tmp)->ar_size) + (void *)tmp + sizeof(struct ar_hdr),
			o->len - (size_t)(ft_atoi(((struct ar_hdr *)tmp)->ar_size) + (void *)tmp + sizeof(struct ar_hdr)), file_name);
		//tmp = 0;
	}
	return (0);
}
*/

/*
** https://en.wikipedia.org/wiki/Ar_(Unix)
*/

int					handle_archive(t_ft_otool *o, char *file_name)
{
	void				*tmp;
	void				*tmp2;
	struct ar_hdr		*ar_header;
	uint64_t			i;

	i = 0;
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
		ft_printf("%s(%s)\n", file_name, (char *)tmp2);
		while (*(char *)tmp2)
			tmp2++;
		while (!*(char *)tmp2)
			tmp2++;
		otool_handle(tmp2, (o->len - (tmp2 - o->data)), file_name);
		break;//
	}
	return (0);
}
