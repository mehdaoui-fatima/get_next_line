/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:00:32 by fmehdaou          #+#    #+#             */
/*   Updated: 2019/12/21 14:57:14 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		buffer_control(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*read_file(char **buf, int fd)
{
	char	*str;
	int		x;

	str = (char*)malloc(BUFFER_SIZE + 1);
	if (!str)
		return (str);
	if ((x = read(fd, str, BUFFER_SIZE)) <= 0)
	{
		free(str);
		free(*buf);
		return (NULL);
	}
	str[x] = '\0';
	free(*buf);
	*buf = ft_strjoin(ft_strdup(""), str);
	return (*buf);
}

int		get_next_line(int fd, char **line)
{
	static char *buf[4864];
	int			n;

	if (fd < 0 || fd > 4864 || line == NULL || read(fd, buf[fd], 0) == -1)
		return (-1);
	*line = (char*)malloc(1);
	**line = '\0';
	while (1)
	{
		if (!(buf[fd] && *buf[fd]))
			if ((buf[fd] = read_file(&buf[fd], fd)) == NULL)
				return (0);
		if ((n = buffer_control(buf[fd])) == -1)
		{
			*line = ft_strjoin(*line, buf[fd]);
			buf[fd] = ft_strdup("\0");
		}
		else
		{
			*line = ft_strjoin(*line, ft_substr(ft_strdup(buf[fd]), 0, n));
			buf[fd] = ft_substr(buf[fd], n + 1, ft_strlen(buf[fd]) - 1);
			return (1);
		}
	}
}
