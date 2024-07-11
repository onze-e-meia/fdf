/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:46:33 by tforster          #+#    #+#             */
/*   Updated: 2024/02/14 21:22:04 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_char
{
	char			content;
	struct s_char	*next;
}					t_char;

typedef struct s_info_nb
{
	char	s_buffer[BUFFER_SIZE + 1];
	t_char	*file;
	int		len_str;
}			t_info_nb;

char	*get_next_line(int fd);
t_char	*gnl_newnode(char content);
void	gnl_lstadd_front(t_char **lst, t_char *new_node);
void	gnl_clear_node(t_char **file);

#endif
