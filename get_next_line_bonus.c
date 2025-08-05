/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:53:43 by asbouani          #+#    #+#             */
/*   Updated: 2024/12/08 21:31:26 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char *str, char *buffer)
{
	char	*tmp;

	if (!str && !buffer)
		return (NULL);
	tmp = ft_strjoin(str, buffer);
	free(str);
	str = NULL;
	return (tmp);
}

char	*ft_next(char *str)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (free(str), NULL);
	line = malloc(sizeof(char) * ft_strlen(str) - i + 1);
	if (!line)
		return (free(str), NULL);
	i++;
	j = 0;
	while (str[i])
		line[j++] = str[i++];
	line[j] = '\0';
	free(str);
	str = NULL;
	return (line);
}

char	*ft_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = NULL;
	if (str[i] == '\n')
		line = malloc(sizeof(char) * (i + 2));
	else if (str[i] == '\0')
		line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_read_file(int fd, char *str)
{
	char	*buffer;
	ssize_t	bytes;

	buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (free(str), NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			free(str);
			return (NULL);
		}
		buffer[bytes] = '\0';
		str = ft_free(str, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	buffer = NULL;
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX || BUFFER_SIZE > INT_MAX)
		return (NULL);
	str[fd] = ft_read_file(fd, str[fd]);
	if (!str[fd])
		str[fd] = ft_strdup("");
	line = ft_line(str[fd]);
	str[fd] = ft_next(str[fd]);
	if (!line)
	{
		free(str[fd]);
		str[fd] = NULL;
	}
	return (line);
}
