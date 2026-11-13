/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafouche <mafouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 14:57:49 by mafouche          #+#    #+#             */
/*   Updated: 2026/11/13 12:23:12 by mafouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c, int x)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
		{
			if (x == 1)
				return ((char *)&s[i + 1]);
			return ((char *)&s[i]);
		}
		i++;
	}
	if ((unsigned char)s[i] == (unsigned char)c)
	{
		if (x == 1)
			return ((char *)&s[i + 1]);
		return ((char *)&s[i]);
	}
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (size == 0)
		return (j);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*new;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	ft_strlcpy(new, s, len + 1);
	return (new);
}

char	*return_line(char	*saved)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(saved) + 2));
	while (saved[i] && saved[i] != '\n')
	{
		tmp[i] = saved[i];
		i++;
	}
	tmp[i] = '\n';
	tmp[i + 1] = '\0';
	return (tmp);
}

char	*get_line(char **saved, char **buffer, char **line, int *cnt, int fd)
{
	char	*rest;
	
	*buffer = ft_calloc((BUFFER_SIZE + 1), 1);
	if (!*buffer)
		return (NULL);
	while ((!ft_strchr(*saved, '\n', 0)) && *cnt > 0)
	{
		*cnt = read(fd, *buffer, BUFFER_SIZE);
		(*buffer)[*cnt] = '\0';
		*saved = ft_strjoin(*saved, *buffer);
	}
	*line = return_line(*saved);
	rest = ft_strdup(ft_strchr(*saved, '\n', 1));
	free(*saved);
	*saved = rest;
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*buffer;
	char		*line;
	int			cnt;

	cnt = 1;
	if (!saved)
	{
		saved = ft_calloc(1, BUFFER_SIZE);
		if (!saved)
			return (NULL);
	}
	line = get_line(&saved, &buffer, &line, &cnt, fd);
	free(buffer);
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