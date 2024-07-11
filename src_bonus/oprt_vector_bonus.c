/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oprt_vector_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:23:05 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 17:49:42 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	init_vector(float x, float y, float z, float vector[4])
{
	vector[0] = x;
	vector[1] = y;
	vector[2] = z;
	vector[3] = 1;
}

void	vector_mult(float vector[4], float c)
{
	vector[0] *= c;
	vector[1] *= c;
	vector[2] *= c;
	vector[3] *= c;
}

void	v_plus_v(float vec_a[4], float vec_b[4], float vector[4])
{
	vector[0] = vec_a[0] + vec_b[0];
	vector[1] = vec_a[1] + vec_b[1];
	vector[2] = vec_a[2] + vec_b[2];
	vector[3] = vec_a[3] + vec_b[3];
}

void	vector_copy(float vector[4], float copy[4])
{
	copy[0] = vector[0];
	copy[1] = vector[1];
	copy[2] = vector[2];
	copy[3] = vector[3];
}
