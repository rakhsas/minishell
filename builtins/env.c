/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:03:56 by rakhsas           #+#    #+#             */
/*   Updated: 2023/03/26 13:49:20 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	search(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (str[i+1])
				return (1);
		}
		i++;
	}
	return (0);
}
void	ft_env(void)
{
	int	i;

	i = 0;
	if (!dep.env)
		printf("env: No such file or directory\n");
	while (dep.env[i])
	{
		if (search(dep.env[i], '=') == 1)
			printf ("%s\n", dep.env[i]);
		i++;
	}
}
