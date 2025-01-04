/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:36:57 by Dias              #+#    #+#             */
/*   Updated: 2025/01/04 15:57:26 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	remainder_check(char **remainder, char **line, int *v)
{
	if (*remainder)
	{
		*line = *remainder;
		v[2] = ft_strlen(*remainder);
		*remainder = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		buffer[BUFFER_SIZE];
	char		*line;
	int			v[3];

	if (fd < 0 || read (fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	remainder_check(&remainder, &line, v);
	v[0] = read (fd, buffer, BUFFER_SIZE);
	while (v[0] > 0)
	{
		line = ft_join(line, buffer, v[0]);
		v[2] += v[0];
		v[1] = ft_newline_position(line, v[2]);
		if (v[1] >= 0)
			return (ft_split(line, v[1], &remainder));
		v[0] = read (fd, buffer, BUFFER_SIZE);
	}
	if (line && *line)
		return (line);
	free(line);
	return (NULL);
}

/* 
v[0] -> for the amout of bytes that was read
v[1] -> the position of new line if it exists in the line
v[2] -> the overall length of the line whatever the line is
---------------------
it can be
1) NULL + BUFFER
2) REMAINDER + BUFFER
3) REMAINDER + NULL
---------------------
*/
