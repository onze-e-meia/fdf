/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:46:20 by tforster          #+#    #+#             */
/*   Updated: 2024/02/05 19:11:43 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_char	*gnl_newnode(char content)
{
	t_char	*lst;

	lst = malloc(sizeof(t_char));
	if (!lst)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}

void	gnl_lstadd_front(t_char **lst, t_char *new_node)
{
	if (lst && new_node)
	{
		new_node->next = *lst;
		*lst = new_node;
	}
}

void	gnl_clear_node(t_char **lst)
{
	t_char	*temp;

	if (lst && *lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		free(temp);
	}
}
