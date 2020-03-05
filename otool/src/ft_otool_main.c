/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:48:22 by jtaylor           #+#    #+#             */
/*   Updated: 2020/03/04 16:29:00 by jtaylor          ###   ########.fr       */
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

int				otool_handle(void		*data, size_t len)
{
	t_ft_otool		o;
	uint32_t		*has_magic;
	uint32_t		which_magic;

	o.data = data;
	o.len = len;
	has_magic = otool_file_read_protect(&o, o.data, sizeof(uint32_t));
	if (!has_magic)
		return (0);
	which_magic = *(uint32_t *)o.data;
	//if else chain to pass to function based on which magic it has
	//
	//
	return (0);
}

/*
** open the file -- check that we had permissions to open it and that != dir
** alloc memory for the file then pass to the handle func to print
** then free // munmap the memory && close the file
*/

static inline void	otool_open_file(char *file_name)
{
	int			fd;
	struct stat	tmp;
	void		*data;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_dprintf(2, "Erorr :Opening: file_path %s\n", file_name);
	else if (!fstat(fd, &tmp))
		ft_dprintf(2, "Erorr :fstat: file_path %s\n", file_name);//and close fd
	else if (S_ISDIR(tmp.st_mode))
		ft_dprintf(2, "Erorr :IS_DIR: file_path %s\n", file_name);//and close fd
	else if (1)
	{
		//still wanna play with mmap, just using mmap should be really simple
		//even though i didn't do malloc
		//so something like
		//alloc memory
		data = mmap(0, tmp.st_size, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0);
		if (!data)
			;//exit error alloc mem
		//pass to handle -- handle alloc fail
		otool_handle(data, tmp.st_size);
		//unalloc memory
		//close fd
	}
	else//this is redundent
		return ;
	//still not sure if want to play with the munmap
	munmap(data, tmp.st_size);
	close(fd);
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
	return (0);
}
