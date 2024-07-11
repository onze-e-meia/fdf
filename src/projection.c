/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:50:22 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 19:01:50 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
