/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mach_o_64.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:06:52 by jtaylor           #+#    #+#             */
/*   Updated: 2020/03/05 23:17:15 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	otool_hex_dump_mach_o_64(

static void	handle_print(ft_otool *o, void *load_cmd, size_t size)
{
	
}

void		handle_mach_o_64(t_ft_otool *o, char *file_name, int swap_end)
{
	struct mach_header_64		*m_header;
	struct load_command			*load_c;
	uint32_t					tmp;

	if (file_name)
		ft_printf("%s\n", file_name);
	m_header = (struct mach_header *)o.data;
	if (m_header->cputype != CPU_TYPE_X86_64 && m_header->cputype != CPU_TYPE_POWERPC_64)
		return ;//invalid
	tmp = (swap_end) ? /*swap_int64(m_header->ncmds)*/ : m_header->ncmds;//i somehow don't have a swap int writen yet
	load_c = o->data + sizeof(mach_header_64);//go to the first segment
	while (tmp--)//go through the load commands
	{
		//if load_c ->parse_segments
		if ((swap_end) ? /*swap_int64(load_c->cmd)*/ == LC_SEGMENT_64 :
				load_c->cmd == LC_SEGMENT_64)
			//function to actually parse the load_c
		//move load_c to next load command
		load_c += load_c->cmdsize;
	}
}
