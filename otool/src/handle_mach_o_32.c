/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mach_o_32.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 19:07:36 by jtaylor           #+#    #+#             */
/*   Updated: 2020/03/07 19:13:05 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** this is close to a carbon copy of the mach-o 64 file,
** just with all of the mach-o64 structs replaced with mach-o 32
*/

#include "ft_otool.h"

/*
** I think that im going to try keeping the magic // cigam in the same function
** because i think that that is goint to be
** simpler than having an almost duplicate function
*/

/*
** we don't care about the endianess for the ehxdump
*/

static void	hex_dump(void *data, size_t len_to_dump)
{
	size_t		i;
	void		*tmp;

	tmp = data;
	i = 0;
	while (i < len_to_dump)
	{
		if (i % 16 == 0)
			ft_printf("%016llx\t", i);//offset from
		ft_printf("%02llx", 0xff & ((char *)data)[i]);// only print 2 spaced hex
		if (i % 16 == 15)
			write(1, " \n", 2);
		else
			write(1, " ", 1);
		i++;
	}
	if ((len_to_dump % 16) != 0)
		write(1, "\n", 1);//so that when it end with a full line it doesn't put
							//an extra newline
}

/*
** the hexdump doesn't care about the endianess
** at least i think anyway , the man for otool-classic just says
** Display the contents of the (__TEXT,__text) section.
*/

static void	otool_hex_dump_mach_o_32_magic(void *data, size_t to_dump,
		char *file_name)
{
	if (file_name)
		ft_printf("%s:\n%s\n", file_name, FT_OTOOL_TEXT);
	hex_dump(data, to_dump);
}

/*
** go through the segments in the load command
** i don't know if its worth it to break after the __TEXT segment , i don't
** think speed really matters in this project
** so the load command has the location of the segment in the file
** so we go to that segemnt and hexdump the __TEXT segment
** the offset is relative to the start of the file
*/

static void	handle_load_command(t_ft_otool *o, void *load_cmd, size_t size,
	int swap_end)
{
	struct segment_command		*curr_segment;
	struct section				*s_32;
	uint32_t						i;

	(void)size;//implement the out of bounds check here ?
	//think i need that to make sure that there isn't any corruption of the file
	// probably easier to do it somewhere else ?
	// makeing sure that we never read out of memory is gonna be a pain :{
	curr_segment = (struct segment_command *)(load_cmd);
	s_32 = (struct section *)((void *)curr_segment +
			sizeof(struct segment_command));
	i = 0;
	while (i < ((swap_end) ? swap_uint32((uint32_t)curr_segment->nsects) :
				curr_segment->nsects))
	{
		if (ft_strequ((s_32 + i)->sectname, SECT_TEXT) &&
				ft_strequ((s_32 + i)->segname, SEG_TEXT))
				// these are from the mach-o/loader header
			(swap_end) ? otool_hex_dump_mach_o_32_magic(o->data +
swap_uint32((s_32 + i)->offset), swap_uint32((s_32 + i)->size), o->file_name)
				: otool_hex_dump_mach_o_32_magic(o->data + (s_32 + i)->offset,
						(s_32 + i)->size, o->file_name);
		i++;
	}
}

/*
** go through the load_commands in the file ,
** for each one that is a load command handle that load commnd
** the first load command is right after the mach-o header
** then each load command is right after each other
*/

void		handle_mach_o_32(t_ft_otool *o, char *file_name, int swap_end)
{
	struct mach_header		*m_header;
	struct load_command			*load_c;
	uint32_t					tmp;

	(void)file_name;
	m_header = (struct mach_header *)o->data;
	if (m_header->cputype != CPU_TYPE_X86 &&\
			m_header->cputype != CPU_TYPE_POWERPC)//im not sure which exact
		//header te CPU_TYPES are defined in, but looking through the
		//	includes in the mach-o headers
		return ;//invalid
	tmp = (swap_end) ? swap_uint32(m_header->ncmds) : m_header->ncmds;
	load_c = (struct load_command *)(o->data + sizeof(struct mach_header));
		//go to the first segment
	while (tmp--)//go through the load commands
	{
		if (((swap_end) ? swap_uint32(load_c->cmd) == LC_SEGMENT :
				load_c->cmd == LC_SEGMENT))
			handle_load_command(o, load_c, o->len, swap_end);
		//move load_c to next load command
		load_c = ((void *)load_c + ((swap_end) ? swap_uint32(load_c->cmdsize) :
					load_c->cmdsize));
	}
}