/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_swap_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 16:53:35 by jtaylor           #+#    #+#             */
/*   Updated: 2020/03/06 18:15:00 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

uint64_t	swap_uint64(uint64_t t)
{
	uint64_t x = (uint64_t)t;
	x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
	x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
	x = (x & 0x00FF00FF00FF00FF) << 8  | (x & 0xFF00FF00FF00FF00) >> 8;
	return (x);
}

uint32_t	swap_uint32(uint64_t t)
{
	t = ((t << 8) & 0xFF00FF00) | ((t >> 8) & 0xFF00FF);
	return ((t << 16) | (t >> 16));
}
