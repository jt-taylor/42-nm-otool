/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:48:22 by jtaylor           #+#    #+#             */
/*   Updated: 2020/03/09 11:42:40 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

/*
** -----------------------------------------------------------------------------
** so the general structure of the otool program at least otool -t
** is that for each file in the list we read the file
** then you print the filename and the contents of the __TEXT section
** theres some stuff with handling which arch the mach-o object is for
** and some bit swapping stuff and fat files are a lil different
** but it doesn't seem super complicated
**
** all otool is doing is printing the hex value of the __TEXT segment (section?)
** https://github.com/aidansteele/osx-abi-macho-file-format-reference
** -----------------------------------------------------------------------------
*/

/*
** this is so that we don't read outsid the bounds of the memory
** cur_add - start_addr + len_rto_read < len of memory
*/

void			*otool_file_read_protect(t_ft_otool *o,
		void *addr_start, size_t len_to_read)
{
	return (((addr_start - o->data) + len_to_read) > o->len) ? 0 : addr_start;
}

/*
** it's simpler to just write a function for each type at least with the
** norm restrictionse
** the magic number is at the start of the file so the pointer is the same as
** the data pointer
*/

void			otool_hanldle_inner(t_ft_otool *o, char *file_name)
{
	uint32_t		which_magic;
	void			*data;

	data = o->data;
	which_magic = *(uint32_t *)data;
	if (which_magic == MH_MAGIC || which_magic == MH_CIGAM)
		handle_mach_o_32(o, file_name, (which_magic == MH_CIGAM_64) ? 1 : 0);//handle mach-o 32
	else if (which_magic == MH_MAGIC_64 || which_magic == MH_CIGAM_64)
		handle_mach_o_64(o, file_name, (which_magic == MH_CIGAM_64) ? 1 : 0);//handle mach-o 64
	else if (which_magic == FAT_MAGIC || which_magic == FAT_CIGAM ||
				which_magic == FAT_MAGIC_64 || which_magic == FAT_CIGAM_64)
		handle_fat_binary(o, file_name);
//	else if (which_magic == AR_MAGIC || which_magic == AR_CIGAM)
//		;//think that we are supposed to handle archives
	else
		;//erorr magic incorrect
}

int				otool_handle(void		*data, size_t len, char *file_name)
{
	t_ft_otool		o;
	uint32_t		*has_magic;

	o.data = data;
	o.len = len;
	o.file_name = file_name;
	has_magic = otool_file_read_protect(&o, o.data, sizeof(uint32_t));
	if (!has_magic)
	{
		ft_printf("%s: is not an object flie\n", file_name);
		return (0);
	}
	otool_hanldle_inner(&o, file_name);
	return (0);
}

/*
** open the file -- check that we had permissions to open it and that != dir
** alloc memory for the file then pass to the handle func to print
** then free // munmap the memory && close the file
*/

static inline int	otool_open_file(char *file_name)
{
	int			fd;
	struct stat	tmp;
	void		*data;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (ft_dprintf(2, "Erorr :Opening: \'%s\'\n", file_name));
	else if (fstat(fd, &tmp))
		return (ft_dprintf(2, "Erorr :fstat: \'%s\'\n", file_name));//and close fd
	else if (S_ISDIR(tmp.st_mode))
		return (ft_dprintf(2, "Erorr :IS_DIR: \'%s\'\n", file_name));//and close fdk
	else if (1)
	{
		//still wanna play with mmap, just using mmap should be really simple
		//even though i didn't do malloc
		//so something like
		//alloc memory the man says MAP_FILE is the default and doesn't need to be specified
		data = mmap(0, tmp.st_size, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0);
		if (!data)
			;//exit error alloc mem
		//pass to handle -- handle alloc fail
		otool_handle(data, tmp.st_size, file_name);
		//unalloc memory
		//close fd
	}
	else//this is redundent
		return (0);
	//still not sure if want to play with the munmap
	munmap(data, tmp.st_size);
	close(fd);
	return (0);
}

static inline void	process_file_list(char **file_list, int file_count)
{
	int			i;

	i = 0;
	while (i < file_count)
	{
		//open && validate file;
		otool_open_file(file_list[i]);
		//process the file;
		//close the file
		//continue;
		i++;
	}
}

int		main(int ac, char **argv)
{
	if (ac < 2)
	{
		ft_dprintf(2, "ft_otool: missing file arglist\n");
		return (INV_ARGS);
	}
	process_file_list(argv + 1, ac - 1);
	//system("leaks a.out");
:wa
	return (0);
}
