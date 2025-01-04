/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:42:11 by Dias              #+#    #+#             */
/*   Updated: 2025/01/04 15:05:06 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_strcopy(char *dst, char *src, int src_len)
{
	int	i;

	if (!dst || !src)
		return ;
	i = 0;
	while (i < src_len && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	ft_newline_position(char *str, int size)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (i < size)
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_join(char *left, char *right, int right_len)
{
	char	*line;
	int		left_len;

	left_len = ft_strlen(left);
	line = malloc(sizeof(char) * (left_len + right_len + 1));
	if (!line)
		return (NULL);
	if (left)
		ft_strcopy(line, left, left_len);
	ft_strcopy(line + left_len, right, right_len);
	if (left)
		free(left);
	return (line);
}

char	*ft_split(char *line, int newline_position, char **remainder)
{
	char	*subline;
	int		len;

	len = ft_strlen(line);
	subline = malloc(sizeof(char) * (newline_position + 2));
	if (!subline)
		return (NULL);
	ft_strcopy(subline, line, newline_position + 1);
	if (line[newline_position + 1])
	{
		*remainder = malloc(sizeof(char) * (len - newline_position));
		if (!(*remainder))
		{
			free(line);
			return (NULL);
		}
		ft_strcopy(*remainder, line + newline_position + 1,
			len - newline_position - 1);
	}
	else
		*remainder = NULL;
	free(line);
	return (subline);
}
