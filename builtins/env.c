/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:03:56 by rakhsas           #+#    #+#             */
/*   Updated: 2023/03/31 00:08:21 by aankote          ###   ########.fr       */
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
void	ft_env(int out)
{
	int	i;

	i = 0;
	if (!g_dep.env)
		ft_putstr_fd("env: No such file or directory\n", out);
	while (g_dep.env[i])
	{
		if (search(g_dep.env[i], '=') == 1)
			ft_putendl_fd(g_dep.env[i], out);
		i++;
	}
}
