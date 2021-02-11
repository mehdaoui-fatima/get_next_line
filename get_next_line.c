/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 10:38:44 by fmehdaou          #+#    #+#             */
/*   Updated: 2019/12/21 15:17:22 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char *buf;
	int			n;

	if (fd < 0 || line == NULL || read(fd, buf, 0) == -1)
		return (-1);
	*line = (char*)malloc(1);
	**line = '\0';
	while (1)
	{
		if (!(buf && *buf))
			if ((buf = read_file(&buf, fd)) == NULL)
				return (0);
		if ((n = buffer_control(buf)) == -1)
		{
			*line = ft_strjoin(*line, buf);
			buf = ft_strdup("\0");
		}
		else
		{
			*line = ft_strjoin(*line, ft_substr(ft_strdup(buf), 0, n));
			buf = ft_substr(buf, n + 1, ft_strlen(buf) - 1);
			return (1);
		}
	}
}
