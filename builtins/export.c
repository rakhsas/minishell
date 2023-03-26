/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:12:01 by rakhsas           #+#    #+#             */
/*   Updated: 2023/03/23 17:56:03 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_next_next_export(t_list *list, int *k, int *help)
{
	char	*str;
	int		j;

	j = 0;
	while (dep.env[j])
	{
		str = ft_search(list->args[*k], '=');
		if (ft_strnstr(dep.env[j], str, ft_strlen(list->args[*k])))
		{
			*help = 1;
			free(dep.env[j]);
			dep.env[j] = ft_strdup(list->args[*k]);
			free(dep.env_copy[j]);
			dep.env_copy[j] = ft_strdup(list->args[*k]);
			j++;
			k[0]++;
			// free(str);
			break ;
		}
		free(str);
		j++;
	}
}

void	ft_next_export(t_list *list, int *i, int *help)
{
	int	k;

	k = 1;
	while (list->args[*i])
		i[0]++;
	while (k < i[0])
	{
		ft_next_next_export(list, &k, help);
		k++;
	}
}

void	ft_next_next(t_list *list)
{
	int	i;
	int	k;
	int	help;

	i = 1;
	help = 0;
	ft_next_export(list, &i, &help);
	if (help == 0)
	{
		k = 1;
		while (k < i)
		{
			dep.env_copy = ft_realloc(dep.env_copy, list->args[k]);
			dep.env = ft_realloc(dep.env, list->args[k]);
			k++;
		}
	}
}

void	ft_export(t_list *list)
{
	int		i;

	i = 0;
	if (!list->args[1])
	{
		if (dep.env_copy)
		{
			while (dep.env_copy[i])
			{
				printf("declare -x %s\n", dep.env_copy[i]);
				i++;
			}
		}
	}
	else if (list->args[1])
		ft_next_next(list);
}
