/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:12:01 by rakhsas           #+#    #+#             */
/*   Updated: 2023/03/31 00:09:17 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_next_next_export(t_list *list, int *k, int *help)
{
	char	*str;
	int		j;

	j = 0;
	while (g_dep.env[j])
	{
		str = ft_search(list->args[*k], '=');
		if (ft_strnstr(g_dep.env[j], str, ft_strlen(list->args[*k])))
		{
			*help = 1;
			free(g_dep.env[j]);
			g_dep.env[j] = ft_strdup(list->args[*k]);
			free(g_dep.env_copy[j]);
			g_dep.env_copy[j] = ft_strdup(list->args[*k]);
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
			g_dep.env_copy = ft_realloc(g_dep.env_copy, list->args[k]);
			g_dep.env = ft_realloc(g_dep.env, list->args[k]);
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
		if (g_dep.env_copy)
		{
			while (g_dep.env_copy[i])
			{
				printf("declare -x %s\n", g_dep.env_copy[i]);
				i++;
			}
		}
	}
	else if (list->args[1])
		ft_next_next(list);
}
