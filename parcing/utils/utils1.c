/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:50:15 by aankote           #+#    #+#             */
/*   Updated: 2023/03/31 01:10:12 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	quotes(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i] && i != index)
	{
		if (open == 0 && line[i] == '\"')
			open = 1;
		else if (open == 1 && line[i] == '\"')
			open = 0;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 2 && line[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
}

char	**ft_realloc(char **p, char *str)
{
	int		i;
	char	**rp;

	i = 0;
	while (p && p[i])
		i++;
	rp = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (p && p[i])
	{
		rp[i] = ft_calloc(1, 1);
		rp[i] = ft_join_free(rp[i], p[i]);
		i++;
	}
	rp[i] = ft_calloc(1, 1);
	rp[i] = ft_join_free(rp[i], str);
	i++;
	rp[i] = NULL;
	free_double(p);
	return (rp);
}

char	*ft_charjoin(char *s, char c)
{
	char	*p;
	int		i;

	i = 0;
	p = malloc(ft_strlen(s) + 2);
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i++] = c;
	p[i] = 0;
	free(s);
	return (p);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_trim(char *arg)
{
	int		i;
	char	*p;

	i = -1;
	p = ft_strdup("");
	while (arg[++i])
	{
		if ((arg[i] != '\'' && arg[i] != '\"'))
			p = ft_charjoin(p, arg[i]);
		if (arg[i] == '\'' && quotes(arg, i) == 1)
			p = ft_charjoin(p, arg[i]);
		if (arg[i] == '\"' && quotes(arg, i) == 2)
			p = ft_charjoin(p, arg[i]);
	}
	return (p);
}
