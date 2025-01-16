/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnursult <dnursult@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:36:57 by Dias              #+#    #+#             */
/*   Updated: 2025/01/16 11:12:14 by dnursult         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_to_buffer(int fd, char *store)
{
	char	*buffer;
	int		read_bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(store, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		store = ft_strjoin(store, buffer);
	}
	free(buffer);
	return (store);
}

static char	*get_line(char *store)
{
	char	*line;
	int		i;

	i = 0;
	if (!store[i])
		return (NULL);
	while (store[i] && store[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (store[i] && store[i] != '\n')
	{
		line[i] = store[i];
		i++;
	}
	if (store[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*update_store(char *store)
{
	char	*new_store;
	int		i;
	int		j;

	i = 0;
	while (store[i] && store[i] != '\n')
		i++;
	if (!store[i])
	{
		free(store);
		return (NULL);
	}
	new_store = malloc(sizeof(char) * (ft_strlen(store) - i + 1));
	if (!new_store)
		return (NULL);
	i++;
	j = 0;
	while (store[i])
		new_store[j++] = store[i++];
	new_store[j] = '\0';
	free(store);
	return (new_store);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	store = read_to_buffer(fd, store);
	if (!store)
		return (NULL);
	line = get_line(store);
	store = update_store(store);
	return (line);
}
