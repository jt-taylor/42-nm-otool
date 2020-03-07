/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mach_o_64.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:06:52 by jtaylor           #+#    #+#             */
/*   Updated: 2020/03/06 20:13:21 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	hex_dump(void *data, size_t len_to_dump)
{
	size_t		i;
	void		*tmp;

	tmp = data;
	i = 0;
	while (i < len_to_dump)
	{
		if (i % 16 == 0)
			ft_printf("%16.16llx\t", data + i);
		ft_printf("%2.2x", 0xff & ((char *)data)[i]);//so we only print 2 cchar
		write(1, " ", 1);
		if (i % 16 == 15)
			write(1, "\n", 1);
		i++;
	}
}

static void	otool_hex_dump_mach_o_64_magic(void *data, size_t to_dump)
{
	hex_dump(data, to_dump);
}

void	otool_hex_dump_mach_o_64_cigam()
{
;
}

/*
** so the load command has the location of the segment in the file
** so we go to that segemnt and hexdump the __TEXT segment
*/

static void	handle_load_command(t_ft_otool *o, void *load_cmd, size_t size,
	int swap_end)
{
	(void)o;//ill need this later i think
	struct segment_command_64		*curr_segment;
	struct section_64				*s_64;
	uint64_t								i;

	curr_segment = (struct segment_command_64 *)(load_cmd);
	s_64 = (struct section_64 *)((void *)curr_segment + sizeof(struct segment_command_64));//isn't the second part always the size of the pointer? or am i begin dumb
	i = 0;
	while (i < ((swap_end) ? swap_uint64((uint64_t)curr_segment->nsects) : curr_segment->nsects))
	{
		if (ft_strequ((s_64 + i)->sectname, SECT_TEXT) && ft_strequ((s_64 + i)->segname, SEG_TEXT))// these are from the mach-o/loader header
			otool_hex_dump_mach_o_64_magic(load_cmd + (s_64 + i)->offset, size);
		i++;
	}
}

void		handle_mach_o_64(t_ft_otool *o, char *file_name, int swap_end)
{
	struct mach_header_64		*m_header;
	struct load_command			*load_c;
	uint32_t					tmp;

	if (file_name)
		ft_printf("%s\n", file_name);
	m_header = (struct mach_header_64 *)o->data;
	if (m_header->cputype != CPU_TYPE_X86_64 && m_header->cputype != CPU_TYPE_POWERPC64)//im not sure which exact header te CPU_TYPES are defined in, but looking through the includes in the mach-o headers
		//probably isn't important
		return ;//invalid
	tmp = (swap_end) ? swap_uint64(m_header->ncmds) : m_header->ncmds;
	load_c = (struct load_command *)(o->data + sizeof(struct mach_header_64));//go to the first segment
	while (tmp--)//go through the load commands
	{
		//if load_c ->parse_segments
		if (((swap_end) ? swap_uint64(load_c->cmd) == LC_SEGMENT_64 :
				load_c->cmd == LC_SEGMENT_64))
			//function to actually parse the load_c
			handle_load_command(o, load_c, o->len, swap_end);
		//move load_c to next load command
		load_c += load_c->cmdsize;//set end
	}
}
