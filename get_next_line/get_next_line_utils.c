/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:07:03 by aankote           #+#    #+#             */
/*   Updated: 2023/03/31 01:35:54 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_n(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

void	ft_bzero_o(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}

void	*ft_calloc_c(size_t count, size_t size)
{
	char	*ptr;

	if (count && size > SIZE_MAX / count)
		return (0);
	ptr = (char *)malloc(count * size);
	if (!ptr)
		return (0);
	ft_bzero_o(ptr, count * size);
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if ((char)c == 0)
		return ((char *)s + ft_strlen_n(s));
	while (i < ft_strlen_n(s))
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}

char	*ft_strjoin_n(char const *s1, char const *s2)
{
	int		i;
	int		j;
	size_t	total_size;
	char	*newstr;

	i = 0;
	j = 0;
	if (!s1)
		return (0);
	total_size = ft_strlen_n(s1) + ft_strlen_n(s2);
	newstr = malloc(sizeof(char) * (total_size + 1));
	if (!newstr)
		return (0);
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[j])
		newstr[i++] = s2[j++];
	newstr[i] = '\0';
	return (newstr);
}
