/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:37:09 by tforster          #+#    #+#             */
/*   Updated: 2024/02/19 17:37:51 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		array_col(t_map *map, char *str, int line, int fd);
static void		populate(t_map *map, char *str, char **ptr, int pos[3]);
static int		walking_atoi(char **str);
static uint32_t	walking_atoc(char **str);

void	init_array(t_map *map, int file_descriptor)
{
	int		line;
	char	*str;

	map->array = malloc(map->info_nb[1] * sizeof(float **));
	map->colors = malloc(map->info_nb[1] * sizeof(int *));
	array_fst_check(map, file_descriptor);
	str = get_next_line(file_descriptor);
	count_columns(str, &map->info_nb[0]);
	line = 0;
	while (str && map->info_nb[1] > line)
	{
		array_col(map, str, line, file_descriptor);
		line++;
		free(str);
		str = get_next_line(file_descriptor);
	}
}

static void	array_col(t_map *map, char *str, int line, int fd)
{
	int		column;
	char	*ptr;
	int		pos[3];

	ptr = str;
	map->array[line] = malloc(map->info_nb[0] * sizeof(float *));
	map->colors[line] = malloc(map->info_nb[0] * sizeof(int));
	array_snd_check(map, str, fd, line);
	pos[2] = fd;
	pos[0] = line;
	column = 0;
	while (map->info_nb[0] > column)
	{
		pos[1] = column;
		populate(map, str, &ptr, pos);
		column++;
	}
}

static void	populate(t_map *map, char *str, char **ptr, int pos[3])
{
	int	fd;
	int	line;
	int	column;

	fd = pos[2];
	line = pos[0];
	column = pos[1];
	map->array[line][column] = malloc(4 * sizeof(float));
	array_thr_check(map, str, fd, pos);
	map->array[line][column][0] = (column + 1);
	map->array[line][column][1] = (map->info_nb[1] - line);
	map->array[line][column][2] = walking_atoi(ptr);
	if (map->array[line][column][2] > map->info_nb[2])
		map->info_nb[2] = map->array[line][column][2];
	map->array[line][column][3] = 1;
	map->colors[line][column] = walking_atoc(ptr);
	if (map->colors[line][column] == 0 && map->array[line][column][2] > 0)
		map->colors[line][column] = GREY;
	else if (map->colors[line][column] == 0)
		map->colors[line][column] = WHITE;
}

static int	walking_atoi(char **str)
{
	int	sign;
	int	number;

	sign = 1;
	number = 0;
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		(*str)++;
	if (**str == '-')
	{
		sign *= -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	while (ft_isdigit(**str))
	{
		number = number * 10 + (**str - '0');
		(*str)++;
	}
	return (sign * number);
}

static uint32_t	walking_atoc(char **str)
{
	int			hex;
	uint32_t	color;
	int			power;

	color = 0;
	power = 5;
	if (!ft_strncmp(*str, ",0x", 3))
	{
		*str += 3;
		hex = -1;
		power = 7;
		while (**str && is_hexdecimal(**str))
		{
			hex++;
			if (**str == HEX_LOW[hex] || **str == HEX_UPP[hex])
			{
				color |= hex << (power * 4);
				power--;
				hex = -1;
				(*str)++;
			}
		}
		color |= 0x96;
	}
	return (color);
}
