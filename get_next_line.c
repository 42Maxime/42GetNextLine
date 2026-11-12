/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafouche <mafouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 14:57:49 by mafouche          #+#    #+#             */
/*   Updated: 2026/11/12 16:34:09 by mafouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*get_line(char **saved, char **buffer, char **line, int *cnt, int fd)
{
	*buffer = ft_calloc((BUFFER_SIZE + 1), 1);
	if (!*buffer)
		return (NULL);
	while ((!ft_strchr(*saved, '\n')) && *cnt > 0)
	{
		*cnt = read(fd, *buffer, BUFFER_SIZE);
		(*buffer)[*cnt] = '\0';
		*saved = ft_strjoin(*saved, *buffer);
	}
	return (*saved);
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
	printf("1er : %s\n", get);
	free(get);
	get = get_next_line(fd);
	printf("2eme : %s\n", get);
	free(get);
	get = get_next_line(fd);
	printf("3eme : %s\n", get);
	free(get);
	get = get_next_line(fd);
	printf("4eme : %s\n", get);
	free(get);
	return (0);
}