/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:09:18 by aankote           #+#    #+#             */
/*   Updated: 2023/03/31 01:35:41 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*get_next_line(int fd);
char	*ft_strjoin_n(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlen_n(const char *s);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc_c(size_t count, size_t size);

#endif
