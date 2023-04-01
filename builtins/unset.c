/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:09:44 by rakhsas           #+#    #+#             */
/*   Updated: 2023/04/01 16:06:31 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset_next(t_list *list, int j, int i)
{
	int	copy;

	copy = 0;
	j = 0;
	while (g_dep.env[j] != NULL)
	{
		if (ft_strnstr(g_dep.env[j], list->args[i],
				ft_strlen(list->args[i]))
			&& (g_dep.env[j][ft_strlen(list->args[i])] == '='
			|| g_dep.env[j][ft_strlen(list->args[i])] == '\0'))
		{
			while (g_dep.env[j])
			{
				free(g_dep.env[j]);
				g_dep.env[j] = g_dep.env[j + 1];
				free(g_dep.env_copy[j]);
				g_dep.env_copy[copy] = g_dep.env_copy[copy + 1];
				j++;
				copy++;
			}
			g_dep.env[copy] = 0;
			g_dep.env_copy[copy] = 0;
			return ;
		}
		copy++;
		j++;
	}
}

void	ft_unset(t_list *list)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (list->args)
	{
		while (list->args[i])
		{
			j = 0;
			// exit(1);
			if (ft_isalnum(list->args[i][ft_strlen(list->args[i]) - 1] == 0)
					&& !ft_strnstr(g_dep.env[j], list->args[i],
						ft_strlen(list->args[i])))
			{
				ft_putstr_fd(list->args[0], 1);
				ft_putstr_fd(": `", 1);
				ft_putstr_fd(list->args[i], 1);
				ft_putstr_fd("': not valid identifier\n", 1);
			}
			ft_unset_next(list, j, i);
			i++;
		}
	}
}
