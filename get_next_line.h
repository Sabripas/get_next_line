/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssteveli <ssteveli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:29:32 by ssteveli          #+#    #+#             */
/*   Updated: 2023/12/08 16:22:21 by ssteveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# include <libc.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_line
{
	char			*content;
	struct s_list	*next;
}					t_line;

char				*get_next_line(int fd);
int					line_len(t_line *list);
t_line				*find_last(t_line *list);
int					find_newline(t_line *list);
void				append(t_line **list, char *buf);
void				dealloc(t_line **list, t_line *clean_list, char *buff);
void				creat_line(t_line **list, int fd);
char				*ft_get_line(t_line *list);
void				clean_list(t_line **list);
void				cpy_line(char *str, t_line *list);

#endif