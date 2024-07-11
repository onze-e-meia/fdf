/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:50:22 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 17:49:45 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	orthographic(float matrix[4][4], t_vol vol)
{
	matrix_unit(matrix, 0, 0);
	matrix[0][0] = 2 / (vol.right - vol.left);
	matrix[0][3] = -(vol.right + vol.left) / (vol.right - vol.left);
	matrix[1][1] = 2 / (vol.top - vol.bottom);
	matrix[1][3] = -(vol.top + vol.bottom) / (vol.top - vol.bottom);
	matrix[2][2] = -2 / (vol.far - vol.near);
	matrix[2][3] = -(vol.far + vol.near) / (vol.far - vol.near);
	matrix[3][3] = 1;
}

void	perspective(float matrix[4][4], t_vol vol)
{
	matrix_unit(matrix, 0, 0);
	matrix[0][0] = (2 * vol.near) / (vol.right - vol.left);
	matrix[0][2] = (vol.right + vol.left) / (vol.right - vol.left);
	matrix[1][1] = (2 * vol.near) / (vol.top - vol.bottom);
	matrix[1][2] = (vol.top + vol.bottom) / (vol.top - vol.bottom);
	matrix[2][2] = -(vol.far + vol.near) / (vol.far - vol.near);
	matrix[2][3] = -(2 * vol.far * vol.near) / (vol.far - vol.near);
	matrix[3][2] = -1;
}

void	partial(float matrix[4][4], t_vol vol, float part)
{
	float	ortho[4][4];
	float	persp[4][4];
	int		j;
	int		i;

	if (part < 0)
		part = 0;
	else if (part > 1)
		part = 1;
	else
		part = powf(part, (float) 1 / 12);
	orthographic(ortho, vol);
	perspective(persp, vol);
	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			matrix[j][i] = (1 - part) * persp[j][i] + part * ortho[j][i];
			i++;
		}
		j++;
	}
}
