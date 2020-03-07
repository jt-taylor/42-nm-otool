/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_func.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:12:43 by jtaylor           #+#    #+#             */
/*   Updated: 2020/03/06 18:14:32 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_FUNC
# define SHARED_FUNC

# include <stdint.h>

/*
** the comman function between ft_nm and ft_otool ------------------------------
*/

uint64_t	swap_uint64(uint64_t);
uint32_t	swap_uint32(uint32_t);

#endif
