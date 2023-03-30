/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:12:01 by rakhsas           #+#    #+#             */
/*   Updated: 2023/03/30 14:26:15 by rakhsas          ###   ########.fr       */
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
	if (ft_isalpha(list->args[1][0]) == 0)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(list->args[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
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

void print_test(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 1;
	char x = '"';
	while (i[str])
	{
		if (i[str] == '=' && c == 1)
		{
			write(1, &i[str], 1);
			write(1, &x, 1);
			c++;
		}
		else
			write(1, &i[str], 1);
		i++;
	}
	write(1, &x, 1);
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
				ft_putstr_fd("declare -x ", 1);
				print_test(dep.env_copy[i]);
				ft_putstr_fd("\n", 1);
				i++;
			}
		}
	}
	else if (list->args[1])
		ft_next_next(list);
	// while(1);
}
