/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asbouani <asbouani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:34:17 by asbouani          #+#    #+#             */
/*   Updated: 2024/12/08 21:30:56 by asbouani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *str, char *buffer)
{
	char	*tmp;

	if (!str && !buffer)
		return (NULL);
	tmp = ft_strjoin(str, buffer);
	if (!tmp)
		return (NULL);
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
	if (str)
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
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	str = ft_read_file(fd, str);
	if (!str)
		str = ft_strdup("");
	line = ft_line(str);
	str = ft_next(str);
	if (!line)
	{
		free(str);
		str = NULL;
	}
	return (line);
}
