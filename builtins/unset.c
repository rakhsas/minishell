/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:09:44 by rakhsas           #+#    #+#             */
/*   Updated: 2023/03/30 13:51:20 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset_next(t_list *list, int j, int i)
{
	int	copy;

	copy = 0;
	j = 0;
	while (dep.env[j] != NULL)
	{
		if (ft_strnstr(dep.env[j], list->args[i],
				ft_strlen(list->args[i]))
			&& (dep.env[j][ft_strlen(list->args[i])] == '='
			|| dep.env[j][ft_strlen(list->args[i])] == '\0'))
		{
			while (dep.env[j])
			{
				free(dep.env[j]);
				dep.env[j] = dep.env[j + 1];
				free(dep.env_copy[j]);
				dep.env_copy[copy] = dep.env_copy[copy + 1];
				j++;
				copy++;
			}
			dep.env[copy] = 0;
			dep.env_copy[copy] = 0;
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

	i = 0;
	j = 0;
	if (list->args)
	{
		while (list->args[i])
		{
			j = 0;
			if (!ft_isalnum(list->args[i][ft_strlen(list->args[i]) - 1])
					&& !ft_strnstr(dep.env[j], list->args[i],
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
