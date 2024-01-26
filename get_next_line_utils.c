/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssteveli <ssteveli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:56:34 by ssteveli          #+#    #+#             */
/*   Updated: 2023/12/08 16:21:13 by ssteveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	cpy_line(char *str, t_line *list)
{
	int	i;
	int	k;

	if (!list)
		return ;
	k = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = list->content[i++];
		}
		list = list->next;
	}
	str[k] = '\0';
}

int	line_len(t_line *list)
{
	int	i;
	int	len;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		list = list->next;
	}
	return (len);
}

t_list	*find_last(t_line *list)
{
	if (!list)
		return (0);
	while (list->next)
	{
		list = list->next;
	}
	return (list);
}

int	find_newline(t_line *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->content[i] && i < BUFFER_SIZE)
		{
			if (list->content[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void	append(t_line **list, char *buf)
{
	t_line	*new_list;
	t_line	*last_list;

	last_list = find_last(*list);
	new_list = malloc(sizeof(t_list));
	if (!new_list)
		return ;
	if (!last_list)
		*list = new_list;
	else
		last_list->next = new_list;
	new_list->content = buf;
	new_list->next = 0;
}
