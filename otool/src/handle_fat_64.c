/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat_64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 12:57:00 by jtaylor           #+#    #+#             */
/*   Updated: 2020/03/10 21:02:02 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

/*
** for a better documented explanation of what all of the functions are doing
** look at the mach-o 64 functions because that is what all these are modified
** off of
*/

/*
** so most of these are going to be the same as how im handling the mach-o files
** because these are just multiple mach-o files grouped together ,
** im thinking that we can look at the fat_header and if there are mach-o files
** in it then i think we only read the first one --
** the otool command line shim only prints one instance of the text section
** probably because they should be the same but im not sure that we even need to
** handle the fat/universal binarys or the archives im just assumeing that i need
** to
*/

static int	pass_to_otool_handle(void *data, char *file_name, t_ft_otool *o)
{
	return (otool_handle(data, (o->len - ((uint64_t)data - (uint64_t)o->data)),
				file_name));
}

int		handle_fat_binary_64(t_ft_otool *o, char *file_name)
{
	struct fat_header		*f_header;
	struct fat_arch_64				*f_arch;
	uint32_t				num_of_arches;

	f_header = (struct fat_header *)o->data;
	if (f_header->magic == FAT_MAGIC_64 || f_header->magic == FAT_CIGAM_64)
		return (handle_fat_binary_64(o, file_name));
	num_of_arches = f_header->nfat_arch;
	num_of_arches = (f_header->magic == FAT_CIGAM) ? swap_uint32(num_of_arches) :
		num_of_arches;
	if (!num_of_arches)
		return (2);//no arches in fat file ??
	f_arch = o->data + sizeof(struct fat_header);
	return (pass_to_otool_handle((o->data + ((f_header->magic == FAT_CIGAM) ?
			swap_uint32(f_arch->offset) : f_arch->offset)), file_name,
				o));
}

/*
** basically what this is doing is reading the fat_header and then going to the
** first arch entry and handling that
*/

/*
** im not sure how the fat header decides the endieness of itself ,
** or if it's 6x vs 32 bit binary but thats not super relavent to
** actually printing the data
*/

int		handle_fat_binary(t_ft_otool *o, char *file_name)
{
	struct fat_header		*f_header;
	struct fat_arch				*f_arch;
	uint32_t				num_of_arches;

	f_header = (struct fat_header *)o->data;
	if (f_header->magic == FAT_MAGIC_64 || f_header->magic == FAT_CIGAM_64)
		return (handle_fat_binary_64(o, file_name));
	num_of_arches = f_header->nfat_arch;
	num_of_arches = (f_header->magic == FAT_CIGAM) ? swap_uint32(num_of_arches) :
		num_of_arches;
	if (!num_of_arches)
		return (2);//no arches in fat file ??
	f_arch = o->data + sizeof(struct fat_header);
	return (pass_to_otool_handle((o->data + ((f_header->magic == FAT_CIGAM) ?
			swap_uint32(f_arch->offset) : f_arch->offset)), file_name,
				o));
}
