/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oprt_matrix_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:51:41 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 17:49:34 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	matrix_unit(float matrix[4][4], float diagonal, float other)
{
	matrix[0][0] = diagonal;
	matrix[0][1] = other;
	matrix[0][2] = other;
	matrix[0][3] = other;
	matrix[1][0] = other;
	matrix[1][1] = diagonal;
	matrix[1][2] = other;
	matrix[1][3] = other;
	matrix[2][0] = other;
	matrix[2][1] = other;
	matrix[2][2] = diagonal;
	matrix[2][3] = other;
	matrix[3][0] = other;
	matrix[3][1] = other;
	matrix[3][2] = other;
	matrix[3][3] = diagonal;
}

void	matrix_vector(float matrix[4][4], float vector[4])
{
	float	copy[4];
	int		i;

	vector_copy(vector, copy);
	i = 0;
	while (i < 4)
	{
		vector[i] = matrix[i][0] * copy[0]
			+ matrix[i][1] * copy[1]
			+ matrix[i][2] * copy[2]
			+ matrix[i][3] * copy[3];
		i++;
	}
}

void	matrix_mult(float mx_a[4][4], float mx_b[4][4], float result[4][4])
{
	int	i;
	int	j;
	int	k;

	matrix_unit(result, 0, 0);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
			{
				result[i][j] += mx_a[i][k] * mx_b[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
}
