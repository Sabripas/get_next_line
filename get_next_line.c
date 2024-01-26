/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssteveli <ssteveli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:33:30 by ssteveli          #+#    #+#             */
/*   Updated: 2023/12/08 16:21:58 by ssteveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	dealloc(t_line **list, t_line *clean_list, char *buff)
{
	t_line	*temp;

	if (!(*list))
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = temp;
	}
	*list = 0;
	if (clean_list->content[0])
		*list = clean_list;
	else
	{
		free(clean_list);
		free(buff);
	}
}

void	creat_list(t_line **list, int fd)
{
	char	*buf;
	int		ret;

	while (!find_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return ;
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret <= 0)
		{
			free(buf);
			return ;
		}
		buf[ret] = '\0';
		append(list, buf);
	}
}

char	*ft_get_line(t_line *list)
{
	char	*new_line;
	int		len;

	if (!list)
		return (0);
	len = line_len(list);
	new_line = malloc(len + 1);
	if (!new_line)
		return (0);
	cpy_line(new_line, list);
	return (new_line);
}

void	clean_list(t_line **list)
{
	t_line	*clean_list;
	t_line	*last_list;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_list = malloc(sizeof(t_list));
	if (!buf || !clean_list)
		return ;
	last_list = find_last(*list);
	i = 0;
	k = 0;
	while (last_list->content[i] && last_list->content[i] != '\n')
		++i;
	while (last_list->content[i] && last_list->content[++i])
		buf[k++] = last_list->content[i];
	buf[k] = '\0';
	clean_list->content = buf;
	clean_list->next = 0;
	dealloc(list, clean_list, buf);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*new_line;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, &new_line, 0) < 0)
		return (0);
	creat_list(&list, fd);
	if (!list)
		return (0);
	new_line = ft_get_line(list);
	clean_list(&list);
	return (new_line);
}
