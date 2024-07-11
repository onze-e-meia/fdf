/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:46:01 by tforster          #+#    #+#             */
/*   Updated: 2024/03/02 00:08:17 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	check_nl(t_info_nb *info_nb, int *nl)
{
	char	*new_buffer;
	char	*temp_buffer;

	new_buffer = info_nb->s_buffer;
	temp_buffer = info_nb->s_buffer;
	while (*temp_buffer)
	{
		if (*nl)
		{
			gnl_lstadd_front(&(info_nb->file), gnl_newnode(*temp_buffer));
			(info_nb->len_str)++;
			if (*temp_buffer == '\n')
				*nl = 0;
			*temp_buffer++ = '\0';
		}
		else
		{
			*new_buffer++ = *temp_buffer;
			*temp_buffer++ = '\0';
		}
	}
	*new_buffer = '\0';
}

char	*get_str(t_info_nb *info_nb)
{
	char	*str;
	char	*temp_str;
	t_char	*temp_file;

	temp_file = info_nb->file;
	str = (char *) malloc((info_nb->len_str + 1) * sizeof(char));
	if (!str)
	{
		while (temp_file)
		{
			temp_file = temp_file->next;
			gnl_clear_node(&info_nb->file);
		}
		return (NULL);
	}
	temp_str = str + info_nb->len_str;
	*temp_str-- = '\0';
	while (temp_file)
	{
		*temp_str-- = temp_file->content;
		temp_file = temp_file->next;
		gnl_clear_node(&info_nb->file);
	}
	info_nb->len_str = 0;
	return (str);
}

void	read_file(int fd, t_info_nb *info_nb)
{
	int	bytes;
	int	nl;

	bytes = 1;
	nl = 1;
	while (bytes > 0 && nl)
	{
		if (*info_nb->s_buffer)
			check_nl(info_nb, &nl);
		else
		{
			bytes = read(fd, info_nb->s_buffer, BUFFER_SIZE);
			if (bytes > 0)
			{
				*(info_nb->s_buffer + bytes) = '\0';
				check_nl(info_nb, &nl);
			}
		}
	}
}

char	*get_next_line(int fd)
{
	static t_info_nb	info_nb[1024];
	char				*str;
	int					count;

	if (fd < 0 || read(fd, info_nb[fd].s_buffer, 0))
	{
		str = info_nb[fd].s_buffer;
		count = BUFFER_SIZE;
		while (count-- > 0)
			*str++ = '\0';
		return (NULL);
	}
	read_file(fd, &info_nb[fd]);
	if (info_nb[fd].file)
	{
		str = get_str(&info_nb[fd]);
		free(info_nb[fd].file);
		return (str);
	}
	else
		free(info_nb[fd].file);
	return (NULL);
}
