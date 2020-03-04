/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:48:22 by jtaylor           #+#    #+#             */
/*   Updated: 2020/03/03 19:45:56 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fot_otool.h"

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
** open the file -- check that we had permissions to open it and that != dir
** alloc memory for the file then pass to the handle func to print
** then free // munmap the memory && close the file
*/

static inline void	otool_open_file(char *file_name)
{
	int			fd;
	struct stat	tmp;

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
		//pass to handle -- handle alloc fail
		//unalloc memory
		//close fd
	}
	else//this is redundent
		return ;
	//still not sure if want to play with the munmap
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
		return (INV_ARG);
	}
}
