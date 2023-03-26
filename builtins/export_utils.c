/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:58:58 by rakhsas           #+#    #+#             */
/*   Updated: 2023/03/20 15:28:17 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_next_search(int *i, char *str)
{
	char	*s;
	int		j;

	j = 0;
	s = (char *)malloc(sizeof(char) * (*i + 1));
	if (!s)
		return (NULL);
	while (str[j] && j < *i)
	{
		s[j] = str[j];
		j++;
	}
	s[j] = '\0';
	return (s);
}

char	*ft_search(char *str, char c)
{
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;
			break ;
		}
		i++;
	}
	return (ft_next_search(&i, str));
}
