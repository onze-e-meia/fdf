/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:49:21 by tforster          #+#    #+#             */
/*   Updated: 2024/03/01 23:53:15 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	validate_fdf(t_map *map, int file_descriptor);
static int	is_map_char(int ch);

void	count_columns(char *str, int *info_nb_x)
{
	while (*str && *str != '\n')
	{
		if (is_map_char(*str) && *(str + 1) == ' ')
		{
			while (*(++str) == ' ')
			{
				if (is_map_char(*(++str)))
					(*info_nb_x)++;
			}
		}
		else
			str++;
	}
	if (*info_nb_x > 0)
		(*info_nb_x)++;
}

int	fdf_read(t_map *map, char *file_path)
{
	char	*str;
	int		file_descriptor;

	str = ft_strnstr(file_path, ".fdf", ft_strlen(file_path));
	if (!str || (ft_strlen(file_path) - ft_strlen(str) == 0))
		error_text("Invalid file name or type, <file_name>.fdf.\n");
	file_descriptor = open(file_path, O_RDONLY);
	if (file_descriptor <= 0)
		error_text("File failed to open, negative file descriptor.\n");
	validate_fdf(map, file_descriptor);
	check_close(file_descriptor);
	file_descriptor = open(file_path, O_RDONLY);
	if (file_descriptor <= 0)
		error_text("File failed to open, negative file descriptor.\n");
	init_array(map, file_descriptor);
	check_close(file_descriptor);
	map->obj_cent[0] = (map->info_nb[0] + 1) / 2;
	map->obj_cent[1] = (map->info_nb[1] + 1) / 2;
	map->obj_cent[2] = map->info_nb[2] / 2;
	map->obj_cent[3] = map->info_nb[3];
	return (0);
}

static void	validate_fdf(t_map *map, int file_descriptor)
{
	int		bytes;
	char	buffer[BUFFER_SIZE];
	int		nb_char;
	int		i;

	bytes = 1;
	nb_char = 0;
	i = 0;
	while (bytes > 0)
	{
		i = 0;
		bytes = read(file_descriptor, buffer, BUFFER_SIZE);
		while (bytes > i)
		{
			if (!is_map_char(buffer[i]))
				error_text("Invalid char in file, not a number.\n");
			nb_char++;
			if (buffer[i++] == '\n')
				map->info_nb[1]++;
		}
		if (nb_char == 0)
			error_text("File is empty or a Dir.\n");
	}
}

static int	is_map_char(int ch)
{
	if (ch == '-' || is_hexdecimal(ch) || ch == ','
		|| ch == ' ' || ch == '\n' || ch == 'x')
		return (1);
	return (0);
}

int	is_hexdecimal(char ch)
{
	if (ft_isdigit(ch) || ('A' <= ch && ch <= 'F') || ('a' <= ch && ch <= 'f'))
		return (1);
	return (0);
}
