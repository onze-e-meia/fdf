/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:05:20 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 19:22:07 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_color	intrplt_color(t_color start, t_color end, float step)
{
	t_color	color;

	color.r = start.r + (end.r - start.r) * step;
	color.g = start.g + (end.g - start.g) * step;
	color.b = start.b + (end.b - start.b) * step;
	color.a = start.a + (end.a - start.a) * step;
	return (color);
}
