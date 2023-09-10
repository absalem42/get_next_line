/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalem < absalem@student.42abudhabi.ae    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:58:01 by absalem           #+#    #+#             */
/*   Updated: 2023/09/06 08:53:05 by absalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_file_read(int fd, char *str)
{
	char	*buff;
	int		len;

	buff = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	len = 1;
	while (!ft_strchr(str, '\n') && (len != 0))
	{
		len = read(fd, buff, BUFFER_SIZE);
		if (len == -1)
		{
			free(buff);
			free(str);
			return (NULL);
		}
		buff[len] = '\0';
		str = ft_strjoin_j(str, buff);
	}
	free(buff);
	return (str);
}

char	*ft_get_line(char *str)
{
	int		i;
	char	*line_new;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line_new = (char *)malloc(sizeof(char) * (i + 2));
	if (!line_new)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line_new[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line_new[i] = str[i];
		i++;
	}
	line_new[i] = '\0';
	return (line_new);
}

char	*ft_remain(char *full_buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	while (full_buffer[i] != '\0' && full_buffer[i] != '\n')
		i++;
	if (full_buffer[i] == '\0')
	{
		free(full_buffer);
		return (NULL);
	}
	new_buffer = malloc(sizeof(char) * (ft_strlen(full_buffer) - i + 1));
	if (new_buffer == NULL)
		return (NULL);
	i++;
	if (!full_buffer[i])
		return (free(new_buffer), free(full_buffer), NULL);
	j = 0;
	while (full_buffer[i] != '\0')
		new_buffer[j++] = full_buffer[i++];
	new_buffer[j] = '\0';
	free(full_buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[10240];

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (0);
	buffer[fd] = ft_file_read(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_get_line(buffer[fd]);
	buffer[fd] = ft_remain(buffer[fd]);
	return (line);
}
