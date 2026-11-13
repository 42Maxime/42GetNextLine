/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafouche <mafouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 14:59:38 by mafouche          #+#    #+#             */
/*   Updated: 2026/11/13 12:51:26 by mafouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;
	size_t	n;

	if (nmemb != 0 && size > (size_t)-1 / nmemb)
		return (NULL);
	if (nmemb <= 0 || size <= 0)
	{
		str = malloc(1);
		if (!str)
			return (NULL);
		ft_bzero(str, 1);
		return (str);
	}
	str = malloc(nmemb * size);
	if (str == NULL)
		return (NULL);
	n = nmemb * size;
	ft_bzero(str, n);
	return ((void *)str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	x = ft_strlen(s2);
	str = malloc(sizeof(char) * (i + x) + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, i);
	ft_memcpy(&str[i], s2, x);
	str[i + x] = '\0';
	free(s1);
	return (str);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (!dest && !src)
		return (dest);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		*d = *s;
		d++;
		s++;
		i++;
	}
	return (dest);
}
