/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:06:10 by aankote           #+#    #+#             */
/*   Updated: 2023/03/31 01:36:10 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_free(char *sta_buff, char *buff)
{
	char	*temp;

	temp = ft_strjoin_n(sta_buff, buff);
	free(sta_buff);
	return (temp);
}

char	*get_read(int fd, char *res)
{
	char	*buff;
	int		bytes;

	bytes = 1;
	if (!res)
		res = ft_calloc_c(1, 1);
	buff = ft_calloc_c(BUFFER_SIZE + 1, 1);
	while (bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buff);
			free(res);
			return (NULL);
		}
		buff[bytes] = '\0';
		res = join_free(res, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (res);
}

char	*ft_get_line(char *buff)
{
	int		i;
	char	*line;

	i = 0;
	if (!buff[i])
		return (0);
	while (buff[i] && buff[i] != '\n')
		i++;
	line = ft_calloc_c(i + 2, 1);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] && buff[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*get_next(char *buff)
{
	int		i;
	int		j;
	char	*next;

	i = 0;
	j = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (0);
	}
	next = ft_calloc_c(ft_strlen_n(buff) - i + 1, 1);
	i++;
	while (buff[i])
		next[j++] = buff[i++];
	free(buff);
	return (next);
}

char	*get_next_line(int fd)
{
	static char	*res;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	res = get_read(fd, res);
	if (!res)
		return (0);
	line = ft_get_line(res);
	res = get_next(res);
	return (line);
}
