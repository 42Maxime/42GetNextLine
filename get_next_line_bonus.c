/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafouche <mafouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 14:57:49 by mafouche          #+#    #+#             */
/*   Updated: 2026/11/13 16:19:45 by mafouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*new;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	while (s[i] && i < len)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*return_line(char *saved)
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
	if (saved[i] == '\n')
		tmp[i++] = '\n';
	tmp[i] = '\0';
	return (tmp);
}

char	*get_line(char **saved, char **buffer, char **line, int fd)
{
	int		cnt;
	char	*rest;

	cnt = 1;
	*buffer = malloc(BUFFER_SIZE + 1);
	if (!*buffer)
		return (NULL);
	while ((!ft_strchr(*saved, '\n', 0)) && cnt > 0)
	{
		cnt = read(fd, *buffer, BUFFER_SIZE);
		if (cnt < 0)
		{
			free(*saved);
			*saved = NULL;
			return (NULL);
		}
		(*buffer)[cnt] = '\0';
		*saved = ft_strjoin(*saved, *buffer);
	}
	if (!*saved || !(*saved)[0])
	{
		free(*saved);
		*saved = NULL;
		return (NULL);
	}
	*line = return_line(*saved);
	rest = ft_strdup(ft_strchr(*saved, '\n', 1));
	free(*saved);
	*saved = rest;
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*saved[MAX_FD];
	char		*buffer;
	char		*line;

	if (fd < 0 || fd >= MAX_FD)
		return (NULL);
	if (!saved[fd])
	{
		saved[fd] = ft_calloc(1, 1);
		if (!saved[fd])
			return (NULL);
	}
	line = get_line(&saved[fd], &buffer, &line, fd);
	free(buffer);
	return (line);
}

/*int	main(void)
{
	int		fd;
	char	*get;

	fd = open("hello.txt", O_RDONLY);

	get = get_next_line(fd);
	printf("1er : %s", get);
	free(get);
	get = get_next_line(fd);
	printf("2eme : %s", get);
	free(get);
	get = get_next_line(fd);
	printf("3eme : %s", get);
	free(get);
	get = get_next_line(fd);
	printf("4eme : %s", get);
	free(get);
	get = get_next_line(fd);
	printf("5eme : %s", get);
	free(get);
	get = get_next_line(fd);
	printf("6eme : %s", get);
	free(get);
	get = get_next_line(fd);
	printf("7eme : %s", get);
	free(get);
	get = get_next_line(fd);
	printf("8eme : %s", get);
	free(get);
	get = get_next_line(fd);
	printf("9eme : %s", get);
	free(get);
	close(fd);
	return (0);
}*/
