/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:03:56 by rakhsas           #+#    #+#             */
/*   Updated: 2023/03/29 02:00:04 by aankote          ###   ########.fr       */
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
	if (!dep.env)
		ft_putstr_fd("env: No such file or directory\n", out);
	while (dep.env[i])
	{
		if (search(dep.env[i], '=') == 1)
			ft_putendl_fd(dep.env[i], out);
		i++;
	}
}
