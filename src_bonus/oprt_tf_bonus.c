/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oprt_tf_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:39:02 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 17:49:39 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	translation(float matrix[4][4], float vector[4])
{
	matrix_unit(matrix, 1, 0);
	matrix[0][3] = vector[0];
	matrix[1][3] = vector[1];
	matrix[2][3] = vector[2];
}

void	scaling(float matrix[4][4], float value)
{
	matrix_unit(matrix, 1 * (1 + value), 0);
	matrix[3][3] = 1;
}
