/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:44:01 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 17:49:26 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	set_fdct_mov(float *type, float mov, t_mov_vec *mov_vec)
{
	*type = mov / mov_vec->fct;
	mov_vec->redraw = YES;
}

void	set_mov(float *type, float mov, t_mov_vec *mov_vec)
{
	*type = mov;
	mov_vec->redraw = YES;
}

void	set_part(float *type, float part, t_mov_vec *mov_vec)
{
	*type += part;
	if (*type < 0)
		*type = 0;
	else if (*type > 1)
		*type = 1;
	mov_vec->redraw = YES;
}
