/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:01:07 by smargine          #+#    #+#             */
/*   Updated: 2023/06/23 13:55:52 by smargine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = malloc(sizeof(char));
		buffer[fd][0] = '\0';
	}
	buffer[fd] = ft_read_text(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_read_line(buffer[fd]);
	buffer[fd] = ft_start_new(buffer[fd]);
	return (line);
}

char	*ft_read_text(int fd, char *buffer)
{
	char	*rd_buf;
	int		rd_bytes;

	rd_bytes = 1;
	rd_buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!rd_buf)
		return (NULL);
	while (rd_bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		rd_bytes = read(fd, rd_buf, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buffer);
			free(rd_buf);
			return (NULL);
		}
		rd_buf[rd_bytes] = '\0';
		buffer = ft_strjoin(buffer, rd_buf);
	}
	free(rd_buf);
	return (buffer);
}

char	*ft_read_line(char *buffer)
{
	char	*the_line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	the_line = malloc(sizeof(char) * (i + 1));
	if (!the_line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		the_line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		the_line[i++] = '\n';
	the_line[i] = '\0';
	return (the_line);
}

char	*ft_start_new(char *buffer)
{
	char	*start_new;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	if (buffer[i] == '\n')
		i++;
	start_new = ft_substr(buffer, i, ft_strlen(buffer) - i);
	free(buffer);
	return (start_new);
}
