/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:12:14 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 17:48:55 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	close_gnl_fd(int fd, char *gnl_str, char *text)
{
	if (gnl_str)
		free(gnl_str);
	check_close(fd);
	error_text(text);
}

void	array_fst_check(t_map *map, int fd)
{
	if (!map->array)
	{
		if (map->colors)
			free(map->colors);
		close_gnl_fd(fd, NULL, "Could not malloc memory for ARRAY LINE.\n");
	}
	if (!map->colors)
	{
		free(map->array);
		close_gnl_fd(fd, NULL, "Could not malloc memory for COLOR LINE.\n");
	}
}

void	array_snd_check(t_map *map, char *str, int fd, int line)
{
	if (line >= 0 && !map->array[line])
	{
		if (map->colors)
			free_array((void ***) map->colors, line + 1, map->info_nb[0], 1);
		free_array((void ***) map->array, line, map->info_nb[0], 4);
		close_gnl_fd(fd, str, "Could not malloc memory for ARRAY COLUMN.\n");
	}
	if (line >= 0 && !map->colors[line])
	{
		free(map->array[line]);
		free_array((void ***) map->array, line, map->info_nb[0], 4);
		free_array((void ***) map->colors, line, map->info_nb[0], 1);
		close_gnl_fd(fd, str, "Could not malloc memory for COLOR COLUMN.\n");
	}
}

void	array_thr_check(t_map *map, char *str, int fd, int pos[2])
{
	int	line;
	int	column;
	int	i;

	line = pos[0];
	column = pos[1];
	if (column >= 0 && !map->array[line][column])
	{
		i = 0;
		while (column > i)
		{
			free(map->array[line][i]);
			i++;
		}
		free(map->array[line]);
		free_array((void ***) map->array, line, map->info_nb[0], 4);
		free_array((void ***) map->colors, line + 1, map->info_nb[0], 1);
		free(str);
		check_close(fd);
		error_text("Could not malloc memory for ELEMENT ARRAY.\n");
	}
}
