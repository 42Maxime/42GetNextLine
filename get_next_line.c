/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafouche <mafouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 14:57:49 by mafouche          #+#    #+#             */
/*   Updated: 2026/11/12 15:39:57 by mafouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char **saved, char **buffer, char **line, int *cnt, int fd)
{
	while (*cnt > 0 /*&& no line in my static*/)
	{
		*buffer = ft_calloc(1, BUFFER_SIZE);
		if (!buffer)
			return (NULL);
		*cnt = read(fd, buffer, BUFFER_SIZE);
	}
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*buffer;
	char		*line;
	int			cnt;

	cnt = 1;
/*	if (!saved)
	{
		saved = ft_calloc(1, BUFFER_SIZE);
		if (!saved)
			return (NULL);
	}*/
	line = get_line(&saved, &buffer, &line, &cnt, fd);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*get;

	fd = open("hello.txt", O_RDONLY);

	get = get_next_line(fd);
	free(get);
	get = get_next_line(fd);
	free(get);
	get = get_next_line(fd);
	free(get);
	get = get_next_line(fd);
	free(get);
	return (0);
}